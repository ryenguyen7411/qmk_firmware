/* Copyright 2023 ryenguyen7411 <ryenguyen7411@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
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

enum rye_keyboardio_atreus_layers {
  _BASE,
  _FN1,
  _FN2,
  _FN3,
  _FN4,
};

enum custom_keycodes {
  MC_VI01 = SAFE_RANGE,
  MC_VI02,
  MC_VI03,
  MC_VI04,
  MC_VI05,
  MC_VI06,
  MC_VI07,
  MC_VI11,
  MC_VI13,
  MC_VI16,
  MC_VI19,
  MC_S04,
  MC_S07,
  MC_S09,
  MC_S10,
  MC_S11,
};

enum tap_dances {
  TD_KC_COLN,
  TD_KC_QUOT,
  TD_MC_VI12,
  TD_MC_FN2,
};

#define FN1 LT(_FN1, KC_SPACE)
#define FN2 TD(TD_MC_FN2)
#define FN3 LT(_FN3, KC_SPACE)
#define FN4 LT(_FN4, KC_ENTER)

#define SHFTESC LSFT_T(KC_ESC)
#define CTRLESC RCTL_T(KC_ESC)
#define LANG C(KC_SPACE)
#define WIN_L C(KC_LEFT)
#define WIN_R C(KC_RIGHT)
#define PEEK C(KC_UP)
#define HTML G(S(KC_C))
#define DOCK C(KC_F3)
#define SCREEN1 G(S(KC_LBRC))
#define SCREEN2 G(S(KC_RBRC))

#define TD_COLN TD(TD_KC_COLN)
#define TD_QUOT TD(TD_KC_QUOT)
#define TD_VI12 TD(TD_MC_VI12)

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

td_tap_t tapdance_get_state(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return TD_SINGLE_TAP;
    else return TD_SINGLE_HOLD;
  } else if (state->count == 2) {
    return TD_DOUBLE_TAP;
  }
  return TD_UNKNOWN;
}

void tapdance_vi12(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) tap_code(KC_E);
  else SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "qq");
}

void tapdance_toggle_fn2_finished(tap_dance_state_t *state, void *user_data) {
  td_tap_state.state = tapdance_get_state(state);
  if (td_tap_state.state == TD_SINGLE_TAP) {
    if (layer_state_is(_FN2)) layer_off(_FN2);
    else tap_code(KC_SPACE);
  }
  else if (td_tap_state.state == TD_SINGLE_HOLD) layer_on(_FN2);
  else if (td_tap_state.state == TD_DOUBLE_TAP) {
    if (layer_state_is(_FN2)) layer_off(_FN2);
    else layer_on(_FN2);
  }
}

void tapdance_toggle_fn2_reset(tap_dance_state_t *state, void *user_data) {
  if (td_tap_state.state == TD_SINGLE_TAP) layer_off(_FN2);
  else if (td_tap_state.state == TD_SINGLE_HOLD) layer_off(_FN2);
  td_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
  [TD_KC_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
  [TD_KC_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT),
  [TD_MC_VI12] = ACTION_TAP_DANCE_FN(tapdance_vi12),
  [TD_MC_FN2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_toggle_fn2_finished, tapdance_toggle_fn2_reset),
};

const key_override_t kc_mouseslow_key_override = ko_make_basic(MOD_BIT(KC_LCMD), KC_ACL0, G(KC_W));
const key_override_t kc_mouseclick_key_override = ko_make_basic(MOD_BIT(KC_LCMD), KC_BTN1, G(KC_T));
const key_override_t kc7_key_override = ko_make_basic(MOD_MASK_GUI, KC_7, DOCK);
const key_override_t kc8_key_override = ko_make_basic(MOD_MASK_GUI, KC_8, LANG);
const key_override_t kc9_key_override = ko_make_basic(MOD_MASK_GUI, KC_9, KC_DEL);
const key_override_t kc0_key_override = ko_make_basic(MOD_MASK_GUI, KC_0, KC_BSPC);
const key_override_t kc_mouseright_ctrl_key_override = ko_make_basic(MOD_MASK_CTRL, KC_MS_R, C(KC_L));
const key_override_t kc_mouseright_cmd_key_override = ko_make_basic(MOD_MASK_GUI, KC_MS_R, G(KC_L));

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &kc_mouseslow_key_override,
    &kc_mouseclick_key_override,
    &kc7_key_override,
    &kc8_key_override,
    &kc9_key_override,
    &kc0_key_override,
    &kc_mouseright_ctrl_key_override,
    &kc_mouseright_cmd_key_override,
    NULL // Null terminate the array of overrides!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   FN4,
    SHFTESC,KC_Z,   KC_X,   KC_C,   KC_V,   _______,MC_S09, KC_B,   KC_N,   KC_M,   _______,CTRLESC,
    KC_LCTL,_______,KC_LOPT,KC_LCMD,FN2,    FN1,    KC_SPC, FN3,    KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT
  ),
  [_FN1] = LAYOUT(
    _______,KC_ACL0,TD_VI12,MC_VI11,KC_BTN1,                KC_BTN2,DOCK,   LANG,   KC_DEL, KC_BSPC,
    KC_RCMD,KC_WH_R,KC_WH_U,KC_WH_D,KC_WH_L,                KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,
    _______,_______,_______,_______,_______,_______,_______,SCREEN1,PEEK,   WIN_L,  WIN_R,  SCREEN2,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
  [_FN2] = LAYOUT(
    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_LCMD,KC_LSFT,KC_LOPT,KC_GRV, KC_TAB,                 KC_MINS,KC_EQL, TD_COLN,TD_QUOT,KC_BSLS,
    _______,_______,_______,_______,_______,_______,_______,KC_LBRC,KC_COMM,KC_DOT, KC_SLSH,KC_RBRC,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
  [_FN3] = LAYOUT(
    _______,_______,_______,MC_VI13,_______,                MC_VI05,_______,MC_VI19,KC_F11, KC_F12,
    _______,_______,_______,_______,MC_VI16,                MC_VI07,MC_VI03,MC_VI06,MC_VI02,MC_VI01,
    _______,_______,_______,_______,_______,_______,_______,MC_VI04,_______,_______,_______,MC_S04,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
  [_FN4] = LAYOUT(
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,
    _______,_______,MC_S07, KC_BRID,KC_BRIU,                _______,KC_MUTE,KC_VOLD,KC_VOLU,_______,
    _______,_______,_______,HTML   ,_______,_______,QK_BOOT,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
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
      case MC_VI05:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "'");
        break;
      case MC_VI06:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "k");
        break;
      case MC_VI07:
        SEND_STRING(SS_LCTL("j"));
        break;
      case MC_VI11:
        if (keyboard_report->mods & MOD_MASK_GUI) {
          SEND_STRING("r");
        } else {
          SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "w");
        }
        break;
      case MC_VI13:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "r");
        break;
      case MC_VI16:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "f");
        break;
      case MC_VI19:
        SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "p");
        break;
      case MC_S04:
        SEND_STRING(SS_LCMD("v"));
        break;
      case MC_S07:
        SEND_STRING(SS_LCTL("`") SS_DELAY(50) SS_LCTL("l"));
        break;
      case MC_S09:
        if ((get_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_CTRL)) {
          layer_off(_FN1);
        } else {
          layer_on(_FN1);
        }
        break;
      default:
        break;
    }
  }
  return true;
}
