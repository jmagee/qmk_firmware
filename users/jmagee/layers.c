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
#include "mouse.h"
#include "passert.h"
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
    case _BASE:
      print("mode just switched to BASE and this is a huge string\n");
      set_single_persistent_default_layer(_BASE);
      layer_map[_BASE] = Layer_persistant;
      return;
#ifdef USE_ALBHED_LAYER
    case _ALBHED:
      print("Famlusa\n");
      switch_transient_layer(layer_map, _ALBHED);
      return;
#endif
#ifdef USE_NUMPAD_LAYER
    case _NUMPAD:
#endif
#ifdef USE_SYMBOLS_LAYER
    case _SYMBOLS:
#endif
#ifdef USE_NAVI_LAYER
    case _NAVI:
#endif
#ifdef USE_MOUSER_LAYER
    case _MOUSER:
#endif
#ifdef USE_FUNC_LAYER
    case _FUNC:
#endif
#ifdef USE_GOD_LAYER
    case _GOD:
#endif
      switch_transient_layer(layer_map, layer);
      return;
    case _MAX_LAYER:
      passert(0 && "_MAX_LAYER cannot be activated.");
      return;
  }
  unreachable();
}

bool is_layer_keycode(Custom_keycodes kc) {
  return kc >= BASE && kc < END_OF_LAYERS;
}

Layers keycode_to_layer(Custom_keycodes kc) {
  passert(kc <= _MAX_LAYER + SAFE_RANGE && "Keycode cannot be converted to layer");
  return kc - SAFE_RANGE;
}

bool process_custom_keycodes(Custom_keycodes keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE ... END_OF_LAYERS:
      return true;
    case SQUEEK:
      /* Toggle through the mouse acceleration speeds. */
      if (record->event.pressed) {
        squeek();
      }
      return false;
  }
  return true;
}
