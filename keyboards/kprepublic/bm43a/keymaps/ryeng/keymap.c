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
  BASE_FN, // Use for active Base layer inside Fn layer
  /* MACROGAME, */
};

enum custom_keycodes {
  MC_VI01 = SAFE_RANGE,
  MC_VI02,
  MC_VI03,
  MC_VI04,
  MC_VI06,
  MC_VI07,
  MC_VI08,
  MC_VI11,
  MC_VI13,
  MC_VI16,
  MC_VI18,
  MC_VI19,
  MC_VI20,
  MC_G01,
  MC_S07,
};

enum tap_dances {
  TD_KC_COLN,
  TD_KC_QUOT,
  TD_MC_VI12,
  TD_MC_FN1,
  TD_MC_FN2_DOCK,
};

#define TD_COLN TD(TD_KC_COLN)
#define TD_QUOT TD(TD_KC_QUOT)
#define TD_VI12 TD(TD_MC_VI12)
#define TD_FN1 TD(TD_MC_FN1)
#define TD_FN2_DOCK TD(TD_MC_FN2_DOCK)
#define KC_FN2 LT(FN2, KC_ENTER)
#define KC_FN3 LT(FN3, KC_SPC)
#define KC_FN4 LT(FN4, KC_SPC)
#define KC_FN_LSFT LM(BASE_FN, MOD_LSFT)
#define KC_FN_LCTL LM(BASE_FN, MOD_LCTL)
#define KC_FN_LALT LM(BASE_FN, MOD_LALT)
#define KC_FN_LGUI LM(BASE_FN, MOD_LGUI) // Not use because it conflict with mouse key
#define KC___ _______

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP
} td_tap_t;

typedef struct {
  td_tap_t state;
} td_state_t;

static td_state_t td_tap_state = {
  .state = TD_NONE
};

td_tap_t tapdance_get_state(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return TD_SINGLE_TAP;
    else return TD_SINGLE_HOLD;
  } else if (state->count == 2) {
    return TD_DOUBLE_TAP;
  }
  return TD_UNKNOWN;
}

void tapdance_vi12(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) tap_code(KC_W);
  else SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "qq");
}

void tapdance_toggle_fn1_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_tap_state.state = tapdance_get_state(state);
  if (td_tap_state.state == TD_SINGLE_TAP) tap_code(KC_ESC);
  else if (td_tap_state.state == TD_SINGLE_HOLD) layer_on(FN1);
  else if (td_tap_state.state == TD_DOUBLE_TAP) {
    if (layer_state_is(FN1)) layer_off(FN1);
    else layer_on(FN1);
  }
}

void tapdance_toggle_fn1_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (td_tap_state.state == TD_SINGLE_TAP) layer_off(FN1);
  else if (td_tap_state.state == TD_SINGLE_HOLD) layer_off(FN1);
  td_tap_state.state = TD_NONE;
}

void tapdance_toggle_dock_fn2(qk_tap_dance_state_t *state, void *user_data) {
  td_tap_state.state = tapdance_get_state(state);
  if (td_tap_state.state == TD_SINGLE_TAP) {
    register_code(KC_LCTL);
    tap_code(KC_F3);
    unregister_code(KC_LCTL);
  } else if (td_tap_state.state == TD_SINGLE_HOLD) {
    tap_code(KC_ENT);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_KC_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
  [TD_KC_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT),
  [TD_MC_VI12] = ACTION_TAP_DANCE_FN(tapdance_vi12),
  [TD_MC_FN1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_toggle_fn1_finished, tapdance_toggle_fn1_reset),
  [TD_MC_FN2_DOCK] = ACTION_TAP_DANCE_FN(tapdance_toggle_dock_fn2),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case MC_VI01:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) ";");
        break;
      case MC_VI02:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "l");
        break;
      case MC_VI03:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "j");
        break;
      case MC_VI04:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "b");
        break;
      case MC_VI06:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "k");
        break;
      case MC_VI07:
        SEND_STRING(",g");
        break;
      case MC_VI08:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "'");
        break;
      case MC_VI11:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "w");
        break;
      // MC_VI12: Leader + qq
      case MC_VI13:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "r");
        break;
      case MC_VI16:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "f");
        break;
      case MC_VI18:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "o");
        break;
      case MC_VI19:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "p");
        break;
      case MC_VI20:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "a");
        break;
      case MC_G01:
        SEND_STRING("kj");
        break;
      case MC_S07:
        SEND_STRING(SS_LCTL("`") SS_DELAY(50) SS_LCTL("l"));
        break;
      default:
        break;
    }
  }
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    TD_FN1, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_FN2,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_DOT, KC___, KC_RGUI,
    KC_LCTL, KC_LALT, KC_LGUI, KC_FN3, KC_FN4, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
  ),
  [FN1] = LAYOUT(
    KC___, KC_ACL0, TD_VI12, MC_VI11, KC___, KC___, KC___, KC___, C(KC_SPC), KC___, KC___, KC_DEL,
    KC___, KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC___, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, TD_FN2_DOCK,
    KC___, KC___, KC___, KC_BTN1, KC_BTN2, KC___, KC___, KC___, C(KC_LEFT), C(KC_RIGHT), C(KC_UP),
    KC___, KC___, KC___, KC_LSFT, KC___, KC___, KC___, KC___, KC___
  ),
  [FN2] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    KC___, KC___, KC___, MC_S07, KC_BRID, KC_BRIU, KC___, KC_MUTE, KC_VOLD, KC_VOLU, KC___,
    KC___, RESET, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___,
    KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___
  ),
  [FN3] = LAYOUT(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LBRC, KC_RBRC,
    KC_LGUI, KC_LSFT, KC_LALT, KC_GRV, KC_TAB, KC___, KC_MINS, KC_EQL, TD_COLN, TD_QUOT, KC_BSLS,
    KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC_COMM, KC_DOT, KC_SLSH, G(KC_V),
    KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___
  ),
  [FN4] = LAYOUT(
    KC___, KC___, KC___, KC___, MC_VI13, MC_VI20, KC___, KC___, KC___, MC_VI18, MC_VI19, KC_F12,
    KC___, KC___, KC___, KC___, MC_VI16, MC_VI07, KC___, MC_VI03, MC_VI06, MC_VI02, MC_VI01,
    KC___, KC___, KC___, KC___, KC___, MC_VI04, KC___, KC___, KC___, MC_VI08, G(KC_V),
    KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___
  ),
  [BASE_FN] = LAYOUT(
    KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC___, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC___,
    KC___, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_DOT, KC___, KC___,
    KC___, KC___, KC___, KC___, KC___, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
  ),
  /* [MACROGAME] = LAYOUT( */
  /*   KC_ESC, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC_MUTE, */
  /*   MO(FN1), DF(BASE), KC___, KC___, KC___, KC___, KC___, KC___, MC_G01, KC___, KC___, */
  /*   KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, */
  /*   KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___, KC___ */
  /* ), */
};
