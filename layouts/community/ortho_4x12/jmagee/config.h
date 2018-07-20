#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    /* #define STARTUP_SONG SONG(NO_SOUND) */

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND) }
    /*#define AUDIO_CLICKY */
#endif

/* Mouser key settings.  All are specified in ms. */
/* When one of the mouse movement buttons is pressed this setting is used to
 * define the delay between that button press and the mouse cursor moving. Some
 * people find that small movements are impossible if this setting is too low,
 * while settings that are too high feel sluggish. */
#define MOUSEKEY_DELAY             300

/* When a movement key is held down this specifies how long to wait between each
 * movement report. Lower settings will translate into an effectively higher mouse
 * speed. */
#define MOUSEKEY_INTERVAL          50

/* As a movement key is held down the speed of the mouse cursor will increase
 * until it reaches MOUSEKEY_MAX_SPEED. */
#define MOUSEKEY_MAX_SPEED         10

/* How long you want to hold down a movement key for until MOUSEKEY_MAX_SPEED is
 * reached. This controls how quickly your cursor will accelerate. */
#define MOUSEKEY_TIME_TO_MAX       20

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

/* Re-enable tapping, in the case that the default config disables it (e.g. for
 * Let's Split Vitamins Included. */
#undef NO_ACTION_TAPPING

#endif
