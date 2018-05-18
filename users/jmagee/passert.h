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

#ifdef NO_DEBUG
#define passert(expr) ((void)(expr))
#define unreachable(expr) __builtin_unreachable()

#else

void passert_fail(const char *assertion, const char *file, unsigned int line, const char *func);
void unreachable_fail(const char *file, unsigned int line, const char *func);

/* Pseudo assert: Print a debug message like assert, but don't actually terminate the program. */
#define passert(expr) \
  ((expr) \
   ? (void)(0) \
   : passert_fail(#expr, __FILE__, __LINE__, __func__))

/* Print a debug message if unreachable code is reached.
 * If compiled with NDEBUG, then this becomes a hint to the optimizer. */
#define unreachable() unreachable_fail(__FILE__, __LINE__, __func__)

#endif /* NDEBUG */
