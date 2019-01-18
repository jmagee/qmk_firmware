/* Copyright 2018 Joshua Magee
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "leader.h"

#include "chord.h"
#include "layers.h"
#include "nkro.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
PROGMEM const char secrets[][32] = { "a" };

enum {
  SECRET_W = 0,
  SECRET_D,
  SECRET_P
};
#endif

enum { N_FKEYS = 25 };
PROGMEM static const uint8_t fkeys[N_FKEYS] = {
  KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
  KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20,
  KC_F21, KC_F22, KC_F23, KC_F24
};

PROGMEM static const uint8_t digits[10][2] = {
  /* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 on QWERTY layer */
  {KC_N, KC_0},
  {KC_M, KC_1},
  {KC_COMM, KC_2},
  {KC_DOT, KC_3},
  {KC_J, KC_4},
  {KC_K, KC_5},
  {KC_L, KC_6},
  {KC_U, KC_7},
  {KC_I, KC_8},
  {KC_O, KC_9}
};

/* Helper function to check the leader sequence.
 * This is equivalent to the SEQ_*_KEYS macros.  Pulling the functionality
 * out into a separate function helps reduce code size dramatically. */
static bool leader_check(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e) {
  if (leader_sequence[0] != a) { return false; }
  if (leader_sequence[1] != b) { return false; }
  if (leader_sequence[2] != c) { return false; }
  if (leader_sequence[3] != d) { return false; }
  if (leader_sequence[4] != e) { return false; }
  return true;
}

/* Helper to map F-key based sequences to a virtual numpad.
 * leader_key is simply a keycode.
 * fkey_map is a function that accepts a keycode argument (one of the
 * F keys) and does something with it (e.g. register keypress events)
 * */
static void f1_to_vnumpad(uint8_t leading_key, void (*fkey_map)(uint8_t)) {
#if 1
  uint8_t f = 1;

  for (uint8_t i = 1; i < 25; ++i) {
    if (i < 10) {
      /* F1 - F9 */
      if (leader_check(leading_key, pgm_read_byte(&(digits[i][0])), 0, 0, 0)) {
        fkey_map(pgm_read_byte(&(fkeys[f])));
      }
    } else {
      /* F10 - F24 */
      uint8_t d1 = i < 20 ? 1 : 2;
      if (leader_check(leading_key,
                       pgm_read_byte(&(digits[d1][0])),
                       pgm_read_byte(&(digits[i % 10])),
                       0, 0)) {
        fkey_map(pgm_read_byte(&(fkeys[f])));
      }
    }
    ++f;
  }
#endif
#if 0
  SEQ_TWO_KEYS(leading_key, digits[1][0]) { fkey_map(fkeys[1]); }
  SEQ_TWO_KEYS(leading_key, digits[2][0]) { fkey_map(fkeys[2]); }
  SEQ_TWO_KEYS(leading_key, digits[3][0]) { fkey_map(fkeys[3]); }
  SEQ_TWO_KEYS(leading_key, digits[4][0]) { fkey_map(fkeys[4]); }
  SEQ_TWO_KEYS(leading_key, digits[5][0]) { fkey_map(fkeys[5]); }
  SEQ_TWO_KEYS(leading_key, digits[6][0]) { fkey_map(fkeys[6]); }
  SEQ_TWO_KEYS(leading_key, digits[7][0]) { fkey_map(fkeys[7]); }
  SEQ_TWO_KEYS(leading_key, digits[8][0]) { fkey_map(fkeys[8]); }
  SEQ_TWO_KEYS(leading_key, digits[9][0]) { fkey_map(fkeys[9]); }
  SEQ_THREE_KEYS(leading_key, digits[1][0], digits[0][0]) { fkey_map(fkeys[10]); }
  SEQ_THREE_KEYS(leading_key, digits[1][0], digits[1][0]) { fkey_map(fkeys[11]); }
  SEQ_THREE_KEYS(leading_key, digits[1][0], digits[2][0]) { fkey_map(fkeys[12]); }
#endif
}

static void ctrl_alt_fkey_map(uint8_t f) {
  chord3(KC_LCTRL, KC_LALT, f);
}

void leader_fkeys(void) {
  f1_to_vnumpad(KC_F, chord1);
}

void leader_ctrl_alt_del(void) {
  if (leader_check(KC_C, KC_A, KC_D, 0, 0)) {
    chord3(KC_LCTRL, KC_LALT, KC_DELETE);
  }
}

void leader_virtual_consoles(void) {
  f1_to_vnumpad(KC_V, ctrl_alt_fkey_map);
}

void leader_xmonad(void) {
  /* launch a terminal */
  if (leader_check(KC_X, KC_ENT, 0, 0, 0)) {
    chord3(KC_LALT, KC_LSFT, KC_ENT);
  }

  /* launch a dmenu */
  if (leader_check(KC_X, KC_P, 0, 0, 0)) {
    chord2(KC_LALT, KC_P);
  }

  /* lock the screen */
  if (leader_check(KC_X, KC_X, 0, 0, 0)) {
    chord2(KC_LALT, KC_X);
  }

  /* close window */
  if (leader_check(KC_X, KC_C, 0, 0, 0)) {
    chord3(KC_LALT, KC_LSFT, KC_C);
  }

  /* cycle layout */
  if (leader_check(KC_X, KC_SPC, 0, 0, 0)) {
    chord2(KC_LALT, KC_SPC);
  }

  /* Toggle the status bar (e.g. xmobar or similiar) */
  if (leader_check(KC_X, KC_B, 0, 0, 0)) {
    chord2(KC_LALT, KC_B);
  }

  /* Start a pomodoro */
  if (leader_check(KC_X, KC_D, 0, 0, 0)) {
    chord2(KC_LALT, KC_D);
  }

  /* quit */
  if (leader_check(KC_X, KC_Q, 0, 0, 0)) {
    chord4(KC_LALT, KC_LSFT, KC_LCTL, KC_Q);
  }

  /* restart */
  if (leader_check(KC_X, KC_R, 0, 0, 0)) {
    chord3(KC_LALT, KC_LSFT, KC_Q);
  }

  /* atl tab */
  if (leader_check(KC_TAB, 0, 0, 0, 0)) {
    chord2(KC_LALT, KC_TAB);
  }

  /* Switch desktops */
  for (uint8_t i = 1; i <= 9; ++i) {
    uint8_t lhs = pgm_read_byte(&(digits[i][0])),
            rhs = pgm_read_byte(&(digits[i][1]));
    if (leader_check(KC_X, lhs, 0, 0, 0)) {
      chord2(KC_LALT, rhs);
    }
    if (leader_check(KC_X, lhs, lhs, 0, 0)) {
      chord3(KC_LALT, KC_LSFT, rhs);
    }
  }

  /* Maybe this should be moved to something like leader_windows ?*/
  if (leader_check(KC_X, KC_T, 0, 0, 0)) {
    chord2(KC_LGUI, KC_GRV);
  }
}

void leader_secret(void) {
  if (leader_check(KC_S, KC_W, 0, 0, 0)) {
    send_string_P(secrets[SECRET_W]);
  }

  if (leader_check(KC_S, KC_D, 0, 0, 0)) {
    send_string_P(secrets[SECRET_D]);
  }

  if (leader_check(KC_S, KC_P, 0, 0, 0)) {
    send_string_P(secrets[SECRET_P]);
  }
}

void leader_utility(void) {
  if (leader_check(KC_F, KC_L, KC_A, KC_S, KC_H)) {
    reset_keyboard();
  }
}

void leader_nkro(void) {
  if (leader_check(KC_N, 0, 0, 0, 0)) {
    enable_nkro(NK_TOGGLE);
  }
}

void leader_god(void) {
#ifdef USE_GOD_LAYER
  if (leader_check(KC_G, KC_O, KC_D, 0, 0)) {
    activate_layer(_GOD);
  }
#endif
}

#if defined(AUDIO_ENABLE)
extern bool music_activated;
extern bool fury_enable;
#endif

void leader_music(void) {
#if defined(AUDIO_ENABLE)
  if (leader_check(KC_SPACE, KC_SPACE, 0, 0, 0)) {
    music_activated ? music_off() : music_on();
  }

  if (leader_check(KC_TAB, KC_TAB, 0, 0, 0)) {
    music_mode_cycle();
  }

  if (leader_check(KC_C, KC_L, KC_I, KC_C, KC_K)) {
    clicky_toggle();
  }

#ifdef AUDIOCLICKY_FURY_ENABLE
  if (leader_check(KC_F, KC_U, KC_R, KC_Y, 0)) {
    fury_enable = !fury_enable;
  }
#endif
#endif
}

void leader_debug(void) {
  if (leader_check(KC_D, KC_E, KC_B, KC_U, KC_G)) {
    debug_enable = !debug_enable;
    if (debug_enable) {
      print("Debug on\n");
    } else {
      print("Debug off\n");
    }
  }
}
