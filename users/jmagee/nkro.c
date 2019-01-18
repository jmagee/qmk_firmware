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

#include "nkro.h"
#include "passert.h"
#include <quantum.h>

void enable_nkro(NK_Control mode) {
  passert((mode == NK_ENABLE || mode == NK_DISABLE || mode == NK_TOGGLE) && "Invalid mode");
  if (!eeconfig_is_enabled()) {
    eeconfig_init();
  }
  keymap_config.raw = eeconfig_read_keymap();
  switch (mode) {
    case NK_ENABLE:
      keymap_config.nkro = true;
      break;
    case NK_DISABLE:
      keymap_config.nkro = false;
      break;
    case NK_TOGGLE:
      keymap_config.nkro = !keymap_config.nkro;
      break;
  }

  if (keymap_config.nkro) {
    print("NKRO on");
  } else {
    print("NKRO off");
  }
  eeconfig_update_keymap(keymap_config.raw);
}
