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
#include "chord.h"
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
  static bool layer_key_pressed = false;
  static bool block_toggle = false;
  switch (keycode) {
    case BASE ... END_OF_LAYERS:
      passert(is_layer_keycode(keycode) && "Not a layer keycode");
      if (record->event.pressed) {
        layer_key_pressed = true;
        press_timer = timer_read();
        activate_layer(keycode_to_layer(keycode));
        return false;
      } else if (block_toggle || timer_elapsed(press_timer) >= TAPPING_TERM) {
        layer_key_pressed = false;
        block_toggle = false;
        deactivate_layer(keycode_to_layer(keycode));
        return false;
      }
      block_toggle = false;
      layer_key_pressed = false;
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
    case KC_READ:
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LCTL)) {
          /* Read a message in outlook */
          chord2(KC_RCTRL, KC_Q);
        } else {
          /* Un-read a message in outlook */
          chord2(KC_RCTRL, KC_U);
        }
        return false;
      }
    case KC_ARROW:
      if (record->event.pressed) {
        SEND_STRING("->");
        return false;
      }
    case KC_BIND:
      if (record->event.pressed) {
        SEND_STRING(">>=");
        return false;
      }
  }
  /* If a layer key is pressed at the same time as any other key,
   * it should be considered a hold and not a tap.  This prevents rapid
   * layer+key pressed from being considered a tap. */
  /* TODO: Consider moving this before the switch? */
  if (layer_key_pressed) {
    block_toggle = true;
    dprintf("Blocked toggle\n");
  }

  return true;
}
