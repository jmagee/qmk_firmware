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

/* Turn off all transient layers.
 * A transient layer is just a non-persistant layer.
 * Only one transient layer can be enabled at a time. */
void transient_layers_off(Layer_state layer_map[_MAX_LAYER]);

/* Switch from one transient layer to another.  This is essentially a mode switch. */
void switch_transient_layer(Layer_state layer_map[_MAX_LAYER], Layers layer);

/* Activate a layer. */
void activate_layer(Layers layer);
