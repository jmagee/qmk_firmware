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
#include <assert.h>

extern keymap_config_t keymap_config;

typedef enum {
  _QWERTY = 0,
  _ALBHED,
  _NUMPAD,
  _SYMBOLS,
  _NAVI,
  _MOUSER,
  _MAX_LAYER      /* Not an actual layer; must appear last in the enum. */
} Planck_layers;

/* Types to manage layer state. */
typedef enum {
  Layer_off = 0,
  Layer_on,
  Layer_persistant
} Layer_state;

typedef enum {
  QWERTY = SAFE_RANGE,
  ALBHED,
  NUMPAD,
  SYMBOLS,
  NAVI,
  MOUSER,
  SQUEEK
} Planck_keycodes;

_Static_assert(QWERTY - SAFE_RANGE == _QWERTY, "Keycode cannot be converted to layer.");
_Static_assert(ALBHED - SAFE_RANGE == _ALBHED, "Keycode cannot be converted to layer.");
_Static_assert(NUMPAD - SAFE_RANGE == _NUMPAD, "Keycode cannot be converted to layer.");
_Static_assert(SYMBOLS - SAFE_RANGE == _SYMBOLS, "Keycode cannot be converted to layer.");
_Static_assert(NAVI - SAFE_RANGE == _NAVI, "Keycode cannot be converted to layer.");
_Static_assert(MOUSER - SAFE_RANGE == _MOUSER, "Keycode cannot be converted to layer.");

/* Smart toggle - toggle layer on tap, momentarily activate on hold. */
#define ST(layer, layer_code) LT(layer, layer_code)
#define T_NUMPAD ST(_NUMPAD, NUMPAD)
#define T_SYM    ST(_SYMBOLS, SYMBOLS)
#define T_NAVI   ST(_NAVI, NAVI)

/* Escape on tap, control on hold.*/
#define ESCTRL   CTL_T(KC_ESC)

/* NKRO Control */
typedef enum {
  NK_ENABLE = 0,
  NK_DISABLE,
  NK_TOGGLE
} NK_Control;

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
  {ESCTRL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
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
  {ESCTRL,  KC_Y,    KC_C,    KC_T,    KC_V,    KC_K,    KC_R,    KC_Z,    KC_G,    KC_M,    KC_SCLN, KC_QUOT},
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

/* Mouser.
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |  C3  |      |      |      |      |      |      |Leader|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  C4  |  C1  |      |  <-  | Down | Up   |  ->  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  C2  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSER] = {
  {_______, _______, _______, _______, KC_BTN3, _______, _______, _______, _______, _______, _______, KC_LEAD},
  {_______, SQUEEK , _______, KC_BTN4, KC_BTN1, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______},
  {_______, _______, _______, _______, KC_BTN2, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},
};

/* Turn off all transient layers.
 * A transient layer is just a non-persistant layer.
 * Only one transient layer can be enabled at a time. */
static void transient_layers_off(Layer_state layer_map[_MAX_LAYER]) {
  for (Planck_layers i = 0; i < _MAX_LAYER; ++i) {
    if (layer_map[i] == Layer_on) {
      layer_map[i] = Layer_off;
      layer_off(i);
    }
  }
}

/* Switch from one transient layer to another.  This is essentially a mode switch. */
static void switch_transient_layer(Layer_state layer_map[_MAX_LAYER], Planck_layers layer) {
  transient_layers_off(layer_map);
  layer_on(layer);
  layer_map[layer] = Layer_on;
}

/* Activate a layer. */
static void activate_layer(Planck_layers layer) {
  static Layer_state layer_map[_MAX_LAYER] = {Layer_off};
  switch (layer) {
    case _QWERTY:
      print("mode just switched to qwerty and this is a huge string\n");
      set_single_persistent_default_layer(_QWERTY);
      layer_map[_QWERTY] = Layer_persistant;
      return;
    case _ALBHED:
      print("Famlusa\n");
      switch_transient_layer(layer_map, _ALBHED);
      return;
    case _NUMPAD:
    case _SYMBOLS:
    case _NAVI:
    case _MOUSER:
      switch_transient_layer(layer_map, layer);
      return;
    case _MAX_LAYER:
      assert(0 && "_MAX_LAYER cannot be activated.");
      return;
  }
  assert(0 && "Unreachable!");
}

static bool is_layer_keycode(Planck_keycodes kc) {
  return kc >= QWERTY && kc <= MOUSER;
}

static Planck_layers keycode_to_layer(Planck_keycodes kc) {
  assert(kc <= _MAX_LAYER + SAFE_RANGE && "Keycode cannot be converted to layer");
  return kc - SAFE_RANGE;
}

uint32_t layer_state_set_user(uint32_t state) {
  return state;
#if 0
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
#endif
}

/* enable_nkro - Turn on, off, or toggle NKRO. */
static void enable_nkro(NK_Control mode) {
  if (!eeconfig_is_enabled()) {
    eeconfig_init();
  }
  keymap_config.raw = eeconfig_read_keymap();
  switch (mode) {
    case NK_ENABLE:
      keymap_config.nkro = true;
      break;
    case NK_DISABLE:
      keymap_config.nkro = false;
      break;
    case NK_TOGGLE:
      keymap_config.nkro = !keymap_config.nkro;
      break;
  }
  eeconfig_update_keymap(keymap_config.raw);
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
        register_code(lookup[current]);
      }
      return false;
    }
  }
  return true;
}

LEADER_EXTERNS();

/* leader_fkeys - Create leader mappings for each function key (f1 - f24)
 * corrosponding to a QWERTY layout, starting at Q.  Thus
 * leader f q -> F1
 * leader f w -> F2
 * ...
 * leader f v -> F24
 */
static void leader_fkeys(void) {
  enum { N = 24 };
  static const uint8_t leader_pairs[N][2] = {
    {KC_Q, KC_F1}, {KC_W, KC_F2}, {KC_E, KC_F3}, {KC_R, KC_F4}, {KC_T, KC_F5}, {KC_U, KC_F6},
    {KC_I, KC_F7}, {KC_O, KC_F8}, {KC_P, KC_F9}, {KC_A, KC_F10}, {KC_S, KC_F11}, {KC_D, KC_F12},
    {KC_F, KC_F13}, {KC_G, KC_F14}, {KC_H, KC_F15}, {KC_J, KC_F16}, {KC_K, KC_F17}, {KC_L, KC_F18},
    {KC_SCLN, KC_F19}, {KC_QUOT, KC_F20}, {KC_Z, KC_F21}, {KC_X, KC_F22}, {KC_C, KC_F23}, {KC_V, KC_F24},
  };

  for (uint8_t i = 0; i < N; ++i) {
    SEQ_TWO_KEYS(KC_F, leader_pairs[i][0]) {
      register_code(leader_pairs[i][1]);
      unregister_code(leader_pairs[i][1]);
    }
  }
}

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    leader_fkeys();

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
