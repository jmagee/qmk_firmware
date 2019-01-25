#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "tapdance.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  LAYOUT( \
    TD(KC_X1),  TD(KC_X2), \
    TD(KC_X3),  TD(KC_X4), \
    TD(KC_X5),  TD(KC_X6), \
    TD(KC_X7),  TD(KC_X8)  \
  )
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [KC_X1]  = ACTION_TAP_DANCE_FN(x_dance),
  [KC_X2]  = ACTION_TAP_DANCE_FN(x_dance),
  [KC_X3]  = ACTION_TAP_DANCE_FN(x_dance),
  [KC_X4]  = ACTION_TAP_DANCE_FN(x_dance),
  [KC_X5]  = ACTION_TAP_DANCE_FN(x_dance),
  [KC_X6]  = ACTION_TAP_DANCE_FN(x_dance),
  [KC_X7]  = ACTION_TAP_DANCE_FN(x_dance),
  [KC_X8]  = ACTION_TAP_DANCE_FN(x_dance)
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
