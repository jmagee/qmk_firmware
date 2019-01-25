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
#include "keycodes.h"
#include "passert.h"
#include <quantum.h>

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
static void secret_unlock(void) {
  /* noop */
}
#endif

#ifndef AUTO_LOCK_TIME
#define AUTO_LOCK_TIME (60U * 60U * (uint32_t)1000U) /* 1 hour */
#endif

typedef struct {
  Lock_t screen_lock;
  uint32_t time_of_lock;
} locker_t;

static locker_t sl = {Unlocked, 0U};

static void reset_lock_state(void) {
  dprintf("Reset lock state to unlocked.\n");
  lock_state_changed_user(Unlocked);
  sl.screen_lock = Unlocked;
}

static void update_lock_state(Lock_t new_state) {
  switch (sl.screen_lock) {
    case Unlocked:
      if (new_state == Short_lock) {
        dprintf("Unlocked -> Short_lock\n");
        lock_state_changed_user(new_state);
      } else if (new_state == Long_lock) {
        dprintf("Unlocked -> Long_lock\n");
        lock_state_changed_user(new_state);
      } else { /* new_state == Unlocked */
        dprintf("Noop: Unlocked -> Unlocked\n");
        break;
      }
      chord2(KC_LALT, KC_X);
      sl.screen_lock = new_state;
      sl.time_of_lock = timer_read32();
      break;
    case Short_lock:
      if (new_state == Unlocked) {
        dprintf("Short_lock -> Unlocked\n");
        lock_state_changed_user(new_state);
        secret_unlock();
      } else if (new_state == Long_lock) {
        dprintf("Short_lock -> Long_lock\n");
        lock_state_changed_user(new_state);
        sl.time_of_lock = timer_read32();
      } else { /* new_state = Short_lock */
        dprintf("Noop: Short_lock -> Short_lock\n");
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
  } else if (state->count == 3) {
    reset_lock_state();
  } else if (state->count == 5) {
    reset_keyboard();
  }
}

#ifdef USE_XMONAD_KEYS
uint8_t x_key_to_n(XTapdance_keycodes kc) {
  passert(kc >= KC_X1 && kc <= KC_X8 && "Not a 'XMonad' key");
  switch (kc) {
  case KC_X1: return KC_1;
  case KC_X2: return KC_2;
  case KC_X3: return KC_3;
  case KC_X4: return KC_4;
  case KC_X5: return KC_5;
  case KC_X6: return KC_6;
  case KC_X7: return KC_7;
  case KC_X8: return KC_8;
  default: break;
  }
  unreachable();
  return 0;
}

void x_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 5) {
    reset_keyboard();
    return;
  }

/*  if (state->keycode < KC_X1 || state->keycode > KC_X8) {*/
    /*dprintf("x_dance used with unexpected key: %d\n", state->keycode);*/
    /*return;*/
  /*}*/

  if (state->count == 1) {
    chord2(KC_LALT, x_key_to_n(state->keycode));
  } else if (state->count == 2) {
    chord3(KC_LALT, KC_LSFT, x_key_to_n(state->keycode));
  }
}
#endif

void expire_short_lock(void) {
  if (sl.screen_lock == Short_lock &&
      timer_elapsed32(sl.time_of_lock) > AUTO_LOCK_TIME) {
    dprintf("Locked at time = %u\n", sl.time_of_lock);
    dprintf("AutoLock time = %u\n", AUTO_LOCK_TIME);
    dprintf("Elapsed lock time = %u\n", timer_elapsed32(sl.time_of_lock));
    update_lock_state(Long_lock);
  }
}

__attribute__((weak))
void lock_state_changed_user(Lock_t lock_state) {
}
