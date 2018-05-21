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

/* Helpers to register a key chord, i.e. mod+mod+key */

/* This one is really just a keypress */
#define CHORD1(key) do { \
  register_code(key); \
  unregister_code(key); \
} while (0);

#define CHORD2(mod, key) do { \
  register_code(mod); \
  register_code(key); \
  unregister_code(key); \
  unregister_code(mod); \
} while (0);

#define CHORD3(mod1, mod2, key) do { \
  register_code(mod1); \
  register_code(mod2); \
  register_code(key); \
  unregister_code(key); \
  unregister_code(mod2); \
  unregister_code(mod1); \
} while (0);

#define CHORD4(mod1, mod2, mod3, key) do { \
  register_code(mod1); \
  register_code(mod2); \
  register_code(mod3); \
  register_code(key); \
  unregister_code(key); \
  unregister_code(mod3); \
  unregister_code(mod2); \
  unregister_code(mod1); \
} while (0);
