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

#endif // JMAGEE_LEADER_H
