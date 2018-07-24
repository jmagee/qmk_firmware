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

#include "keycodes.h"
#include "layers.h"
#include "mouse.h"
#include "passert.h"
#include <quantum.h>

bool is_layer_keycode(Custom_keycode kc) {
  return kc >= BASE && kc < END_OF_LAYERS;
}

Layers keycode_to_layer(Custom_keycode kc) {
  passert(kc <= _MAX_LAYER + SAFE_RANGE && "Keycode cannot be converted to layer");
  return kc - SAFE_RANGE;
}

bool process_custom_keycodes(Custom_keycode keycode, keyrecord_t *record) {
  static uint16_t press_timer = 0;
  switch (keycode) {
    case BASE ... END_OF_LAYERS:
      passert(is_layer_keycode(keycode) && "Not a layer keycode");
      if (record->event.pressed) {
        press_timer = timer_read();
        activate_layer(keycode_to_layer(keycode));
        return false;
      } else if (timer_elapsed(press_timer) >= TAPPING_TERM) {
        deactivate_layer(keycode_to_layer(keycode));
        return false;
      }
    case SQUEEK:
      /* Toggle through the mouse acceleration speeds. */
      if (record->event.pressed) {
        squeek();
        return false;
      }
    case KC_HEX:
      if (record->event.pressed) {
        SEND_STRING("0x");
        return false;
      }
  }
  return true;
}
