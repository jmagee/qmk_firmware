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

#ifndef JMAGEE_LAYERS_H
#define JMAGEE_LAYERS_H

#include <quantum.h>

typedef enum {
  _QWERTY = 0,
  _ALBHED,
  _NUMPAD,
  _SYMBOLS,
  _NAVI,
  _MOUSER,
  _MAX_LAYER      /* Not an actual layer; must appear last in the enum. */
} Layers;

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
} Custom_keycodes;

_Static_assert(QWERTY - SAFE_RANGE == _QWERTY, "Keycode cannot be converted to layer.");
_Static_assert(ALBHED - SAFE_RANGE == _ALBHED, "Keycode cannot be converted to layer.");
_Static_assert(NUMPAD - SAFE_RANGE == _NUMPAD, "Keycode cannot be converted to layer.");
_Static_assert(SYMBOLS - SAFE_RANGE == _SYMBOLS, "Keycode cannot be converted to layer.");
_Static_assert(NAVI - SAFE_RANGE == _NAVI, "Keycode cannot be converted to layer.");
_Static_assert(MOUSER - SAFE_RANGE == _MOUSER, "Keycode cannot be converted to layer.");

/* Turn off all transient layers.
 * A transient layer is just a non-persistant layer.
 * Only one transient layer can be enabled at a time. */
void transient_layers_off(Layer_state layer_map[_MAX_LAYER]);

/* Switch from one transient layer to another.  This is essentially a mode switch. */
void switch_transient_layer(Layer_state layer_map[_MAX_LAYER], Layers layer);

/* Activate a layer. */
void activate_layer(Layers layer);

/* Check if a keycode corrosponds to a layer.
 * E.g. _QWERTY -> QWERTY.
 */
bool is_layer_keycode(Custom_keycodes kc);

/* Convert a keycode into a layer.
 * pre-condition: is_layer_keycode() must return true.
 */
Layers keycode_to_layer(Custom_keycodes kc);

#endif
