/* Copyright 2018 Joshua Magee
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

#pragma once

#include "layers.h"
#include <quantum.h>

typedef enum {
  BASE = SAFE_RANGE,

#ifdef USE_ALBHED_LAYER
  ALBHED,
#endif

#ifdef USE_NUMPAD_LAYER
  NUMPAD,
#endif

#ifdef USE_SYMBOLS_LAYER
  SYMBOLS,
#endif

#ifdef USE_NAVI_LAYER
  NAVI,
#endif

#ifdef USE_MOUSER_LAYER
  MOUSER,
#endif

#ifdef USE_FUNC_LAYER
  FUNC,
#endif

#ifdef USE_GOD_LAYER
  GOD,
#endif

  END_OF_LAYERS, /* Not an actual keycode; must appear after the last layer,
                  * but other custom keycodes may appear after. */
  SQUEEK,
  KC_HEX,
} Custom_keycode;

_Static_assert(BASE - SAFE_RANGE == _BASE, "Keycode cannot be converted to layer.");
#ifdef USE_ALBHED_LAYER
_Static_assert(ALBHED - SAFE_RANGE == _ALBHED, "Keycode cannot be converted to layer.");
#endif
#ifdef USE_NUMPAD_LAYER
_Static_assert(NUMPAD - SAFE_RANGE == _NUMPAD, "Keycode cannot be converted to layer.");
#endif
#ifdef USE_SYMBOLS_LAYER
_Static_assert(SYMBOLS - SAFE_RANGE == _SYMBOLS, "Keycode cannot be converted to layer.");
#endif
#ifdef USE_NAVI_LAYER
_Static_assert(NAVI - SAFE_RANGE == _NAVI, "Keycode cannot be converted to layer.");
#endif
#ifdef USE_MOUSER_LAYER
_Static_assert(MOUSER - SAFE_RANGE == _MOUSER, "Keycode cannot be converted to layer.");
#endif
#ifdef USE_FUNC_LAYER
_Static_assert(FUNC - SAFE_RANGE == _FUNC, "Keycode cannot be converted to layer.");
#endif
#ifdef USE_GOD_LAYER
_Static_assert(GOD - SAFE_RANGE == _GOD, "Keycode cannot be converted to layer.");
#endif

/* Smart toggle - toggle layer on tap, momentarily activate on hold. */
#define ST(layer, layer_code) LT(layer, layer_code)

/* Smart toggles for specific layout / keycode combos. */
#ifdef USE_NUMPAD_LAYER
#  define T_NUMPAD ST(_NUMPAD, NUMPAD)
#endif
#ifdef USE_SYMBOLS_LAYER
#  define T_SYM    ST(_SYMBOLS, SYMBOLS)
#endif
#ifdef USE_NAVI_LAYER
#  define T_NAVI   ST(_NAVI, NAVI)
#endif
#ifdef USE_MOUSER_LAYER
#  define T_MOUSE  ST(_MOUSER, MOUSER)
#endif
#ifdef USE_ALBHED_LAYER
#  define T_BHED   ST(_ALBHED, ALBHED)
#endif
#ifdef USE_FUNC_LAYER
#  define T_FUNC   ST(_FUNC, FUNC)
#endif
#ifdef USE_GOD_LAYER
#  define T_GOD    ST(_GOD, GOD)
#endif

/* Escape on tap, control on hold.*/
#define ESCTRL   CTL_T(KC_ESC)

/* Check if a keycode corrosponds to a layer.
 * E.g. _BASE -> BASE
 */
bool is_layer_keycode(Custom_keycode kc);

/* Convert a keycode into a layer.
 * pre-condition: is_layer_keycode() must return true.
 */
Layers keycode_to_layer(Custom_keycode kc);

/* Process custom keycodes and perform their associated actions.
 * TODO: Add a _user version of this? */
bool process_custom_keycodes(Custom_keycode kc, keyrecord_t *record);
