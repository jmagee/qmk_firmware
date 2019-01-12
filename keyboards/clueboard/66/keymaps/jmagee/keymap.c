#include QMK_KEYBOARD_H
#include <keymap_german.h>
#include "keycodes.h"
#include "layers.h"
#include "leader.h"

static uint32_t mode;
static uint16_t h;
static uint8_t s, v;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwertz. */
[_BASE] = LAYOUT(
  DE_CIRC,DE_1,   DE_2,   DE_3,   DE_4,   DE_5,   DE_6,   DE_7,   DE_8,   DE_9,   DE_0,   DE_SS,  DE_ACUT,KC_BSPC,KC_DEL ,        KC_PGUP,
  KC_TAB, DE_Q,   DE_W,   DE_E,   DE_R,   DE_T,   DE_Z,   DE_U,   DE_I,   DE_O,   DE_P,   DE_UE,  DE_PLUS,XXXXXXX,                KC_PGDN,
  ESCTRL, DE_A,   DE_S,   DE_D,   DE_F,   DE_G,   DE_H,   DE_J,   DE_K,   DE_L,   DE_OE,  DE_AE  ,DE_HASH,KC_ENT,
  KC_LSFT,DE_LESS,DE_Y,   DE_X,   DE_C,   DE_V,   DE_B,   DE_N,   DE_M,   DE_COMM,DE_DOT, DE_MINS,KC_LEAD,KC_RSFT,        KC_UP,
  KC_LOCK,KC_LGUI,KC_LALT,KC_HYPR,        KC_SPC, KC_ENT,                         KC_ALGR,KC_MEH, FUNC   ,ALBHED ,KC_LEFT,KC_DOWN,KC_RGHT),

/* Al Bhed. */
[_ALBHED] = LAYOUT(
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,
  _______,DE_W,   DE_F,   DE_A,   DE_N,   DE_D,   DE_O,   DE_I,   DE_E,   DE_U,   DE_B,   _______,_______,XXXXXXX,                _______,
  _______,DE_Z,   DE_C,   DE_T,   DE_V,   DE_K,   DE_R,   DE_Y,   DE_G,   DE_M,   _______,_______,_______,_______,
  _______,_______,DE_W,   DE_Q,   DE_L,   DE_J,   DE_P,   DE_H,   DE_S,   _______,_______,_______,_______,_______,        _______,
  _______,_______,_______,_______,        _______,_______,                        _______,_______,_______,BASE   ,_______,_______,_______),

/* Keymap _FL: Function Layer */
[_FUNC] = LAYOUT(
  _______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_MUTE,KC_MUTE,       KC_VOLU,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,XXXXXXX,                KC_VOLD,
  _______,_______,_______,_______,_______,_______,_______,KC_MPRV,KC_MSTP,KC_MPLY,KC_MNXT,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_PGUP,
  _______,_______,_______,_______,        _______,_______,                        _______,_______,BASE   ,_______,KC_HOME,KC_PGDN,KC_END),

/* GOD: Control layer */
[_GOD] = LAYOUT(
  BL_STEP,RGB_M_P,RGB_M_B,RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,RGB_M_X,RGB_M_G,_______,_______,_______,_______,_______,RGB_TOG,        RGB_VAI,
  BASE   ,_______,_______,_______,RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,                RGB_VAD,
  _______,RGB_M_R,RGB_M_SN,_______,_______,_______,_______,_______,RGB_M_K,_______,_______,_______,_______,_______,
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        RGB_SAI,
  _______,_______,_______,_______,        RGB_MOD,   RGB_MOD,                     _______,_______,_______,_______,RGB_HUD,RGB_SAD,RGB_HUI),
};

void matrix_init_user(void) {
  static bool initialized = false;
  if (!initialized){
      rgblight_enable();
      rgblight_mode(4);
      initialized = 1;
      activate_layer(_BASE);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv(rand() % 360, rand() % 255, rand() % 255);
  } else {
    rgblight_mode(mode);
    rgblight_sethsv(h, s, v);
  }

  return process_custom_keycodes(keycode, record);
}

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    leader_ctrl_alt_del();
    leader_utility();
    leader_nkro();
    leader_god();
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _BASE:
      mode = RGBLIGHT_MODE_RAINBOW_SWIRL;
      break;
    case _ALBHED:
      mode = 1;
      h = 42;
      s = 242;
      v = 255;
      break;
    case _FUNC:
      mode = 1;
      h = 209;
      s = 244;
      v = 255;
      break;
    case _GOD:
      mode = 1;
      h = 189;
      s = 71;
      v = 100;
      break;
  }

  rgblight_mode(mode);
  rgblight_sethsv(h, s, v);

  return state;
}
/* vim: set nowrap : */
