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

#include "leader.h"

#include "chord.h"
#include "layers.h"
#include "nkro.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
PROGMEM const char secrets[][32] = { "a" };

enum {
  SECRET_W = 0,
  SECRET_D,
  SECRET_P
};
#endif

enum { N_FKEYS = 24 };
PROGMEM static const uint8_t fkeys[N_FKEYS] = {
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
  KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20,
  KC_F21, KC_F22, KC_F23, KC_F24
};

PROGMEM static const uint8_t digits[10] = {
  /* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 on QWERTY layer */
  KC_N, KC_M, KC_COMM, KC_DOT, KC_J, KC_K, KC_L, KC_U, KC_I, KC_O
};

/* Helper to map F-key based sequences to a virtual numpad.
 * leader_key is simply a keycode.
 * fkey_map is a function that accepts a keycode argument (one of the
 * F keys) and does something with it (e.g. register keypress events)
 * */
static void f1_to_vnumpad(uint8_t leading_key, void (*fkey_map)(uint8_t)) {
  uint8_t f = 0;

  for (uint8_t i = 1; i < 25; ++i) {
    if (i < 10) {
      /* F1 - F9 */
      SEQ_TWO_KEYS(leading_key, digits[i]) {
        fkey_map(fkeys[f]);
      }
    } else {
      /* F10 - F24 */
      uint8_t d1 = i < 20 ? 1 : 2;
      SEQ_THREE_KEYS(leading_key, digits[d1], digits[i % 10]) {
        fkey_map(fkeys[f]);
      }
    }
    ++f;
  }
}

static void ctrl_alt_fkey_map(uint8_t f) {
  chord3(KC_LCTRL, KC_LALT, f);
}

void leader_fkeys(void) {
  f1_to_vnumpad(KC_F, chord1);
}

void leader_ctrl_alt_del(void) {
  SEQ_THREE_KEYS(KC_C, KC_A, KC_D) {
    chord3(KC_LCTRL, KC_LALT, KC_DELETE);
  }
}

void leader_virtual_consoles(void) {
  f1_to_vnumpad(KC_V, ctrl_alt_fkey_map);
}

void leader_xmonad(void) {
  /* launch a terminal */
  SEQ_TWO_KEYS(KC_X, KC_ENT) {
    chord3(KC_LALT, KC_LSFT, KC_ENT);
  }

  /* launch a dmenu */
  SEQ_TWO_KEYS(KC_X, KC_P) {
    chord2(KC_LALT, KC_P);
  }

  /* lock the screen */
  SEQ_TWO_KEYS(KC_X, KC_X) {
    chord2(KC_LALT, KC_X);
  }

  /* close window */
  SEQ_TWO_KEYS(KC_X, KC_C) {
    chord2(KC_LALT, KC_C);
  }

  /* cycle layout */
  SEQ_TWO_KEYS(KC_X, KC_SPC) {
    chord2(KC_LALT, KC_SPC);
  }

  /* Toggle the status bar (e.g. xmobar or similiar) */
  SEQ_TWO_KEYS(KC_X, KC_B) {
    chord2(KC_LALT, KC_B);
  }

  /* Start a pomodoro */
  SEQ_TWO_KEYS(KC_X, KC_D) {
    chord2(KC_LALT, KC_D);
  }

  /* quit */
  SEQ_TWO_KEYS(KC_X, KC_Q) {
    chord4(KC_LALT, KC_LSFT, KC_LCTL, KC_Q);
  }

  /* restart */
  SEQ_TWO_KEYS(KC_X, KC_R) {
    chord3(KC_LALT, KC_LSFT, KC_Q);
  }

  /* Switch desktops */
  for (uint8_t i = 1; i < 10; ++i) {
    SEQ_TWO_KEYS(KC_X, digits[i]) {
      chord2(KC_LALT, i);
    }
  }
}

void leader_secret(void) {
  SEQ_TWO_KEYS(KC_S, KC_W) {
    send_string_P(secrets[SECRET_W]);
  }

  SEQ_TWO_KEYS(KC_S, KC_D) {
    send_string_P(secrets[SECRET_D]);
  }

  SEQ_TWO_KEYS(KC_S, KC_S) {
    send_string_P(secrets[SECRET_P]);
  }
}

void leader_utility(void) {
  SEQ_FIVE_KEYS(KC_F, KC_L, KC_A, KC_S, KC_H) {
    register_code16(RESET);
    unregister_code16(RESET);
  }
}

void leader_nkro(void) {
  SEQ_ONE_KEY(KC_N) {
    enable_nkro(NK_TOGGLE);
  }
}

void leader_god(void) {
#ifdef USE_GOD_LAYER
  SEQ_THREE_KEYS(KC_G, KC_O, KC_D) {
    activate_layer(_GOD);
  }
#endif
}

#if defined(AUDIO_ENABLE)
extern bool music_activated;
#endif

void leader_music(void) {
#if defined(AUDIO_ENABLE)
  SEQ_TWO_KEYS(KC_SPACE, KC_SPACE) {
    music_activated ? music_off() : music_on();
  }

  SEQ_TWO_KEYS(KC_TAB, KC_TAB) {
    music_mode_cycle();
  }
#endif
}
