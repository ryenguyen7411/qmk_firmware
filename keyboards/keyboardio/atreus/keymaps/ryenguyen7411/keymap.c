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

// Layer Definitions
enum rye_keyboardio_atreus_layers {
  _BASE,
  _FN1,
  _FN2,
  _FN3,
  _FN4,
};

// Custom Keycodes
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
  SCREEN1,
  SCREEN2,
  PEEK,
  CLEAR,
  MOUSE,
  MC_RCMD,
  MC_S10,
  MC_S11,
};

// Tap Dance Definitions
enum tap_dances {
  TD_FN_SCLN,
  TD_FN_QUOT,
  TD_FN_VI12,
  TD_FN_FN2,
};

#define FN1 LT(_FN1, KC_SPACE)
#define FN2 TD(TD_FN_FN2)
#define FN2_LT LT(_FN2, KC_SPACE)
#define FN3 LT(_FN3, KC_SPACE)
#define FN4 LT(_FN4, KC_ENTER)

#define SHFTESC LSFT_T(KC_ESC)
#define CTRLESC RCTL_T(KC_ESC)
#define LANG C(KC_SPACE)
#define WIN_L C(KC_LEFT)
#define WIN_R C(KC_RIGHT)
#define HTML G(S(KC_C))
#define DOCK C(KC_F3)
#define PASTE G(KC_V)

#define TD_SCLN TD(TD_FN_SCLN)
#define TD_QUOT TD(TD_FN_QUOT)
#define TD_VI12 TD(TD_FN_VI12)

// TAP DANCE -----------------------------------------------------------------

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

td_tap_t td_get_state(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return TD_SINGLE_TAP;
    else return TD_SINGLE_HOLD;
  }
  return TD_DOUBLE_TAP;
}

void td_vi12(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) tap_code(KC_E);
  else SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE) "qq");
}

void td_fn2_finished(tap_dance_state_t *state, void *user_data) {
  td_tap_state.state = td_get_state(state);
  if (td_tap_state.state == TD_SINGLE_TAP) {
    if (!layer_state_is(_FN2)) tap_code(KC_SPACE);
  }
  else if (td_tap_state.state == TD_SINGLE_HOLD) layer_on(_FN2);
  else if (td_tap_state.state == TD_DOUBLE_TAP) layer_on(_FN2);
}

void td_fn2_reset(tap_dance_state_t *state, void *user_data) {
  if (td_tap_state.state == TD_SINGLE_TAP) layer_off(_FN2);
  else if (td_tap_state.state == TD_SINGLE_HOLD) layer_off(_FN2);
  td_tap_state.state = TD_NONE;
}

// Register tap dance actions
tap_dance_action_t tap_dance_actions[] = {
  [TD_FN_SCLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
  [TD_FN_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT),
  [TD_FN_VI12] = ACTION_TAP_DANCE_FN(td_vi12),
  [TD_FN_FN2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_fn2_finished, td_fn2_reset),
};

// KEY OVERRIDES -------------------------------------------------------------

const key_override_t ko_cmd_s = ko_make_basic(MOD_BIT(KC_LCMD), KC_WH_R, G(KC_S));
const key_override_t ko_cmd_d = ko_make_basic(MOD_BIT(KC_LCMD), KC_WH_U, G(KC_D));
const key_override_t ko_cmd_f = ko_make_basic(MOD_BIT(KC_LCMD), KC_WH_D, G(KC_F));
const key_override_t ko_cmd_g = ko_make_basic(MOD_BIT(KC_LCMD), KC_MS_L, G(KC_G));
const key_override_t ko_cmd_h = ko_make_basic(MOD_BIT(KC_LCMD), KC_MS_L, G(KC_H));
const key_override_t ko_cmd_j = ko_make_basic(MOD_BIT(KC_LCMD), KC_MS_D, G(KC_J));
const key_override_t ko_cmd_k = ko_make_basic(MOD_BIT(KC_LCMD), KC_MS_U, G(KC_K));
const key_override_t ko_cmd_l = ko_make_basic(MOD_BIT(KC_LCMD), KC_MS_R, G(KC_L));
const key_override_t ko_cmd_w = ko_make_basic(MOD_BIT(KC_LCMD), KC_ACL0, G(KC_W));
const key_override_t ko_cmd_t = ko_make_basic(MOD_BIT(KC_LCMD), KC_BTN1, G(KC_T));
const key_override_t ko_cmd_y = ko_make_basic(MOD_BIT(KC_LCMD), KC_BTN2, G(KC_Y));
const key_override_t ko_rcmd_s = ko_make_basic(MOD_BIT(KC_RCMD), KC_WH_R, KC_LSFT);
const key_override_t ko_rcmd_d = ko_make_basic(MOD_BIT(KC_RCMD), KC_WH_U, KC_LOPT);
const key_override_t ko_rcmd_f = ko_make_basic(MOD_BIT(KC_RCMD), KC_WH_D, KC_GRV);
const key_override_t ko_rcmd_g = ko_make_basic(MOD_BIT(KC_RCMD), KC_WH_L, KC_TAB);
const key_override_t ko_rcmd_h = ko_make_basic(MOD_BIT(KC_RCMD), KC_MS_L, KC_MINS);
const key_override_t ko_rcmd_j = ko_make_basic(MOD_BIT(KC_RCMD), KC_MS_D, KC_EQL);
const key_override_t ko_rcmd_k = ko_make_basic(MOD_BIT(KC_RCMD), KC_MS_U, KC_SCLN);
const key_override_t ko_rcmd_l = ko_make_basic(MOD_BIT(KC_RCMD), KC_MS_R, KC_QUOT);
const key_override_t ko_ctrl_h = ko_make_basic(MOD_MASK_CTRL, KC_MS_L, C(KC_H));
const key_override_t ko_ctrl_j = ko_make_basic(MOD_MASK_CTRL, KC_MS_D, C(KC_J));
const key_override_t ko_ctrl_k = ko_make_basic(MOD_MASK_CTRL, KC_MS_U, C(KC_K));
const key_override_t ko_ctrl_l = ko_make_basic(MOD_MASK_CTRL, KC_MS_R, C(KC_L));
const key_override_t ko_ctrl_o = ko_make_basic(MOD_MASK_CTRL, KC_DEL, C(KC_O));

const key_override_t ko_7 = ko_make_basic(MOD_MASK_GUI, KC_7, DOCK);
const key_override_t ko_8 = ko_make_basic(MOD_MASK_GUI, KC_8, LANG);
const key_override_t ko_9 = ko_make_basic(MOD_MASK_GUI, KC_9, KC_DEL);
const key_override_t ko_0 = ko_make_basic(MOD_MASK_GUI, KC_0, KC_BSPC);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_cmd_s,
    &ko_cmd_d,
    &ko_cmd_f,
    &ko_cmd_g,
    &ko_cmd_h,
    &ko_cmd_j,
    &ko_cmd_k,
    &ko_cmd_l,
    &ko_cmd_w,
    &ko_cmd_t,
    &ko_cmd_y,
    &ko_rcmd_s,
    &ko_rcmd_d,
    &ko_rcmd_f,
    &ko_rcmd_g,
    &ko_rcmd_h,
    &ko_rcmd_j,
    &ko_rcmd_k,
    &ko_rcmd_l,
    &ko_ctrl_h,
    &ko_ctrl_j,
    &ko_ctrl_k,
    &ko_ctrl_l,
    &ko_ctrl_o,
    &ko_7,
    &ko_8,
    &ko_9,
    &ko_0,
    NULL // Null terminate the array of overrides!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   FN4,
    SHFTESC,KC_Z,   KC_X,   KC_C,   KC_V,   FN2,    MOUSE,  KC_B,   KC_N,   KC_M,   FN2_LT, CTRLESC,
    KC_LCTL,_______,KC_LOPT,KC_LCMD,FN2,    FN1,    KC_SPC, FN3,    KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT
  ),
  [_FN1] = LAYOUT(
    _______,KC_ACL0,TD_VI12,MC_VI11,KC_BTN1,                KC_BTN2,DOCK,   LANG,   KC_DEL, KC_BSPC,
    MC_RCMD,KC_WH_R,KC_WH_U,KC_WH_D,KC_WH_L,                KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,KC_ENT,
    _______,_______,_______,_______,_______,_______,_______,SCREEN1,PEEK,   WIN_L,  WIN_R,  SCREEN2,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
  [_FN2] = LAYOUT(
    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_LCMD,KC_LSFT,KC_LOPT,KC_GRV, KC_TAB,                 KC_MINS,KC_EQL, TD_SCLN,TD_QUOT,KC_BSLS,
    _______,_______,_______,_______,_______,_______,_______,KC_LBRC,KC_COMM,KC_DOT, KC_SLSH,KC_RBRC,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
  [_FN3] = LAYOUT(
    _______,_______,_______,MC_VI13,_______,                MC_VI05,_______,MC_VI19,KC_F11, KC_F12,
    _______,_______,_______,_______,MC_VI16,                MC_VI07,MC_VI03,MC_VI06,MC_VI02,MC_VI01,
    _______,_______,_______,_______,_______,_______,_______,MC_VI04,_______,_______,_______,PASTE,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
  [_FN4] = LAYOUT(
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,
    _______,_______,CLEAR,  KC_BRID,KC_BRIU,                _______,KC_MUTE,KC_VOLD,KC_VOLU,_______,
    _______,_______,_______,HTML   ,_______,_______,QK_BOOT,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
};

static bool is_lcmd_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCMD:
      is_lcmd_pressed = record->event.pressed;
      break;
    case MC_RCMD:
      if (is_lcmd_pressed) {
        if (record->event.pressed) {
          register_code(KC_A);
        } else {
          unregister_code(KC_A);
        }
        return false;
      } else {
        if (record->event.pressed) {
          register_code(KC_RCMD);
        } else {
          unregister_code(KC_RCMD);
        }
      }
      break;
    default:
      break;
  }

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
      case SCREEN1:
        if ((keyboard_report->mods & MOD_BIT(KC_LGUI)) || (keyboard_report->mods & MOD_MASK_SHIFT)) {
          SEND_STRING("b");
        } else if (keyboard_report->mods & MOD_BIT(KC_RGUI)) {
          SEND_STRING("[");
        } else {
          register_code(KC_LCMD);
          register_code(KC_LSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          unregister_code(KC_LSFT);
          unregister_code(KC_LCMD);
        }
        break;
      case SCREEN2:
        if (keyboard_report->mods & MOD_BIT(KC_RGUI)) {
          SEND_STRING("]");
        } else {
          register_code(KC_LCMD);
          register_code(KC_LSFT);
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
          unregister_code(KC_LSFT);
          unregister_code(KC_LCMD);
        }
        break;
      case PEEK:
        if ((keyboard_report->mods & MOD_MASK_GUI) || (keyboard_report->mods & MOD_MASK_SHIFT)) {
          SEND_STRING("n");
        } else {
          register_code(KC_LCTL);
          register_code(KC_UP);
          unregister_code(KC_UP);
          unregister_code(KC_LCTL);
        }
        break;
      case CLEAR:
        SEND_STRING(SS_LCTL("`") SS_DELAY(50) SS_LCTL("l"));
        break;
      case MOUSE:
        if ((keyboard_report->mods & MOD_MASK_SHIFT) || (keyboard_report->mods & MOD_MASK_CTRL)) {
          layer_off(_FN1);
          layer_off(_FN2);
        } else {
          layer_on(_FN1);
          layer_off(_FN2);
        }
        break;
      default:
        break;
    }
  }
  return true;
}
