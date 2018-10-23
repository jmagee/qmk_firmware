// Below layout is based upon /u/That-Canadian's planck layout
#include "launchpad.h"
#include "keycodes.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------.
 * |   1  |  2   |
 * |------+------|
 * |   3  |  4   |
 * |------+------|
 * |   5  |  6   |
 * |------+------|
 * |   7  |  8   |
 * `-------------'
 */
[_QWERTY] = LAYOUT( \
    KC_X1,      KC_X2, \
    KC_X3,      KC_X4, \
    KC_X5,      KC_X6, \
    KC_X7,      KC_X8 \
)
};

void matrix_init_user(void) {
  static bool initialized = 0;
  if (!initialized){
    rgblight_enable();
    rgblight_mode(2);
    rgblight_sethsv(301, 77, 72);
    initialized = 1;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv(296, 39, 255);
  } else {
    rgblight_mode(2);
    rgblight_sethsv(301, 77, 72);
  }
  return process_custom_keycodes(keycode, record);
}
