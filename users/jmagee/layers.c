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

#include "layers.h"
#include <assert.h>
#include <quantum.h>

void transient_layers_off(Layer_state layer_map[_MAX_LAYER]) {
  for (Layers i = 0; i < _MAX_LAYER; ++i) {
    if (layer_map[i] == Layer_on) {
      layer_map[i] = Layer_off;
      layer_off(i);
    }
  }
}

void switch_transient_layer(Layer_state layer_map[_MAX_LAYER], Layers layer) {
  transient_layers_off(layer_map);
  layer_on(layer);
  layer_map[layer] = Layer_on;
}

void activate_layer(Layers layer) {
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

bool is_layer_keycode(Custom_keycodes kc) {
  return kc >= QWERTY && kc <= MOUSER;
}

Layers keycode_to_layer(Custom_keycodes kc) {
  assert(kc <= _MAX_LAYER + SAFE_RANGE && "Keycode cannot be converted to layer");
  return kc - SAFE_RANGE;
}
