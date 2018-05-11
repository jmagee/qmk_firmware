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

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _ALBHED,
  _NUMPAD,
  _SYMBOLS,
  _NAVI,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  ALBHED,
  NUMPAD,
  SYMBOLS,
  NAVI,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

/* Smart toggle - toggle layer on tap, momentarily activate on hold. */
#define ST(layer, layer_code) LT(layer, layer_code)
#define T_NUMPAD ST(_NUMPAD, NUMPAD)
#define T_SYM    ST(_SYMBOLS, SYMBOLS)
#define T_NAVI   ST(_NAVI, NAVI)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Leader|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |EsCtl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |NumPad| Sym  | GUI  | Alt  |Space | Tab  |Bksp  |Enter | Comp | Navi |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {_______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LEAD},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______},
  {T_NUMPAD,T_SYM  , KC_LGUI, KC_LALT, KC_SPC , KC_TAB,  KC_BSPC, KC_ENT,  T_NAVI , _______, _______, _______}
},

/* Al Bhed
 * ,-----------------------------------------------------------------------------------.
 * |xfando|   X  |   F  |   A  |   N  |   D  |   O  |   I  |   E  |   U  |   B  |Leader|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |EsCtl |   Y  |   C  |   T  |   V  |   K  |   R  |   Z  |   G  |   M  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   W  |   Q  |   L  |   J  |   P  |   H  |   S  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |NumPad| Sym  | GUI  | Alt  |Space | Tab  |Bksp  |Enter | Comp |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ALBHED] = {
  {QWERTY , KC_X,    KC_F,    KC_A,    KC_N,    KC_D,    KC_O,    KC_I,    KC_E,    KC_U,    KC_B,    KC_LEAD},
  {KC_ESC,  KC_Y,    KC_C,    KC_T,    KC_V,    KC_K,    KC_R,    KC_Z,    KC_G,    KC_M,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_W,    KC_Q,    KC_L,    KC_J,    KC_P,    KC_H,    KC_S,    KC_COMM, KC_DOT,  KC_SLSH, _______},
  {T_NUMPAD,T_SYM  , KC_LGUI, KC_LALT, KC_SPC , KC_TAB,  KC_BSPC, KC_ENT,  _______, _______, _______, _______}
},

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |QWERTY|  +   |   7  |   8  |   9  |  /   |  +   |   7  |   8  |   9  |  /   |Leader|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  .   |   4  |   5  |   6  |  *   |   .  |   4  |   5  |   6  |  *   |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  0   |   1  |   2  |   3  |  -   |   0  |   1  |   2  |   3  |  -   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = {
  {QWERTY , KC_PLUS, KC_7,    KC_8,    KC_9,    KC_SLSH, KC_PLUS, KC_7,    KC_8,    KC_9,    KC_SLSH, KC_LEAD},
  {_______, KC_DOT,  KC_4,    KC_5,    KC_6,    KC_ASTR, KC_DOT,  KC_4,    KC_5,    KC_6,    KC_ASTR, KC_PLUS},
  {_______, KC_0,    KC_1,    KC_2,    KC_3,    KC_MINS, KC_0,    KC_1,    KC_2,    KC_3,    KC_SLSH, KC_ENT },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |QWERTY|  !   |   @  |  #   |  $   |  %   |   +  |   [  |  ]   |  *   |  \   |Leader|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  &   |      |   {  |   (  |  )   |  }   |  |   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   /  |   _  |  -   |  =   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOLS] = {
  {QWERTY , KC_EXLM, KC_AT,   KC_HASH, KC_DLR , KC_PERC, KC_PLUS, KC_LBRC, KC_RBRC, KC_ASTR, KC_NUBS, KC_LEAD},
  {_______, _______, _______, _______, KC_AMPR, _______, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE, _______},
  {_______, _______, _______, _______, _______, _______, KC_N,    KC_UNDS, KC_MINS, KC_EQL,  _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Navigation
 * This doesn't have keys like HOME, END, and others - I never use those.  I'll add them
 * if/when I need them.
 * ,-----------------------------------------------------------------------------------.
 * |QWERTY|      |      |      | PGUP |      |      |      |      |      |      |Leader|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | PGDN |      |  <-  | Down | Up   |  ->  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVI] = {
  {QWERTY , _______, _______, _______, KC_PGUP, _______, _______, _______, _______, _______, _______, KC_LEAD},
  {_______, _______, _______, _______, KC_PGDN, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = {
  {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
  {XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   DEBUG,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, PLOVER,  _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return state;
#if 0
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
#if 0
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
#endif
    case ALBHED:
      if (record->event.pressed) {
        print("Famlusa\n");
        layer_on(_ALBHED);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        layer_on(_NUMPAD);
      }
      return false;
      break;
    case _SYMBOLS:
      if (record->event.pressed) {
        layer_on(_SYMBOLS);
      }
      return false;
      break;
    case _NAVI:
      if (record->event.pressed) {
        layer_on(_NAVI);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        PORTE &= ~(1<<6);
      } else {
        unregister_code(KC_RSFT);
        PORTE |= (1<<6);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
#if 0
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
#endif
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
#if 0
    case RAISE:
    case LOWER:
      return false;
#endif
    default:
      return true;
  }
}
