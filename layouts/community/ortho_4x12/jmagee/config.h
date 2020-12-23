#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    /* #define STARTUP_SONG SONG(NO_SOUND) */

    /*#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND) } */
    #define AUDIO_CLICKY
    #define AUDIO_CLICKY_FREQ_MIN 75.0f
    #define AUDIO_CLICKY_FREQ_MAX 3000.0f
    #define AUDIO_CLICKY_FREQ_RANDOMNESS 0.1f
    #define AUDIOCLICKY_FURY_ENABLE
#endif

/* Mouser key settings.  All are specified in ms. */
/* When one of the mouse movement buttons is pressed this setting is used to
 * define the delay between that button press and the mouse cursor moving. Some
 * people find that small movements are impossible if this setting is too low,
 * while settings that are too high feel sluggish. */
#define MOUSEKEY_DELAY             200

/* When a movement key is held down this specifies how long to wait between each
 * movement report. Lower settings will translate into an effectively higher mouse
 * speed. */
#define MOUSEKEY_INTERVAL          25

/* As a movement key is held down the speed of the mouse cursor will increase
 * until it reaches MOUSEKEY_MAX_SPEED. */
#define MOUSEKEY_MAX_SPEED         12

/* How long you want to hold down a movement key for until MOUSEKEY_MAX_SPEED is
 * reached. This controls how quickly your cursor will accelerate. */
#define MOUSEKEY_TIME_TO_MAX       10

/* The top speed for scrolling movements. */
#define MOUSEKEY_WHEEL_MAX_SPEED   8

/* How long you want to hold down a scroll key for until
 * MOUSEKEY_WHEEL_MAX_SPEED is reached. This controls how quickly your scrolling
 * will accelerate. */
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

/* Leader key settings */
#define LEADER_TIMEOUT 300

/* Layer settings */
#define USE_ALBHED_LAYER
#define USE_NUMPAD_LAYER
#define USE_NAVI_LAYER
#define USE_SYMBOLS_LAYER
#define USE_MOUSER_LAYER

#ifdef NO_ACTION_TAPPING
/* Error if this is defined as my config depends on action tapping. */
#error "NO_ACTION_TAPPING is defined."
#endif

#undef DISABLE_LEADER

#define LEADER_PER_KEY_TIMING
#define TAPPING_TERM 200

#ifdef RGBLIGHT_ENABLE
/* If RGBLIGHT is enabled, then enable some - but not all - animations. */
/*#define RGBLIGHT_ANIMATIONS - all, but takes too much space */
//#define RGBLIGHT_EFFECT_BREATHING
//#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
//#define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#define RGBLIGHT_EFFECT_SNAKE
//#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE
#endif

#endif
