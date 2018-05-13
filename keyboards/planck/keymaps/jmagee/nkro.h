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

#ifndef JMAGEE_NKRO_H
#define JMAGEE_NKRO_H

/* NKRO Control */
typedef enum {
  NK_DISABLE = 0,
  NK_ENABLE,
  NK_TOGGLE
} NK_Control;

/* enable_nkro - Turn on, off, or toggle NKRO. */
void enable_nkro(NK_Control mode);

#endif /* JMAGEE_NKRO_H */
