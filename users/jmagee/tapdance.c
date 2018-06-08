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

#include "tapdance.h"
#include "chord.h"
#include <quantum.h>

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
static void secret_unlock(void) {
  /* noop */
}
#endif

#ifndef AUTO_LOCK_TIME
#define AUTO_LOCK_TIME (60U * 60U * 1000U) /* 1 hour */
#endif

typedef enum {
  Unlocked,
  Short_lock,   /* A short lock - this can "auto-unlocked" */
  Long_lock,    /* Long lock - no choice but to manually unlock via a human */
} Lock_t;

typedef struct {
  Lock_t screen_lock;
  uint32_t time_of_lock;
} locker_t;

static locker_t sl = {Unlocked, 0U};

static void update_lock_state(Lock_t new_state) {
  switch (sl.screen_lock) {
    case Unlocked:
      if (new_state == Short_lock) {
        dprintf("Unlocked -> Short_lock\n");
      } else if (new_state == Long_lock) {
        dprintf("Unlocked -> Long_lock\n");
      } else { /* new_state == Unlocked */
        break;
      }
      chord2(KC_LALT, KC_X);
      sl.screen_lock = new_state;
      sl.time_of_lock = timer_read32();
      break;
    case Short_lock:
      if (new_state == Unlocked) {
        dprintf("Short_lock -> Unlocked\n");
        secret_unlock();
      } else if (new_state == Long_lock) {
        dprintf("Short_lock -> Long_lock\n");
        sl.time_of_lock = timer_read32();
      } else { /* new_state = Short_lock */
        break;
      }
      sl.screen_lock = new_state;
      break;
    case Long_lock:
      dprintf("Cannot unlock or demote \"Long_lock\"");
      break;
  }
}

void lock_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      /* emit short term lock */
      update_lock_state(Short_lock);
    } else {
      /* emit long term lock on hold */
      update_lock_state(Long_lock);
    }
  } else if (state->count == 2) {
    update_lock_state(Unlocked);
  }
}

void expire_short_lock(void) {
  if (timer_elapsed32(sl.time_of_lock) > AUTO_LOCK_TIME) {
    update_lock_state(Long_lock);
  }
}
