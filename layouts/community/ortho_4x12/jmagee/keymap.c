/* Copyright 2015-2017 Jack Humbert, 2018 Joshua Magee
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

#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "chord.h"
#include "keycodes.h"
#include "layers.h"
#include "leader.h"
#include "mouse.h"

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
[_BASE] = LAYOUT_ortho_4x12(
  BASE   , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LEAD,
  ESCTRL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
  SYMBOLS, NUMPAD,  KC_LGUI, KC_LALT, KC_SPC , KC_TAB,  KC_BSPC, KC_ENT,  KC_RALT, NAVI   , MOUSER,  ALBHED
),

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
[_ALBHED] = LAYOUT_ortho_4x12(
  _______, KC_X,    KC_F,    KC_A,    KC_N,    KC_D,    KC_O,    KC_I,    KC_E,    KC_U,    KC_B,    _______,
  _______, KC_Y,    KC_C,    KC_T,    KC_V,    KC_K,    KC_R,    KC_Z,    KC_G,    KC_M,    KC_SCLN, KC_QUOT,
  _______, KC_W,    KC_Q,    KC_L,    KC_J,    KC_P,    KC_H,    KC_S,    KC_COMM, KC_DOT,  KC_SLSH, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |   b  |   7  |   8  |   9  |  e   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  /   |  *   |  -   |  +   |  %   |   a  |   4  |   5  |   6  |  d   |  f   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  0x  |  ,   |  .   |      |   0  |   1  |   2  |   3  |  c   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_ortho_4x12(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_B   , KC_7,    KC_8,    KC_9,    KC_E   , _______,
  _______, KC_SLSH, KC_ASTR, KC_MINS, KC_PLUS, KC_PERC, KC_A  ,  KC_4,    KC_5,    KC_6,    KC_D   , KC_F   ,
  _______, XXXXXXX, KC_HEX , KC_COMM, KC_DOT , XXXXXXX, KC_0,    KC_1,    KC_2,    KC_3,    KC_C   , _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |      |  !   |   @  |  #   |      |      |  &   |   [  |  ]   |      |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  /   |   *  |  -   |  +   |  %   |   {  |   (  |  )   |  }   |  |   | tilda|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  _   |  =   |      |      |   ^  |  $   |      | tick |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOLS] = LAYOUT_ortho_4x12(
  _______, KC_EXLM, KC_AT,   KC_HASH, XXXXXXX, XXXXXXX, KC_AMPR, KC_LBRC, KC_RBRC, XXXXXXX, KC_BSLS, _______,
  _______, KC_SLSH, KC_ASTR, KC_MINS, KC_PLUS, KC_PERC, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE, KC_TILD,
  _______, XXXXXXX, XXXXXXX, KC_UNDS, KC_EQL , XXXXXXX, XXXXXXX, KC_CIRC, KC_DLR , XXXXXXX, KC_GRV , _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Navigation
 * This doesn't have keys like HOME, END, and others - I never use those.  I'll add them
 * if/when I need them.
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      | READ | PGUP |      |      |UNREAD|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | DEL  | PGDN |      |  <-  | Down | Up   |  ->  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVI] = LAYOUT_ortho_4x12(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, KC_READ, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, XXXXXXX, XXXXXXX, KC_DEL , KC_PGDN, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Mouser.
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |  C3  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |SQUEEK|      |  C4  |  C1  |      |  <-  | Down | Up   |  ->  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  C2  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSER] = LAYOUT_ortho_4x12(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, SQUEEK , XXXXXXX, KC_BTN4, KC_BTN1, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_custom_keycodes(keycode, record);
}

void matrix_init_user(void) {
  debug_enable = true;
}

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    leader_fkeys();
    leader_ctrl_alt_del();
    leader_virtual_consoles();
    leader_xmonad();
    leader_secret();
    leader_utility();
    leader_nkro();
    leader_music();
  }
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case KC_SPACE:
    case KC_TAB:
      return false;
  }

  return !is_layer_keycode(keycode);
}

uint32_t layer_state_set_user(uint32_t state) {
  /* Send a special keystroke on layer state change.
   * My window manager maps this to a utility which records the
   * currently active layer and displays it. */
  switch (biton32(state)) {
    case _BASE:
      print("Layer: base\n");
      /*meh_chord(KC_B);*/
      break;
    case _ALBHED:
      /*meh_chord(KC_A);*/
      print("Layer: albhed\n");
      break;
    case _NUMPAD:
      /*meh_chord(KC_N);*/
      print("Layer: numpad\n");
      break;
    case _SYMBOLS:
      /*meh_chord(KC_S);*/
      print("Layer: symbols\n");
      break;
    case _NAVI:
      /*meh_chord(KC_V);*/
      print("Layer: navi\n");
      break;
    case _MOUSER:
      /*meh_chord(KC_M);*/
      print("Layer: mouser\n");
      break;
  }
  return state;
}

/* vim: set nowrap : */
