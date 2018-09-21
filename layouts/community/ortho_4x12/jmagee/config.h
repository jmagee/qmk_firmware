#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    /* #define STARTUP_SONG SONG(NO_SOUND) */

    /*#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND) } */
    #define AUDIO_CLICKY
    /*#define AUDIO_CLICKY_FREQ_MIN 400.0f*/
    /*#define AUDIO_CLICKY_FREQ_MAX 500.0f*/
    //#define AUDIO_CLICKY_FREQ_RANDOMNESS 0.00001f
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

#define TAPPING_TERM 200

#endif
