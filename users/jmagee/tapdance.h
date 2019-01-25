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
#include <quantum.h>

typedef enum {
  TD_LCK = 0
} Tapdance_keycodes;

#ifdef  USE_XMONAD_KEYS
typedef enum {
  KC_X1 = 0,   /* XMonad desktop switches */
  KC_X2,
  KC_X3,
  KC_X4,
  KC_X5,
  KC_X6,
  KC_X7,
  KC_X8
} XTapdance_keycodes;
#endif

typedef enum {
  Unlocked,
  Short_lock,   /* A short lock - this can "auto-unlocked" */
  Long_lock,    /* Long lock - no choice but to manually unlock via a human */
} Lock_t;

/* Tap dance routine for locking the screen.
 * 1 Tap: Lock
 * 2 taps: Unlock
 * 1 long tap (hold): Lock the screen and don't allow it to be unlocked via 2 taps. */
void lock_dance(qk_tap_dance_state_t *state, void *user_data);

#ifdef USE_XMONAD_KEYS
void x_dance(qk_tap_dance_state_t *state, void *user_data);
#endif

/* Upgrade a Short_lock to a Long_lock if a certain amount of time has elapsed. */
void expire_short_lock(void);

/* Perform side effects on lock state changes.
 * This is called whenever a lock state changes. */
void lock_state_changed_user(Lock_t lock_state);
