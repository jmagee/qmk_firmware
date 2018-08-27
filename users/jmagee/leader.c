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

PROGMEM static const uint8_t digits[10][2] = {
  /* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 on QWERTY layer */
  {KC_N, KC_0},
  {KC_M, KC_1},
  {KC_COMM, KC_2},
  {KC_DOT, KC_3},
  {KC_J, KC_4},
  {KC_K, KC_5},
  {KC_L, KC_6},
  {KC_U, KC_7},
  {KC_I, KC_8},
  {KC_O, KC_9}
};

/* Helper to map F-key based sequences to a virtual numpad.
 * leader_key is simply a keycode.
 * fkey_map is a function that accepts a keycode argument (one of the
 * F keys) and does something with it (e.g. register keypress events)
 * */
static void f1_to_vnumpad(uint8_t leading_key, void (*fkey_map)(uint8_t)) {
#if 0
  uint8_t f = 0;

  for (uint8_t i = 1; i < 25; ++i) {
    if (i < 10) {
      /* F1 - F9 */
      SEQ_TWO_KEYS(leading_key, digits[i][0]) {
        print("F1-F9");
        fkey_map(fkeys[f]);
      }
    } else {
      /* F10 - F24 */
      uint8_t d1 = i < 20 ? 1 : 2;
      SEQ_THREE_KEYS(leading_key, digits[d1][0], digits[i % 10][0]) {
        fkey_map(fkeys[f]);
      }
    }
    ++f;
  }
#endif
  SEQ_TWO_KEYS(leading_key, digits[1][0]) { fkey_map(fkeys[1]); }
  SEQ_TWO_KEYS(leading_key, digits[2][0]) { fkey_map(fkeys[2]); }
  SEQ_TWO_KEYS(leading_key, digits[3][0]) { fkey_map(fkeys[3]); }
  SEQ_TWO_KEYS(leading_key, digits[4][0]) { fkey_map(fkeys[4]); }
  SEQ_TWO_KEYS(leading_key, digits[5][0]) { fkey_map(fkeys[5]); }
  SEQ_TWO_KEYS(leading_key, digits[6][0]) { fkey_map(fkeys[6]); }
  SEQ_TWO_KEYS(leading_key, digits[7][0]) { fkey_map(fkeys[7]); }
  SEQ_TWO_KEYS(leading_key, digits[8][0]) { fkey_map(fkeys[8]); }
  SEQ_TWO_KEYS(leading_key, digits[9][0]) { fkey_map(fkeys[9]); }
  SEQ_THREE_KEYS(leading_key, digits[1][0], digits[0][0]) { fkey_map(fkeys[10]); }
  SEQ_THREE_KEYS(leading_key, digits[1][0], digits[1][0]) { fkey_map(fkeys[11]); }
  SEQ_THREE_KEYS(leading_key, digits[1][0], digits[2][0]) { fkey_map(fkeys[12]); }
}

static void ctrl_alt_fkey_map(uint8_t f) {
  print("Chording ctrl alt fkey\n");
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
    chord3(KC_LALT, KC_LSFT, KC_C);
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

  /* atl tab */
  SEQ_ONE_KEY(KC_TAB) {
    chord2(KC_LALT, KC_TAB);
  }

  /* Switch desktops */
#if 0
  for (int x = 1; x < 9; ++x) {
    SEQ_TWO_KEYS(KC_X, digits[x][0]) {
      chord2(KC_LALT, digits[x][1]);
    }
  }
#endif

  /* For reasons I have not determined, this code does not work if wrapped in a loop.... */
  SEQ_TWO_KEYS(KC_X, digits[1][0]) { chord2(KC_LALT, digits[1][1]); }
  SEQ_TWO_KEYS(KC_X, digits[2][0]) { chord2(KC_LALT, digits[2][1]); }
  SEQ_TWO_KEYS(KC_X, digits[3][0]) { chord2(KC_LALT, digits[3][1]); }
  SEQ_TWO_KEYS(KC_X, digits[4][0]) { chord2(KC_LALT, digits[4][1]); }
  SEQ_TWO_KEYS(KC_X, digits[5][0]) { chord2(KC_LALT, digits[5][1]); }
  SEQ_TWO_KEYS(KC_X, digits[6][0]) { chord2(KC_LALT, digits[6][1]); }
  SEQ_TWO_KEYS(KC_X, digits[7][0]) { chord2(KC_LALT, digits[7][1]); }
  SEQ_TWO_KEYS(KC_X, digits[8][0]) { chord2(KC_LALT, digits[8][1]); }
  SEQ_TWO_KEYS(KC_X, digits[9][0]) { chord2(KC_LALT, digits[9][1]); }

  /* Send to desktops */
  SEQ_THREE_KEYS(KC_X, digits[1][0], digits[1][0]) { chord3(KC_LALT, KC_LSFT, digits[1][1]); }
  SEQ_THREE_KEYS(KC_X, digits[2][0], digits[2][0]) { chord3(KC_LALT, KC_LSFT, digits[2][1]); }
  SEQ_THREE_KEYS(KC_X, digits[3][0], digits[3][0]) { chord3(KC_LALT, KC_LSFT, digits[3][1]); }
  SEQ_THREE_KEYS(KC_X, digits[4][0], digits[4][0]) { chord3(KC_LALT, KC_LSFT, digits[4][1]); }
  SEQ_THREE_KEYS(KC_X, digits[5][0], digits[5][0]) { chord3(KC_LALT, KC_LSFT, digits[5][1]); }
  SEQ_THREE_KEYS(KC_X, digits[6][0], digits[6][0]) { chord3(KC_LALT, KC_LSFT, digits[6][1]); }
  SEQ_THREE_KEYS(KC_X, digits[7][0], digits[7][0]) { chord3(KC_LALT, KC_LSFT, digits[7][1]); }
  SEQ_THREE_KEYS(KC_X, digits[8][0], digits[8][0]) { chord3(KC_LALT, KC_LSFT, digits[8][1]); }
  SEQ_THREE_KEYS(KC_X, digits[9][0], digits[9][0]) { chord3(KC_LALT, KC_LSFT, digits[9][1]); }

  /* Maybe this should be moved to something like leader_windows ?*/
  SEQ_TWO_KEYS(KC_X, KC_T) {
    chord2(KC_LGUI, KC_GRV);
  }
}

void leader_secret(void) {
  SEQ_TWO_KEYS(KC_S, KC_W) {
    send_string_P(secrets[SECRET_W]);
  }

  SEQ_TWO_KEYS(KC_S, KC_D) {
    send_string_P(secrets[SECRET_D]);
  }

  SEQ_TWO_KEYS(KC_S, KC_P) {
    send_string_P(secrets[SECRET_P]);
  }
}

void leader_utility(void) {
  SEQ_FIVE_KEYS(KC_F, KC_L, KC_A, KC_S, KC_H) {
    reset_keyboard();
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
extern bool clicky_enable;
#endif

void leader_music(void) {
#if defined(AUDIO_ENABLE)
  SEQ_TWO_KEYS(KC_SPACE, KC_SPACE) {
    music_activated ? music_off() : music_on();
  }

  SEQ_TWO_KEYS(KC_TAB, KC_TAB) {
    music_mode_cycle();
  }

  SEQ_FIVE_KEYS(KC_C, KC_L, KC_I, KC_C, KC_K) {
    clicky_enable = !clicky_enable;
  }
#endif
}

void leader_debug(void) {
  SEQ_FIVE_KEYS(KC_D, KC_E, KC_B, KC_U, KC_G) {
    debug_enable = !debug_enable;
    if (debug_enable) {
      print("Debug enabled\n");
    } else {
      print("Debug disabled\n");
    }
  }
}
