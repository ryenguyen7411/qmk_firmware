/* Copyright 2019 mechmerlin
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
#include QMK_KEYBOARD_H

enum rye_bm43_layers {
  BASE,
  FN1,
  FN2,
  FN3,
  FN4,
};

enum custom_keycodes {
  MC_VIM_01 = SAFE_RANGE,
  MC_VIM_02,
  MC_VIM_03,
  MC_VIM_04,
  MC_VIM_05,
  MC_VIM_06,
  MC_VIM_07,
  MC_VIM_08,
  MC_VIM_09,
  MC_VIM_11,
};

enum tap_dances {
  TD_COLN,
  TD_QUOT,
  TD_MINS,
  TD_PLUS,
  TD_LBRC,
  TD_RBRC,
  TD_COMM,
  TD_DOT,

  TD_VIM_12,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    LT(FN1, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, LT(FN2, KC_ENTER),
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, _______, _______, _______,
    KC_LCTL, KC_LALT, KC_LGUI, LT(FN3, KC_SPC), LT(FN4, KC_SPC), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
  ),
  [FN1] = LAYOUT(
    _______, _______, _______, TD(TD_VIM_12), MC_VIM_11, _______, _______, _______, _______, KC_LCBR, KC_RCBR, KC_DEL,
    _______, KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, C(KC_SPC),
    _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, C(KC_LEFT), C(KC_RIGHT), C(KC_UP),
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [FN2] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_BRID, KC_BRIU, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,
    _______, RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [FN3] = LAYOUT(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LBRC, KC_RBRC,
    KC_LGUI, KC_LSFT, KC_LALT, KC_GRV, KC_TAB, C(S(KC_6)), KC_MINS, KC_EQL, TD(TD_COLN), TD(TD_QUOT), KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, KC_COMM, KC_DOT, KC_SLSH, G(KC_V),
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [FN4] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    MC_VIM_05, _______, _______, _______, _______, MC_VIM_09, _______, MC_VIM_03, MC_VIM_06, MC_VIM_02, MC_VIM_01,
    _______, _______, _______, _______, _______, MC_VIM_04, _______, _______, MC_VIM_07, MC_VIM_08, G(KC_V),
    _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};

void tapdance_coln_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_SCLN);
  } else {
    register_code16(KC_COLN);
  }
}

void tapdance_coln_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_SCLN);
  } else {
    unregister_code16(KC_COLN);
  }
}

void tapdance_quot_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_QUOT);
  } else {
    register_code16(KC_DQT);
  }
}

void tapdance_quot_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_QUOT);
  } else {
    unregister_code16(KC_DQT);
  }
}

void tapdance_mins_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_MINS);
  } else {
    register_code16(KC_UNDS);
  }
}

void tapdance_mins_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_MINS);
  } else {
    unregister_code16(KC_UNDS);
  }
}

void tapdance_plus_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_EQL);
  } else {
    register_code16(KC_PLUS);
  }
}

void tapdance_plus_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_EQL);
  } else {
    unregister_code16(KC_PLUS);
  }
}

void tapdance_lbrc_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LBRC);
  } else {
    register_code16(KC_LCBR);
  }
}

void tapdance_lbrc_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_LBRC);
  } else {
    unregister_code16(KC_LCBR);
  }
}

void tapdance_rbrc_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_RBRC);
  } else {
    register_code16(KC_RCBR);
  }
}

void tapdance_rbrc_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_RBRC);
  } else {
    unregister_code16(KC_RCBR);
  }
}

void tapdance_comm_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_COMM);
  } else {
    register_code16(KC_LT);
  }
}

void tapdance_comm_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_COMM);
  } else {
    unregister_code16(KC_LT);
  }
}

void tapdance_dot_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_DOT);
  } else {
    register_code16(KC_GT);
  }
}

void tapdance_dot_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_DOT);
  } else {
    unregister_code16(KC_GT);
  }
}

void tapdance_vim_12_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count > 1) {
    SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "qq");
  }
}

void tapdance_vim_12_reset(qk_tap_dance_state_t *state, void *user_data) {
}

// All tap dance functions would go here.
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_COLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_coln_finished, tapdance_coln_reset),
  [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_quot_finished, tapdance_quot_reset),
  [TD_MINS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_mins_finished, tapdance_mins_reset),
  [TD_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_plus_finished, tapdance_plus_reset),
  [TD_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_lbrc_finished, tapdance_lbrc_reset),
  [TD_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_rbrc_finished, tapdance_rbrc_reset),
  [TD_COMM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_comm_finished, tapdance_comm_reset),
  [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_dot_finished, tapdance_dot_reset),
  [TD_VIM_12] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_vim_12_finished, tapdance_vim_12_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // COMM (,) is VIM Leader Key
  switch (keycode) {
    case MC_VIM_01:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) ",;");
      }
      break;
    case MC_VIM_02:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) ",l");
      }
      break;
    case MC_VIM_03:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) ",j");
      }
      break;
    case MC_VIM_04:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) ",b");
      }
      break;
    case MC_VIM_05:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c") SS_TAP(X_ESC));
      }
      break;
    case MC_VIM_06:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) ",k");
      }
      break;
    case MC_VIM_07:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) "[g");
      }
      break;
    case MC_VIM_08:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) "]g");
      }
      break;
    case MC_VIM_09:
      if (record->event.pressed) {
        SEND_STRING(",g");
      }
      break;
    case MC_VIM_11:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "w");
      }
      break;
    default:
      break;
  }
  return true;
}
