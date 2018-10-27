/*
Copyright 2018 Cole Markham, Joshua Magee

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "layers.h"
#include "tapdance.h"

static uint32_t mode;
static uint16_t h;
static uint8_t s, v;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT(TD(TD_LCK))
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LCK]  = ACTION_TAP_DANCE_FN(lock_dance)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE ;
}

void matrix_init_user(void) {
  static bool initialized = 0;
  debug_enable = true;
  if (!initialized){
      dprintf("Initializing in matrix_scan_user");
      rgblight_enable();
      /*rgblight_mode(7);*/
      /*rgblight_sethsv(0,255,255);*/
      /*rgblight_setrgb(0x00, 0x00, 0xFF);*/
      rgblight_mode(1);
      rgblight_sethsv(189, 71, 100);
      initialized = 1;
    }
}

void matrix_scan_user(void) {
  expire_short_lock();
}

void lock_state_changed_user(Lock_t lock_state) {
  switch (lock_state) {
    case Unlocked:
      mode = 1;
      h = 189;
      s = 71;
      v = 100;
      break;
    case Short_lock:
      mode = 2;
      h = 43;
      s = 186;
      v = 255;
      break;
    case Long_lock:
      mode = 2;
      h = 359;
      s = 255;
      v = 255;
      break;
  }
  rgblight_mode(mode);
  rgblight_sethsv(h, s, v);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv(296, 39, 255);
  } else {
    rgblight_mode(mode);
    rgblight_sethsv(h, s, v);
  }
  return true;
}
