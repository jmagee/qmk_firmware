#include QMK_KEYBOARD_H
#include <keymap_german.h>
#include "layers.h"
#include "leader.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
#define _BL 0
#define _FL 1
#define _CL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwertz.  We're re-using the _QWERTY layer name because it is close enough. */
[_QWERTY] = LAYOUT(
  DE_CIRC,DE_1,   DE_2,   DE_3,   DE_4,   DE_5,   DE_6,   DE_7,   DE_8,   DE_9,   DE_0,   DE_SS,  DE_ACUT,XXXXXXX,KC_BSPC,        KC_PGUP,
  KC_TAB, DE_Q,   DE_W,   DE_E,   DE_R,   DE_T,   DE_Z,   DE_U,   DE_I,   DE_O,   DE_P,   DE_UE,  DE_PLUS,XXXXXXX,                KC_PGDN,
  ESCTRL, DE_A,   DE_S,   DE_D,   DE_F,   DE_G,   DE_H,   DE_J,   DE_K,   DE_L,   DE_OE,  DE_AE  ,DE_HASH,KC_ENT,
  KC_LSFT,DE_LESS,DE_Y,   DE_X,   DE_C,   DE_V,   DE_B,   DE_N,   DE_M,   DE_COMM,DE_DOT, DE_MINS,KC_LEAD,KC_RSFT,        KC_UP,
  KC_LOCK,KC_LGUI,KC_LALT,KC_HYPR,        KC_SPC, KC_ENT,                         DE_ALGR,KC_MEH, MO(_FL),KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT(
  _______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_DEL,        KC_VOLU,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_MUTE,                KC_VOLD,
  _______,_______,MO(_CL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_PGUP,
  _______,_______,_______,_______,        _______,_______,                        _______,_______,MO(_FL),_______,KC_HOME,KC_PGDN,KC_END),

  /* Keymap _CL: Control layer
   */
[_CL] = LAYOUT(
  BL_STEP,RGB_M_P,RGB_M_B,RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,RGB_M_X,RGB_M_G,_______,_______,_______,_______,_______,RGB_TOG,        RGB_VAI,
  _______,_______,_______,_______,RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,                RGB_VAD,
  _______,_______,MO(_CL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
  MO(_FL),_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        RGB_SAI,
  _______,_______,_______,_______,        RGB_MOD,   RGB_MOD,                     _______,_______,MO(_FL),_______,RGB_HUD,RGB_SAD,RGB_HUI),
};

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    leader_ctrl_alt_del();
    leader_utility();
    leader_nkro();
  }
}
/* vim: set nowrap : */
