/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

#define _BASE_LAYER 0
#define _SPACE_LAYER 1
#define _FN_LAYER 2
#define _ALT_LAYER 3
#define _COLEMAK_LAYER 4

//Tap Dance Declarations
enum custom_tapdance {
  TD_LEFT_CURLY = 0,
  TD_HOME_DANCE = 1,
  TD_RIGHT_CURLY = 2,
  TD_QUOTES = 3,
//   TD_SPC_ENT = 0,
};

// custom keycodes
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    SPLIT_EDITOR,
    GIT_ADD,
    GIT_COMMIT,
    GIT_PUSH
};

// MACROS
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            SEND_STRING("QMK is the best thing ever!");
        } else {
        }
        break;
    case SPLIT_EDITOR:
        if (record->event.pressed) {
            tap_code16(C(KC_BSLS));
            wait_ms(500);
            register_code(KC_LALT);
            tap_code16(S(KC_LEFT));
            wait_ms(500);
            clear_keyboard();
            tap_code16(C(KC_W));
        } else {
            // safeguard to clear board in case of bugs
            clear_keyboard();
        }
        break;
    case GIT_ADD:
        if (record->event.pressed) {
            SEND_STRING("git add .");
        } else {
        }
        break;
    case GIT_COMMIT:
        if (record->event.pressed) {
           SEND_STRING("git commit -m '"); // selects all and copies
        } else {
        }
        break;
    case GIT_PUSH:
        if (record->event.pressed) {
           SEND_STRING("git push"); // selects all and copies
        } else {
        }
        break;
    }
    return true;
};

// Quotes tap dance
void dance_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_QUOTE);
    } else {
        register_code16(KC_LSFT);
        register_code(KC_QUOTE);
    }
}

void dance_quote_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_QUOTE);
    } else {
        unregister_code16(KC_LSFT);
        unregister_code(KC_QUOTE);
    }
}
// Curly brace tap dance
void dance_curly_left_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LSFT);
        register_code(KC_LBRACKET);
    } else {
        register_code(KC_LBRACKET);
    }
}

void dance_curly_left_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_LSFT);
        unregister_code(KC_LBRACKET);
    } else {
        unregister_code16(KC_LBRACKET);
    }
}

// Right bracket tap dance
void dance_curly_right_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LSFT);
        register_code(KC_RBRACKET);
    } else {
        register_code(KC_RBRACKET);
    }
}

void dance_curly_right_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_LSFT);
        unregister_code(KC_RBRACKET);
    } else {
        unregister_code16(KC_RBRACKET);
    }
}

// Home tap dance 1: regular, 2: shift home, 3: ctrl + home
void dance_home_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_HOME);
    }
    else if (state->count == 2)
    {
        register_code(KC_LSFT);
        register_code(KC_HOME);

    }
    else if (state->count == 3) {
        register_code(KC_LCTL);
        register_code(KC_HOME);
    }
}

void dance_home_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_HOME);
    } else if (state->count == 2)
    {
        unregister_code(KC_LSFT);
        unregister_code(KC_HOME);

    }
    else if (state->count == 3) {
        unregister_code(KC_LCTL);
        unregister_code(KC_HOME);

    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFT_CURLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_curly_left_finished, dance_curly_left_reset),
  [TD_HOME_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_home_finished, dance_home_reset),
  [TD_RIGHT_CURLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_curly_right_finished, dance_curly_right_reset),
  [TD_QUOTES] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_quote_finished, dance_quote_reset),
};
//   [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENTR),
//   [TD_SEMICOLON_COLON] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    [_BASE_LAYER] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DELETE,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,

        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD(TD_LEFT_CURLY), TD(TD_RIGHT_CURLY), KC_BSLS,          KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, TD(TD_QUOTES),          KC_ENT,           TD(TD_HOME_DANCE),
        KC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, LM(_ALT_LAYER, MOD_LALT),                            LT(_SPACE_LAYER,KC_SPC),                             KC_RALT, TT(_COLEMAK_LAYER),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_SPACE_LAYER] = LAYOUT(
        KC_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DELETE,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC,          _______,

        _______, KC_Q, KC_LBRACKET, KC_ESC, S(KC_7), KC_T, KC_Y, KC_MINS, S(KC_DOT), S(KC_LBRACKET), _______, GIT_ADD, GIT_COMMIT, SPLIT_EDITOR,            _______,
        _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), KC_HOME, KC_END, S(KC_MINUS), S(KC_EQUAL), S(KC_QUOTE), KC_EQUAL, _______,          _______,          _______,
        _______,          _______, _______, S(KC_1), KC_EQUAL, KC_B, C(KC_BSPC), KC_BSPC, _______, _______, S(KC_BSLASH),          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, C(S(KC_LEFT)), _______, C(S(KC_RIGHT))
    ),
    [_FN_LAYER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, KC_7, KC_8, KC_9, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,

        _______, _______, KC_4, KC_5, KC_6, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, KC_1, KC_2, KC_3, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, C(KC_X), C(KC_C), C(KC_V), _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_ALT_LAYER] = LAYOUT(
        KC_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,

        _______, _______, _______, _______, _______, _______, _______, _______, KC_UP, _______, _______, _______, _______, RESET,            _______,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_COLEMAK_LAYER] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DELETE,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,

        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    TD(TD_LEFT_CURLY), TD(TD_RIGHT_CURLY), KC_BSLS,          KC_PGDN,
        KC_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, TD(TD_QUOTES),          KC_ENT,           TD(TD_HOME_DANCE),
        KC_LSPO,          KC_X,    KC_C,    KC_D,    KC_V,    KC_Z,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, LM(_ALT_LAYER, MOD_LALT),                            LT(_SPACE_LAYER,KC_SPC),                             KC_RALT, _______,   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

};

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (IS_HOST_LED_ON(led_caps)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(3, 255, 0, 0); //capslock key
    }
    if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(67, 0, 255, 0); //side led 01
        RGB_MATRIX_INDICATOR_SET_COLOR(70, 0, 255, 0); //side led 02
        RGB_MATRIX_INDICATOR_SET_COLOR(73, 0, 255, 0); //side led 03
    }
    if (!IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {   // on if NUM lock is OFF
    RGB_MATRIX_INDICATOR_SET_COLOR(83, 255, 0, 255); //side led 06
    RGB_MATRIX_INDICATOR_SET_COLOR(87, 255, 0, 255); //side led 07
        RGB_MATRIX_INDICATOR_SET_COLOR(91, 255, 0, 255); //side led 08
    }

       switch(get_highest_layer(layer_state)){  // special handling per layer
            case 1:  //layer one
                RGB_MATRIX_INDICATOR_SET_COLOR(0, 255, 0, 255); //esc
                break;
            case 2:
                RGB_MATRIX_INDICATOR_SET_COLOR(0, 255, 0, 255); //esc
                break;
            case 3:
                rgb_matrix_set_color_all(255, 255, 0)
                break;
            default:
                break;
            break;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}

void keyboard_post_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_set_color_all(RGB_NAUTILUS); // Default startup colour
    #endif
}
