#include "audio.h"
#include "process_clicky.h"

#ifdef AUDIO_CLICKY

#ifndef AUDIO_CLICKY_FREQ_DEFAULT
#define AUDIO_CLICKY_FREQ_DEFAULT 440.0f
#endif // !AUDIO_CLICKY_FREQ_DEFAULT
#ifndef AUDIO_CLICKY_FREQ_MIN
#define AUDIO_CLICKY_FREQ_MIN 65.0f
#endif // !AUDIO_CLICKY_FREQ_MIN
#ifndef AUDIO_CLICKY_FREQ_MAX
#define AUDIO_CLICKY_FREQ_MAX 1500.0f
#endif // !AUDIO_CLICKY_FREQ_MAX
#ifndef AUDIO_CLICKY_FREQ_FACTOR
#define AUDIO_CLICKY_FREQ_FACTOR 1.18921f
#endif // !AUDIO_CLICKY_FREQ_FACTOR
#ifndef AUDIO_CLICKY_FREQ_RANDOMNESS
#define AUDIO_CLICKY_FREQ_RANDOMNESS 0.05f
#endif // !AUDIO_CLICKY_FREQ_RANDOMNESS

#ifdef AUDIOCLICKY_FURY_ENABLE
#ifdef AUDIO_CLICKY_FURY_ON
bool fury_enable = true;
#else // AUDIO_CLICKY_FURY_ON
bool fury_enable = false;
#endif // !AUDIO_CLICKY_FURY_ON
#ifndef AUDIO_CLICKY_FURY_INCREMENT
#define AUDIO_CLICKY_FURY_INCREMENT 5.0f
#endif // !AUDIO_CLICKY_FURY_INCREMENT
#ifndef AUDIO_CLICKY_FURY_CUTOFF
#define AUDIO_CLICKY_FURY_CUTOFF 200
#endif // !AUDIO_CLICKY_FURY_CUTOFF
#ifndef AUDIO_CLICKY_FURY_RESET
#define AUDIO_CLICKY_FURY_RESET 2500
#endif // !AUDIO_CLICKY_FURY_CUTOFF
#endif // !AUDIO_CLICKY_FURY_ENABLE

float clicky_freq = AUDIO_CLICKY_FREQ_DEFAULT;
float clicky_song[][2]  = {{AUDIO_CLICKY_FREQ_DEFAULT, 3}, {AUDIO_CLICKY_FREQ_DEFAULT, 1}}; // 3 and 1 --> durations

extern audio_config_t audio_config;

#ifndef NO_MUSIC_MODE
extern bool music_activated;
extern bool midi_activated;
#endif // !NO_MUSIC_MODE

/* Check if either clicky mode or fury mode is enabled. */
static bool is_clicky_enabled(void) {
  bool enabled = audio_config.clicky_enable;
#ifdef AUDIOCLICKY_FURY_ENABLE
  enabled = enabled || fury_enable;
#endif
  return enabled;
}

/* Resets the clicky frequency to the default value.*/
static void reset_clicky_freq(void) {
  clicky_freq = AUDIO_CLICKY_FREQ_DEFAULT;
}

/* Clip the provided frequency to the range of
 * [AUDIO_CLICKY_FREQ_MIN, AUDIO_CLICKY_FREQ_MAX]. */
static float clip_clicky_freq(float new_freq) {
  if (new_freq > AUDIO_CLICKY_FREQ_MAX) {
    return AUDIO_CLICKY_FREQ_MAX;
  } else if (new_freq < AUDIO_CLICKY_FREQ_MIN) {
    return AUDIO_CLICKY_FREQ_MIN;
  }
  return new_freq;
}

static float randomize_freq(float freq) {
  return freq * (1.0 + AUDIO_CLICKY_FREQ_RANDOMNESS * ((float)rand() / (float)RAND_MAX));
}

void clicky_play(void) {
#ifndef NO_MUSIC_MODE
  if (music_activated || midi_activated) return;
#endif // !NO_MUSIC_MODE

#ifdef AUDIOCLICKY_FURY_ENABLE
  if (fury_enable) {
    static uint32_t last_click = 0U;
    uint32_t duration = timer_elapsed32(last_click);

    if (duration < (uint32_t)AUDIO_CLICKY_FURY_CUTOFF) {
      clicky_freq += AUDIO_CLICKY_FURY_INCREMENT;
    } else if (duration < (uint32_t)AUDIO_CLICKY_FURY_RESET) {
      int32_t ticks = duration / AUDIO_CLICKY_FURY_CUTOFF;
      clicky_freq += (ticks * -AUDIO_CLICKY_FURY_INCREMENT);
    } else {
      reset_clicky_freq();
    }

    last_click = timer_read32();
    clicky_freq = clip_clicky_freq(clicky_freq);

    /* Fury and clicky modes can be combined (allowing some randomness to be
     * added to the fury.)  If clicky_mode is enabled, then the fury-adjusted
     * clicky_freq will be used later to create the song.  Otherwise, we need
     * to create the song here. */
    if (!clicky_enable) {
      clicky_song[0][0] = clip_clicky_freq(2.0f * clicky_freq);
      clicky_song[1][0] = clicky_freq;
    }
  }
#endif // !AUDIO_CLICKY_FURY_ENABLE

  if (clicky_enable) {
    clicky_song[0][0] = clip_clicky_freq(2.0f * randomize_freq(clicky_freq));
    clicky_song[1][0] = clip_clicky_freq(randomize_freq(clicky_freq));
  }

  PLAY_SONG(clicky_song);
}

void clicky_freq_up(void) {
  float new_freq = clicky_freq * AUDIO_CLICKY_FREQ_FACTOR;
  if (new_freq < AUDIO_CLICKY_FREQ_MAX) {
    clicky_freq = new_freq;
  }
}

void clicky_freq_down(void) {
  float new_freq = clicky_freq / AUDIO_CLICKY_FREQ_FACTOR;
  if (new_freq > AUDIO_CLICKY_FREQ_MIN) {
    clicky_freq = new_freq;
  }
}

void clicky_freq_reset(void) {
  clicky_freq = AUDIO_CLICKY_FREQ_DEFAULT;
}

void clicky_toggle(void) {
  audio_config.clicky_enable ^= 1;
  eeconfig_update_audio(audio_config.raw);
}

void clicky_on(void) {
  audio_config.clicky_enable = 1;
  eeconfig_update_audio(audio_config.raw);
}

void clicky_off(void) {
  audio_config.clicky_enable = 0;
  eeconfig_update_audio(audio_config.raw);
}

bool is_clicky_on(void) {
      return (audio_config.clicky_enable != 0);
}

bool process_clicky(uint16_t keycode, keyrecord_t *record) {
    if (keycode == CLICKY_TOGGLE && record->event.pressed) { clicky_toggle(); }

    if (keycode == CLICKY_ENABLE && record->event.pressed) { clicky_on(); }
    if (keycode == CLICKY_DISABLE && record->event.pressed) { clicky_off(); }
    if (keycode == CLICKY_RESET && record->event.pressed) { clicky_freq_reset(); }
    if (keycode == CLICKY_UP && record->event.pressed) { clicky_freq_up(); }
    if (keycode == CLICKY_DOWN && record->event.pressed) { clicky_freq_down(); }

#ifdef AUDIOCLICKY_FURY_ENABLE
    if (keycode == CLICKY_FURY_TOGGLE && record->event.pressed) {
      reset_clicky_freq();
      fury_enable = !fury_enable;
    }
#endif

    if (is_clicky_enabled()) {
      if (record->event.pressed) {
        clicky_play();;
      }
    }
    return true;
}

#endif //AUDIO_CLICKY
