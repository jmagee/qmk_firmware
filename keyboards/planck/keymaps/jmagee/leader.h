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
 * corrosponding to a QWERTY layout, starting at Q.  Thus
 * leader f q -> F1
 * leader f w -> F2
 * ...
 * leader f v -> F24
 */
void leader_fkeys(void);

#endif // JMAGEE_LEADER_H
