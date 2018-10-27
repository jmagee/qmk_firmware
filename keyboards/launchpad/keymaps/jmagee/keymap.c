#include QMK_KEYBOARD_H
#include "keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  LAYOUT( \
    KC_X1,      KC_X2, \
    KC_X3,      KC_X4, \
    KC_X5,      KC_X6, \
    KC_X7,      KC_X8  \
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
