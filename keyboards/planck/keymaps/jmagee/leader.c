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

#if 0
void leader_fkeys(void) {
  enum { N = 24 };
  static const uint8_t leader_pairs[N][2] = {
    {KC_Q, KC_F1}, {KC_W, KC_F2}, {KC_E, KC_F3}, {KC_R, KC_F4}, {KC_T, KC_F5}, {KC_U, KC_F6},
    {KC_I, KC_F7}, {KC_O, KC_F8}, {KC_P, KC_F9}, {KC_A, KC_F10}, {KC_S, KC_F11}, {KC_D, KC_F12},
    {KC_F, KC_F13}, {KC_G, KC_F14}, {KC_H, KC_F15}, {KC_J, KC_F16}, {KC_K, KC_F17}, {KC_L, KC_F18},
    {KC_SCLN, KC_F19}, {KC_QUOT, KC_F20}, {KC_Z, KC_F21}, {KC_X, KC_F22}, {KC_C, KC_F23}, {KC_V, KC_F24},
  };

  for (uint8_t i = 0; i < N; ++i) {
    SEQ_TWO_KEYS(KC_F, leader_pairs[i][0]) {
      register_code(leader_pairs[i][1]);
      unregister_code(leader_pairs[i][1]);
    }
  }
}
#endif

void leader_fkeys(void) {
  enum { N = 24 };
  static const uint8_t fkeys[N] = {
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
    KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20,
    KC_F21, KC_F22, KC_F23, KC_F24
  };
  static const uint8_t digits[10] = {
    /* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 on QWERTY layer */
    KC_N, KC_M, KC_COMM, KC_DOT, KC_J, KC_K, KC_L, KC_U, KC_I, KC_O
  };

  uint8_t f = 0;

  for (uint8_t i = 1; i < 25; ++i) {
    if (i < 10) {
      /* F1 - F9 */
      SEQ_TWO_KEYS(KC_F, digits[i]) {
        register_code(fkeys[f]);
        unregister_code(fkeys[f]);
      }
    } else {
      /* F10 - F24 */
      uint8_t d1 = i < 20 ? 1 : 2;
      SEQ_THREE_KEYS(KC_F, digits[d1], digits[i % 10]) {
        register_code(fkeys[f]);
        unregister_code(fkeys[f]);
      }
    }
    ++f;
  }
}

void leader_ctrl_alt_del(void) {
  SEQ_THREE_KEYS(KC_C, KC_A, KC_D) {
    register_code(KC_LCTRL);
    register_code(KC_LALT);
    register_code(KC_DELETE);
    unregister_code(KC_DELETE);
    unregister_code(KC_LALT);
    unregister_code(KC_LCTRL);
  }
}
