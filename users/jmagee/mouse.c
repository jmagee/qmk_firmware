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

#include "mouse.h"
#include "jmagee.h"
#include <quantum.h>

void squeek(void) {
  /* Toggle through the mouse acceleration speeds. */
  static const uint8_t lookup[3] = { KC_ACL0, KC_ACL1, KC_ACL2 };
  static uint8_t current = 0;
  if (++current > 2) {
    current = 0;
  }
  CHORD1(lookup[current]);
}
