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
