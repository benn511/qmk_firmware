#include QMK_KEYBOARD_H

enum layers {
    _COPY_LAYER = 0,
    _LOWER = 1,
    _NUMBER = 2
};

enum custom_keycodes {
  ITEM_UNIT = SAFE_RANGE,
  DEALER_ID,

};

// Readability keycodes
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)

// MACROS
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ITEM_UNIT:
        if (record->event.pressed) {
            SEND_STRING("<item unitid");
        } else {
        }
        break;
    case DEALER_ID:
        if (record->event.pressed) {
            SEND_STRING("<dealerid>");
        } else {
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COPY_LAYER] = LAYOUT(
  DEALER_ID,  ITEM_UNIT,    RESET,    KC_ENTER,
  C(KC_F),  KC_F5,    C(KC_W),    C(KC_T),
  C(KC_BSPACE),  C(KC_A),    C(KC_C),    C(KC_V)
  ),
  [_NUMBER] = LAYOUT(
    KC_0, KC_1, KC_4, KC_7,
    KC_DOT, KC_2, KC_5, KC_8,
    _______, KC_3, KC_6, KC_9
  )

};
