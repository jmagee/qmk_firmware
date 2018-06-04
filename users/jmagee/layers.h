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

#include <quantum.h>

typedef enum {
  _BASE = 0,

#ifdef USE_ALBHED_LAYER
  _ALBHED,
#endif

#ifdef USE_NUMPAD_LAYER
  _NUMPAD,
#endif

#ifdef USE_SYMBOLS_LAYER
  _SYMBOLS,
#endif

#ifdef USE_NAVI_LAYER
  _NAVI,
#endif

#ifdef USE_MOUSER_LAYER
  _MOUSER,
#endif

#ifdef USE_FUNC_LAYER
  _FUNC,
#endif

#ifdef USE_GOD_LAYER
  _GOD,
#endif

  _MAX_LAYER      /* Not an actual layer; must appear last in the enum. */
} Layers;

/* Types to manage layer state. */
typedef enum {
  Layer_off = 0,
  Layer_on,
  Layer_persistant
} Layer_state;

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
} Custom_keycodes;

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

/* Turn off all transient layers.
 * A transient layer is just a non-persistant layer.
 * Only one transient layer can be enabled at a time. */
void transient_layers_off(Layer_state layer_map[_MAX_LAYER]);

/* Switch from one transient layer to another.  This is essentially a mode switch. */
void switch_transient_layer(Layer_state layer_map[_MAX_LAYER], Layers layer);

/* Activate a layer. */
void activate_layer(Layers layer);

/* Check if a keycode corrosponds to a layer.
 * E.g. _BASE -> BASE
 */
bool is_layer_keycode(Custom_keycodes kc);

/* Convert a keycode into a layer.
 * pre-condition: is_layer_keycode() must return true.
 */
Layers keycode_to_layer(Custom_keycodes kc);
