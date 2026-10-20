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

// =============================================================================
// LAYERS & KEYCODES
// =============================================================================

enum layer_names {
    _BASE,
    _FN1, // mouse + windows
    _FN2, // numbers + symbols
    _FN3, // vim / tmux shortcuts
    _FN4, // F-keys + media
};

enum custom_keycodes {
    // Vim / tmux shortcuts (FN3)
    MC_VI01 = SAFE_RANGE,
    MC_VI02,
    MC_VI03,
    MC_VI04,
    MC_VI05,
    MC_VI06,
    MC_VI07,
    MC_VI08,
    MC_VI09,
    MC_VI10,
    MC_VI11,
    MC_VI12,
    MC_VI99, // save

    // Window / screen management (FN1)
    SCREEN1,
    SCREEN2,
    PEEK,
    WIN_L,
    WIN_R,

    // Mouse layer
    MOUSE,     // turn the mouse layer on (off with Shift/Ctrl)
    MOUSEON,  // turn the mouse layer on (FN3)
    MOUSEOF, // turn the mouse layer off (FN3)
    MC_RCMD,   // right Cmd, also the digitizer jump modifier
    DRAG,      // drag lock

    CLEAR, // terminal clear (FN4)
};

#define FN1 LT(_FN1, KC_SPACE)
#define FN2 LT(_FN2, KC_SPACE)
#define FN3 LT(_FN3, KC_SPACE)
#define FN4 LT(_FN4, KC_ENTER)
#define A_RCMD LT(_FN1, KC_A) // hold: right Cmd + mouse layer, for cursor jumps

#define SHFTESC LSFT_T(KC_ESC)
#define CTRLESC RCTL_T(KC_ESC)
#define LANG C(KC_SPACE)
#define HTML G(S(KC_C))
#define DOCK C(KC_F3)
#define WIDG C(S(KC_Z))
#define PASTE G(KC_V)

// =============================================================================
// TAP DANCE
// =============================================================================

enum tap_dances {
    TD_FN_SCLN,
};

#define TD_SCLN TD(TD_FN_SCLN)

tap_dance_action_t tap_dance_actions[] = {
    [TD_FN_SCLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
};

// =============================================================================
// KEY OVERRIDES
// =============================================================================

// Mouse-layer overrides fire only when the mod is held before the key. Pressing the mod while a
// key is already held keeps the real mouse action (e.g. hold M ▶, then Cmd = move with Cmd held).
#define ko_make_mouse(mods, key, replacement) \
    ko_make_with_layers_negmods_and_options(mods, key, replacement, ~0, 0, ko_option_activation_trigger_down)

// Left Cmd + mouse-layer key sends Cmd + the letter underneath
const key_override_t ko_cmd_s = ko_make_mouse(MOD_BIT(KC_LCMD), MS_WHLR, G(KC_S));
const key_override_t ko_cmd_d = ko_make_mouse(MOD_BIT(KC_LCMD), MS_WHLU, G(KC_D));
const key_override_t ko_cmd_f = ko_make_mouse(MOD_BIT(KC_LCMD), MS_WHLD, G(KC_F));
const key_override_t ko_cmd_g = ko_make_mouse(MOD_BIT(KC_LCMD), MS_WHLL, G(KC_G));
const key_override_t ko_cmd_h = ko_make_mouse(MOD_BIT(KC_LCMD), MS_LEFT, G(KC_H));
const key_override_t ko_cmd_j = ko_make_mouse(MOD_BIT(KC_LCMD), MS_DOWN, G(KC_J));
const key_override_t ko_cmd_k = ko_make_mouse(MOD_BIT(KC_LCMD), MS_UP, G(KC_K));
const key_override_t ko_cmd_l = ko_make_mouse(MOD_BIT(KC_LCMD), MS_RGHT, G(KC_L));
const key_override_t ko_cmd_w = ko_make_mouse(MOD_BIT(KC_LCMD), MS_ACL0, G(KC_W));
const key_override_t ko_cmd_t = ko_make_mouse(MOD_BIT(KC_LCMD), MS_BTN1, G(KC_T));
const key_override_t ko_cmd_y = ko_make_mouse(MOD_BIT(KC_LCMD), MS_BTN2, G(KC_Y));
const key_override_t ko_cmd_o = ko_make_with_layers_and_negmods(MOD_BIT(KC_LCMD), KC_DEL, G(KC_O), ~0, MOD_MASK_SHIFT);

// Ctrl + mouse-layer key sends Ctrl + the letter underneath. Ctrl + wheel keys stay
// Ctrl + scroll (zoom in maps / Figma), except Ctrl + Shift + Whl ▼.
const key_override_t ko_ctrl_h = ko_make_mouse(MOD_MASK_CTRL, MS_LEFT, C(KC_H));
const key_override_t ko_ctrl_j = ko_make_mouse(MOD_MASK_CTRL, MS_DOWN, C(KC_J));
const key_override_t ko_ctrl_k = ko_make_mouse(MOD_MASK_CTRL, MS_UP, C(KC_K));
const key_override_t ko_ctrl_l = ko_make_mouse(MOD_MASK_CTRL, MS_RGHT, C(KC_L));
const key_override_t ko_ctrl_o = ko_make_basic(MOD_MASK_CTRL, KC_DEL, C(KC_O));
const key_override_t ko_ctrl_shift_f = ko_make_mouse(MOD_MASK_CS, MS_WHLD, C(S(KC_F)));

// Either Cmd + 7/8/9/0
const key_override_t ko_7 = ko_make_basic(MOD_MASK_GUI, KC_7, DOCK);
const key_override_t ko_8 = ko_make_basic(MOD_MASK_GUI, KC_8, LANG);
const key_override_t ko_9 = ko_make_basic(MOD_MASK_GUI, KC_9, KC_DEL);
const key_override_t ko_0 = ko_make_basic(MOD_MASK_GUI, KC_0, KC_BSPC);

// clang-format off
const key_override_t *key_overrides[] = {
    &ko_cmd_s, &ko_cmd_d, &ko_cmd_f, &ko_cmd_g, &ko_cmd_h, &ko_cmd_j, &ko_cmd_k, &ko_cmd_l, &ko_cmd_w, &ko_cmd_t, &ko_cmd_y, &ko_cmd_o,
    &ko_ctrl_h, &ko_ctrl_j, &ko_ctrl_k, &ko_ctrl_l, &ko_ctrl_o, &ko_ctrl_shift_f,
    &ko_7, &ko_8, &ko_9, &ko_0,
};
// clang-format on

// =============================================================================
// KEYMAP
// =============================================================================

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
    A_RCMD, KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   FN4,
    SHFTESC,KC_Z,   KC_X,   KC_C,   KC_V,   DRAG,   MOUSE,  KC_B,   KC_N,   KC_M,   _______,CTRLESC,
    KC_LCTL,_______,KC_LOPT,KC_LCMD,_______,FN2,    FN1,    FN3,    KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT
  ),
  [_FN1] = LAYOUT(
    _______,MS_ACL0,WIDG,   MC_VI99,MS_BTN1,                MS_BTN2,DOCK,   LANG,   KC_DEL, KC_BSPC,
    MC_RCMD,MS_WHLR,MS_WHLU,MS_WHLD,MS_WHLL,                MS_LEFT,MS_DOWN,MS_UP,  MS_RGHT,_______,
    _______,_______,_______,_______,_______,_______,_______,SCREEN1,PEEK,   WIN_L,  WIN_R,  SCREEN2,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
  [_FN2] = LAYOUT(
    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_LCMD,KC_LSFT,KC_LOPT,KC_GRV, KC_TAB,                 KC_MINS,KC_EQL, TD_SCLN,KC_QUOT,KC_BSLS,
    _______,_______,_______,_______,_______,MC_VI99,_______,KC_LBRC,KC_COMM,KC_DOT, KC_SLSH,KC_RBRC,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
  [_FN3] = LAYOUT(
    _______,_______,MC_VI07,MC_VI08,_______,                MC_VI05,_______,MC_VI10,MC_VI11,MC_VI12,
    _______,_______,_______,MOUSEOF,MC_VI09,                MOUSEON,MC_VI03,MC_VI06,MC_VI02,MC_VI01,
    _______,_______,_______,_______,_______,_______,_______,MC_VI04,_______,_______,_______,PASTE,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
  [_FN4] = LAYOUT(
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,
    _______,_______,CLEAR,  KC_F11, KC_F12,                 KC_BRID,KC_BRIU,KC_VOLD,KC_VOLU,_______,
    _______,_______,_______,HTML   ,_______,_______,_______,_______,_______,KC_MUTE,_______,_______,
    _______,QK_BOOT,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),
};
// clang-format on

// =============================================================================
// MODIFIER HELPERS
// =============================================================================

static bool is_lgui_pressed(void) {
    return get_mods() & MOD_BIT(KC_LGUI);
}

static bool is_rgui_pressed(void) {
    return get_mods() & MOD_BIT(KC_RGUI);
}

static bool is_shift_pressed(void) {
    return get_mods() & MOD_MASK_SHIFT;
}

static bool is_ctrl_pressed(void) {
    return get_mods() & MOD_MASK_CTRL;
}

// =============================================================================
// MOUSE LAYER: DIGITIZER JUMP
// =============================================================================

// MC_RCMD + a mouse direction key jumps instead of moving: each jump keeps one
// half of the current region and places the cursor at its centre. Each fresh
// MC_RCMD press, or MC_RCMD + Enter (centre), starts over from the whole screen.
static float jump_x0 = 0, jump_x1 = 1, jump_y0 = 0, jump_y1 = 1;

static void reset_jump(void) {
    jump_x0 = jump_y0 = 0;
    jump_x1 = jump_y1 = 1;
}

static void digitizer_move_to(float x, float y) {
    // Set position and in-range together so the cursor doesn't flick to the old spot first
    digitizer_state.x        = x;
    digitizer_state.y        = y;
    digitizer_state.in_range = true;
    digitizer_state.dirty    = true;
    digitizer_flush();
    digitizer_in_range_off();
}

static void handle_center(void) {
    reset_jump();
    digitizer_move_to(0.5f, 0.5f);
}

static void handle_jump(uint16_t keycode) {
    float mid_x = (jump_x0 + jump_x1) / 2;
    float mid_y = (jump_y0 + jump_y1) / 2;
    switch (keycode) {
        case MS_LEFT:
            jump_x1 = mid_x;
            break;
        case MS_RGHT:
            jump_x0 = mid_x;
            break;
        case MS_UP:
            jump_y1 = mid_y;
            break;
        case MS_DOWN:
            jump_y0 = mid_y;
            break;
    }

    digitizer_move_to((jump_x0 + jump_x1) / 2, (jump_y0 + jump_y1) / 2);
}

// MC_RCMD sends A while left Cmd is held, otherwise right Cmd. Release whatever the
// press sent, so toggling left Cmd mid-hold can't leave right Cmd stuck down.
static uint16_t rcmd_sent = KC_NO;

static bool handle_rcmd_key(keyrecord_t *record) {
    if (record->event.pressed) {
        rcmd_sent = is_lgui_pressed() ? KC_A : KC_RCMD;
        if (rcmd_sent == KC_RCMD) {
            reset_jump();
        }
        register_code(rcmd_sent);
    } else {
        unregister_code(rcmd_sent);
        rcmd_sent = KC_NO;
    }
    return false;
}

// =============================================================================
// MOUSE LAYER: DRAG LOCK, ENTER / EXIT
// =============================================================================

// DRAG holds the left button down until tapped again, a normal click, Esc, or leaving the layer
static bool is_dragging = false;

static void end_drag(void) {
    if (is_dragging) {
        is_dragging = false;
        unregister_code(MS_BTN1);
    }
}

// On the base layer DRAG also turns the mouse layer on, so the same key ends the drag there
static void handle_drag(void) {
    layer_on(_FN1);
    is_dragging = !is_dragging;
    if (is_dragging) {
        register_code(MS_BTN1);
    } else {
        unregister_code(MS_BTN1);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Never leave the button stuck down after leaving the mouse layer
    if (!layer_state_cmp(state, _FN1)) {
        end_drag();
    }
    return state;
}

// Esc (a tap of either Esc mod-tap) ends the drag lock. It runs on the Esc release, so macOS
// sees Esc while the button is still down and cancels the drag instead of dropping.
static bool is_esc_tap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ESC:
            return true;
        case SHFTESC:
        case CTRLESC:
            return record->tap.count > 0;
    }
    return false;
}

// Keys that leave the mouse layer when pressed, because typing usually follows:
// ` or Z alone; Ctrl + Z, C or L; left Cmd (alone) + L, F, T or a Space thumb key.
static bool exits_mouse_layer(uint16_t keycode) {
    uint8_t mods = get_mods();
    if (mods == 0) {
        return keycode == KC_GRV || keycode == KC_Z;
    }
    if (mods == MOD_BIT(KC_LCTL) || mods == MOD_BIT(KC_RCTL)) {
        return keycode == KC_Z || keycode == KC_C || keycode == MS_RGHT;
    }
    if (mods == MOD_BIT(KC_LCMD)) {
        switch (keycode) {
            case MS_WHLD:
            case MS_RGHT:
            case MS_BTN1:
            case FN1:
            case FN2:
            case FN3:
                return true;
        }
    }
    return false;
}

static void handle_mouse_toggle(void) {
    if (is_shift_pressed() || is_ctrl_pressed()) {
        layer_off(_FN1);
    } else {
        layer_on(_FN1);
    }
}

// =============================================================================
// VIM / TMUX SHORTCUTS
// =============================================================================

// ESC to normal mode, then <leader> (Space) + key
static void send_leader(char key) {
    SEND_STRING(SS_TAP(X_ESC) SS_DELAY(50) SS_TAP(X_SPACE));
    send_char(key);
}

static void handle_vi_command(uint16_t keycode) {
    switch (keycode) {
        case MC_VI01: // find files
            send_leader(';');
            break;
        case MC_VI02: // projects
            send_leader('l');
            break;
        case MC_VI03: // live grep
            send_leader('j');
            break;
        case MC_VI04: // buffers
            send_leader('b');
            break;
        case MC_VI05: // resume picker
            send_leader('\'');
            break;
        case MC_VI06: // file browser
            send_leader('k');
            break;
        case MC_VI07: // emmet
            SEND_STRING(SS_LCTL("j"));
            break;
        case MC_VI08: // DiffviewOpen
            send_leader('r');
            break;
        case MC_VI09: // DiffviewFileHistory
            send_leader('f');
            break;
        case MC_VI10: // notes
            send_leader('i');
            break;
        case MC_VI11: // tmux: opencode
            SEND_STRING(SS_LCTL("o"));
            break;
        case MC_VI12: // tmux: cursor
            SEND_STRING(SS_LCTL("p"));
            break;
    }
}

// Save; with left Cmd held it's Cmd+R, with right Cmd held a plain R
static void handle_vi99_command(void) {
    if (is_lgui_pressed()) {
        SEND_STRING("r");
    } else if (is_rgui_pressed()) {
        uint8_t mods = get_mods();
        del_mods(MOD_BIT(KC_RGUI));
        tap_code16(KC_R);
        set_mods(mods);
    } else {
        send_leader('w');
    }
}

// =============================================================================
// WINDOW / SCREEN / TERMINAL SHORTCUTS
// =============================================================================

// Each key has a left-Cmd/Shift and a right-Cmd variant on top of its default action
static void handle_utility_command(uint16_t keycode) {
    switch (keycode) {
        case PEEK:
            if (is_lgui_pressed() || is_shift_pressed()) {
                SEND_STRING("n");
            } else if (is_rgui_pressed()) {
                SEND_STRING(SS_LCTL(","));
            } else {
                tap_code16(LCTL(KC_UP));
            }
            break;
        case WIN_L:
            if (is_lgui_pressed() || is_shift_pressed()) {
                SEND_STRING("m");
            } else if (is_rgui_pressed()) {
                SEND_STRING(SS_LCTL("."));
            } else {
                tap_code16(LCTL(KC_LEFT));
            }
            break;
        case WIN_R:
            if (is_rgui_pressed()) {
                SEND_STRING(SS_LCTL("/"));
            } else {
                tap_code16(LCTL(KC_RIGHT));
            }
            break;
        case SCREEN1:
            if (is_lgui_pressed() || is_shift_pressed()) {
                SEND_STRING("b");
            } else if (is_rgui_pressed()) {
                SEND_STRING("[");
            } else {
                tap_code16(LGUI(LSFT(KC_LBRC)));
            }
            break;
        case SCREEN2:
            if (is_rgui_pressed()) {
                SEND_STRING("]");
            } else {
                tap_code16(LGUI(LSFT(KC_RBRC)));
            }
            break;
        case CLEAR:
            SEND_STRING(SS_LCTL("`") SS_DELAY(50) SS_LCTL("l"));
            break;
    }
}

// =============================================================================
// KEY PROCESSING
// =============================================================================

// MC_RCMD + Enter centres the cursor. Handled before tap/hold resolution so it fires
// on press, and the matching release is swallowed so Enter/FN4 never sees either.
static bool is_centering = false;

// Holding A adds right Cmd on top of the layer the LT turns on. If another key was pressed
// during the hold, FN1 stays on after A is released (as if MOUSE was tapped); if not, it goes off.
static bool is_a_held = false;
static bool is_a_used = false;

static bool handle_a_rcmd_hold(keyrecord_t *record) {
    if (record->event.pressed) {
        is_a_held = true;
        is_a_used = false;
        reset_jump();
        register_mods(MOD_BIT(KC_RGUI));
        return true;
    }
    is_a_held = false;
    unregister_mods(MOD_BIT(KC_RGUI));
    // Skipping the LT release skips its layer_off
    return !is_a_used;
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (is_a_held && record->event.pressed && keycode != A_RCMD) {
        is_a_used = true;
    }
    if (keycode == FN4) {
        if (record->event.pressed && is_rgui_pressed()) {
            is_centering = true;
            handle_center();
            return false;
        }
        if (!record->event.pressed && is_centering) {
            is_centering = false;
            return false;
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && layer_state_is(_FN1) && exits_mouse_layer(keycode)) {
        layer_off(_FN1);
    }

    if (keycode == MC_RCMD) {
        return handle_rcmd_key(record);
    }

    if (keycode == A_RCMD && record->tap.count == 0) {
        return handle_a_rcmd_hold(record);
    }

    if (!record->event.pressed && is_dragging && is_esc_tap(keycode, record)) {
        end_drag();
    }

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case MC_VI01 ... MC_VI12:
            handle_vi_command(keycode);
            return false;
        case MC_VI99:
            handle_vi99_command();
            return false;
        case MS_LEFT:
        case MS_DOWN:
        case MS_UP:
        case MS_RGHT:
            // Right Cmd jumps; left Cmd keeps its HJKL overrides
            if (is_rgui_pressed()) {
                handle_jump(keycode);
                return false;
            }
            return true;
        case MS_BTN1:
            // A normal click while drag-locked releases the button, so end the lock too
            is_dragging = false;
            return true;
        case DRAG:
            handle_drag();
            return false;
        case MOUSE:
            handle_mouse_toggle();
            return false;
        case MOUSEON:
            layer_on(_FN1);
            return false;
        case MOUSEOF:
            layer_off(_FN1);
            return false;
        case PEEK:
        case WIN_L:
        case WIN_R:
        case SCREEN1:
        case SCREEN2:
        case CLEAR:
            handle_utility_command(keycode);
            return false;
    }
    return true;
}
