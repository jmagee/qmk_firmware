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

#ifndef JMAGEE_LEADER_H
#define JMAGEE_LEADER_H

#include "quantum.h"

LEADER_EXTERNS();

/* FIXME: Move these chord routines elsewhere. */
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

/* leader_fkeys - Create leader mappings for each function key (f1 - f24)
 * corrosponding to a virtual numpad on a QWERTY layout.  Logically,
 * leader f 1 -> F1
 * leader f 2 -> F2
 * ...
 * leader f 2 4 -> F24
 *
 * Where the virtual numpad are keys:
 *   uio
 *   jkl
 *   m,.
 *
 * Thus 'leader f m k' would be F15.
 */
void leader_fkeys(void);

/* leader_ctrl_alt_del - Create a leader mapping for ctrl-alt-del.
 * leader c a d
 */
void leader_ctrl_alt_del(void);

/* leader_virtual_consoles - Create leader mappings for switching virtual consoles
 * in Linux.  E.g. Ctrl+Alt+F1 - Ctrll+Alt+F12.
 */
void leader_virtual_consoles(void);

/* leader_xmonad - Create leader mappings for xmonad chords.
 * The mappings are not complete - only those that I commonly want to use
 * as leader mappings are here. */
void leader_xmonad(void);

#endif // JMAGEE_LEADER_H
