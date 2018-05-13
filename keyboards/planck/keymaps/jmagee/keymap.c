/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"
#include "layers.h"
#include "leader.h"
#include "nkro.h"
#include <assert.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |QWERTY|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Leader|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |EsCtl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |NumPad| Sym  | GUI  | Alt  |Space | Tab  |Bksp  |Enter | Comp | Navi |Mouser|AlBhed|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {QWERTY , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LEAD},
  {ESCTRL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______},
  {T_NUMPAD,T_SYM  , KC_LGUI, KC_LALT, KC_SPC , KC_TAB,  KC_BSPC, KC_ENT,  T_NAVI , T_MOUSE, _______, T_BHED }
},

/* Al Bhed
 * ,-----------------------------------------------------------------------------------.
 * |xfando|   X  |   F  |   A  |   N  |   D  |   O  |   I  |   E  |   U  |   B  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Y  |   C  |   T  |   V  |   K  |   R  |   Z  |   G  |   M  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   W  |   Q  |   L  |   J  |   P  |   H  |   S  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ALBHED] = {
  {_______, KC_X,    KC_F,    KC_A,    KC_N,    KC_D,    KC_O,    KC_I,    KC_E,    KC_U,    KC_B,    _______},
  {_______, KC_Y,    KC_C,    KC_T,    KC_V,    KC_K,    KC_R,    KC_Z,    KC_G,    KC_M,    KC_SCLN, KC_QUOT},
  {_______, KC_W,    KC_Q,    KC_L,    KC_J,    KC_P,    KC_H,    KC_S,    KC_COMM, KC_DOT,  KC_SLSH, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |  +   |   7  |   8  |   9  |  /   |  +   |   7  |   8  |   9  |  /   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  .   |   4  |   5  |   6  |  *   |   .  |   4  |   5  |   6  |  *   |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  0   |   1  |   2  |   3  |  -   |   0  |   1  |   2  |   3  |  -   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = {
  {_______, KC_PLUS, KC_7,    KC_8,    KC_9,    KC_SLSH, KC_PLUS, KC_7,    KC_8,    KC_9,    KC_SLSH, _______},
  {_______, KC_DOT,  KC_4,    KC_5,    KC_6,    KC_ASTR, KC_DOT,  KC_4,    KC_5,    KC_6,    KC_ASTR, KC_PLUS},
  {_______, KC_0,    KC_1,    KC_2,    KC_3,    KC_MINS, KC_0,    KC_1,    KC_2,    KC_3,    KC_SLSH, KC_ENT },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |      |  !   |   @  |  #   |  $   |  %   |   +  |   [  |  ]   |  *   |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  &   |      |   {  |   (  |  )   |  }   |  |   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   /  |   _  |  -   |  =   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOLS] = {
  {_______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR , KC_PERC, KC_PLUS, KC_LBRC, KC_RBRC, KC_ASTR, KC_NUBS, _______},
  {_______, _______, _______, _______, KC_AMPR, _______, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE, _______},
  {_______, _______, _______, _______, _______, _______, KC_N,    KC_UNDS, KC_MINS, KC_EQL,  _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Navigation
 * This doesn't have keys like HOME, END, and others - I never use those.  I'll add them
 * if/when I need them.
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      | PGUP |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | PGDN |      |  <-  | Down | Up   |  ->  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVI] = {
  {_______, _______, _______, _______, KC_PGUP, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, KC_PGDN, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Mouser.
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |  C3  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  C4  |  C1  |      |  <-  | Down | Up   |  ->  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  C2  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSER] = {
  {_______, _______, _______, _______, KC_BTN3, _______, _______, _______, _______, _______, _______, _______},
  {_______, SQUEEK , _______, KC_BTN4, KC_BTN1, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______},
  {_______, _______, _______, _______, KC_BTN2, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},
};

uint32_t layer_state_set_user(uint32_t state) {
  return state;
#if 0
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (is_layer_keycode(keycode)) {
    if (record->event.pressed) {
      activate_layer(keycode_to_layer(keycode));
      return false;
    }
  }

  switch (keycode) {
    case SQUEEK: {
      /* Toggle through the mouse acceleration speeds. */
      static const uint8_t lookup[3] = { KC_ACL0, KC_ACL1, KC_ACL2 };
      static uint8_t current = 0;
      if (record->event.pressed) {
        ++current;
        if (current > 2) {
          current = 0;
        }
        CHORD1(lookup[current]);
      }
      return false;
    }
  }
  return true;
}

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    leader_fkeys();
    leader_ctrl_alt_del();
    leader_virtual_consoles();
    leader_xmonad();

    SEQ_ONE_KEY(KC_N) {
      enable_nkro(NK_TOGGLE);
    }
  }
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    default:
      return true;
  }
}
