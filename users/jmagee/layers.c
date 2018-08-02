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

void transient_layers_off(void) {
  /* Note that the base layer is persistant */
  for (Layers i = 1; i < _MAX_LAYER; ++i) {
    if (IS_LAYER_ON(i)) {
      layer_off(i);
    }
  }
}

void switch_transient_layer(Layers layer) {
  transient_layers_off();
  layer_on(layer);
}

void activate_layer(Layers layer) {
  dprintf("activate layer called\n");
  switch (layer) {
    case _BASE:
      set_single_persistent_default_layer(_BASE);
      transient_layers_off();
      dprintf("return to base layer\n");
      return;
#ifdef USE_ALBHED_LAYER
    case _ALBHED:
      switch_transient_layer(_ALBHED);
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
      dprintf("turned on layer %d\n", layer);
      switch_transient_layer(layer);
      return;
    case _MAX_LAYER:
      passert(0 && "_MAX_LAYER cannot be activated.");
      return;
  }
  unreachable();
}

void deactivate_layer(Layers layer) {
  passert(IS_LAYER_ON(layer) && "Layer is not on");
  layer_off(layer);
  dprintf("turned off layer %d\n", layer);
}
