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

#include <stdint.h>

/* Helpers to register a key chord, i.e. mod+mod+key */

/* This one is really just a keypress */
void chord1(uint8_t key);

void chord2(uint8_t mod, uint8_t key);

void chord3(uint8_t mod1, uint8_t mod2, uint8_t key);

void chord4(uint8_t mod1, uint8_t mod2, uint8_t mod3, uint8_t key);

void meh_chord(uint8_t key);
