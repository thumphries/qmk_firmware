/*
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

// Layer shorthand
enum layer {
    _BASE,
    _NAV,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_hhkb(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_EQL,  KC_MINS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    M(4),    M(3),    KC_H,    KC_J,    KC_K,    KC_L,    LT(_FN, KC_SCLN), KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    M(4),    M(3),    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                MO(_NAV), MO(_FN), _______, KC_LGUI,          KC_SPC,  KC_ENT,           MO(_FN), KC_LALT, _______, TG(_NAV)
    ),

    [_NAV] = LAYOUT_ortho_hhkb(
       TG(_NAV), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, TG(_NAV), _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
                 _______, _______, KC_HOME, KC_END,           _______, _______,          KC_PGUP, KC_PGDN,  _______, TG(_NAV)
    ),

    [_FN] = LAYOUT_ortho_hhkb(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        M(5),    _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_MPLY,
        _______, RGB_TOG, _______, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, KC_MUTE, KC_MPRV, KC_MNXT, KC_BSLS, _______,
                 _______, _______, _______, _______,          _______, _______,          KC_PGUP, KC_PGDN, _______, RESET
    )
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 1:
          if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_BSPC);
            unregister_code(KC_LALT);
            unregister_code(KC_BSPC);
          }
          break;
        case 2:
          if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_D);
            unregister_code(KC_LALT);
            unregister_code(KC_D);
          }
          break;
        case 3:
          if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_B);
            unregister_code(KC_LCTL);
            unregister_code(KC_B);
          }
          break;
        case 4:
          if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_X);
            unregister_code(KC_LCTL);
            unregister_code(KC_X);
          }
          break;
        case 5:
          if (record->event.pressed) {
            register_code(KC_LALT);
            register_code(KC_LCTL);
            register_code(KC_F11);
            unregister_code(KC_F11);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
          }
          break;
      }
    return MACRO_NONE;
};


// RGB stuff
void matrix_init_user(void) {
    eeconfig_init();
    rgblight_enable();
    rgblight_setrgb(0x00,  0xFF, 0xFF);
};

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _NAV:
        rgblight_setrgb (0xD4,  0x67, 0x65);
        break;
    case _FN:
        rgblight_setrgb (0x73,  0x2A, 0x47);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0x0B,  0x32, 0x4D);
        break;
    }
  return state;
}
