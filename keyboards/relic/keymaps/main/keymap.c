/* Copyright 2021 projectcain
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
enum layers{
  BASE,
  NUM,
  NAV,
  FN
};

enum combo_events {
  COMBO_ESC,
};

// HOMEROW MODS STUFF

#define LOWERSP LT(NAV, KC_SPC)
#define RAISEENT LT(NUM, KC_ENT)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
#define KC_GA LGUI_T(KC_A)
#define KC_AS LALT_T(KC_S)
#define KC_CD LCTL_T(KC_D)
#define KC_CK RCTL_T(KC_K)
#define KC_AL RALT_T(KC_L)


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
            return TAPPING_TERM + 300;
        case LALT_T(KC_S):
            return TAPPING_TERM + 120;
        case RALT_T(KC_L):
            return TAPPING_TERM + 400;
        case LCTL_T(KC_D):
            return TAPPING_TERM + 40;
        case RCTL_T(KC_K):
            return TAPPING_TERM + 200;
        default:
            return TAPPING_TERM;
    }
}

// macros
enum custom_keycodes {
    SCREENSHOT = SAFE_RANGE,
    DESKTOP,
    
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SCREENSHOT:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING(SS_LSFT(SS_LGUI("s")));
        } else {
            // when keycode is released
        }
        break;
      case DESKTOP:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING(SS_LGUI("d"));
        } else {
            // when keycode is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*  BASE
 * ┌─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  Q  │  W  │  E  │  R  │  T  │     │  Y  │  U  │  I  │  O  │  P  │BACK │
 * ├─────┴─┬───┴─┬───┴─┬───┴─┬───┴─┐   └─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─────┤
 * │ A/GUI │S/ALT│D/CTL│F/SFT│  G  │     │  H  │J/SFT│K/CTL│L/ALT│  QUOT   │
 * ├───────┴──┬──┴──┬──┴──┬──┴──┬──┴──┐  └──┬──┴──┬──┴──┬──┴──┬──┴──┬──────┤
 * │     Z    │  X  │  C  │  V  │  B  │     │  N  │  M  │ COM │ DOT │ SLSH │
 * └──┬──────┬┴─────┼─────┴─────┴─────┘     └─────┴─────┴──┬──┴───┬─┴────┬─┘
 *    │  SS  │  DT  │                                      │ VOLU │ VOLD │
 *    └──────┴──────┘ ┌─────┬──────────┬──────────┬─────┐  └──────┴──────┘
 *                    │ TAB │  SPACE   │  RETURN  │ FN1 │
 *                    └─────┴──────────┴──────────┴─────┘
 * 
 * SS = screenshot
 * DT = desktop
 * Q + W = ESC Combo
 * Long tap z for caps
 */

  [BASE] = LAYOUT_all(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_GA,    KC_AS,    KC_CD,    KC_SF,    KC_G,    KC_H,    KC_SJ,    KC_CK,    KC_AL,    KC_QUOTE,   
     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  
      SCREENSHOT, DESKTOP,    KC_TAB , LOWERSP, KC_NO, RAISEENT, MO(FN),      KC_VOLD, KC_VOLU
  ),

/*  NUM
 * ┌─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  !  │  @  │  #  │  $  │  %  │     │  ^  │  &  │  *  │  =  │  +  │BACK │
 * ├─────┴─┬───┴─┬───┴─┬───┴─┬───┴─┐   └─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─────┤
 * │   1   │  2  │  3  │  4  │  5  │     │  6  │  7  │  8  │  9  │    0    │
 * ├───────┴──┬──┴──┬──┴──┬──┴──┬──┴──┐  └──┬──┴──┬──┴──┬──┴──┬──┴──┬──────┤
 * │     -    │  {  │  [  │  (  │  _  │     │  )  │  ]  │  }  │ COM │ QUES │
 * └──┬──────┬┴─────┼─────┴─────┴─────┘     └─────┴─────┴──┬──┴───┬─┴────┬─┘
 *    │  SS  │  DT  │                                      │ VOLU │ VOLD │
 *    └──────┴──────┘ ┌─────┬──────────┬──────────┬─────┐  └──────┴──────┘
 *                    │ TAB │  SPACE   │  RETURN  │TO(0)│
 *                    └─────┴──────────┴──────────┴─────┘
 * 
 *
 */

  [NUM] = LAYOUT_all(
    KC_EXLM,    KC_AT,    KC_HASH,    KC_DLR,    KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_EQL,    KC_PLUS,    KC_BSPC,
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   
     KC_MINS,    KC_LCBR,    KC_LBRC,    KC_LPRN,    KC_UNDS,    KC_RPRN,    KC_RBRC,    KC_RCBR, KC_COMM,  KC_QUES,  
         SCREENSHOT, DESKTOP,    KC_TAB , LOWERSP, KC_NO, RAISEENT, TO(BASE),      KC_VOLU, KC_VOLD
  ),
  

/*  NAV
 * ┌─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │Home │ Up  │ End │ PIPE│  t  │     │  ^  │  &  │  *  │  =  │  +  │  :  │
 * ├─────┴─┬───┴─┬───┴─┬───┴─┬───┴─┐   └─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─────┤
 * │ Left  │ Down│Right│BSLS │  g  │     │  6  │  7  │  8  │  9  │    ;    │
 * ├───────┴──┬──┴──┬──┴──┬──┴──┬──┴──┐  └──┬──┴──┬──┴──┬──┴──┬──┴──┬──────┤
 * │   Caps   │  x  │  c  │  v  │  b  │     │  n  │  m  │ COM │ DOT │ SLSH │
 * └──┬──────┬┴─────┼─────┴─────┴─────┘     └─────┴─────┴──┬──┴───┬─┴────┬─┘
 *    │  SS  │  DT  │                                      │ VOLU │ VOLD │
 *    └──────┴──────┘ ┌─────┬──────────┬──────────┬─────┐  └──────┴──────┘
 *                    │ TAB │  SPACE   │  RETURN  │TO(0)│
 *                    └─────┴──────────┴──────────┴─────┘
 * 
 */
  [NAV] = LAYOUT_all(
    KC_HOME,    KC_UP,      KC_END,     KC_PIPE,    KC_BSLS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_COLN,    KC_TRNS,
    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_BSLS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_SCLN,   
     KC_CAPS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_SLSH,  
         SCREENSHOT, DESKTOP,    KC_TAB , LOWERSP, KC_NO, RAISEENT, TO(BASE),      KC_VOLU, KC_VOLD
  ),
/*  FN
 * ┌─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │ F1  │ F2  │ F3  │ F4  │  F5 │     │  F6 │  F7 │  F8 │ F9  │ F10 │ F11 │
 * ├─────┴─┬───┴─┬───┴─┬───┴─┬───┴─┐   └─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─────┤
 * │ a     │  s  │ d   │  f  │  g  │     │  h  │  j  │  k  │  l  │  f12    │
 * ├───────┴──┬──┴──┬──┴──┬──┴──┬──┴──┐  └──┬──┴──┬──┴──┬──┴──┬──┴──┬──────┤
 * │   RESET  │  x  │  c  │  v  │  b  │     │  n  │  m  │ COM │ DOT │ SLSH │
 * └──┬──────┬┴─────┼─────┴─────┴─────┘     └─────┴─────┴──┬──┴───┬─┴────┬─┘
 *    │  SS  │  DT  │                                      │ VOLU │ VOLD │
 *    └──────┴──────┘ ┌─────┬──────────┬──────────┬─────┐  └──────┴──────┘
 *                    │ TAB │ LOCK NAV │ LOCK NUM │     │
 *                    └─────┴──────────┴──────────┴─────┘
 * 
 *
 */
  [FN] = LAYOUT_all(
    KC_F1,    KC_F2,      KC_F3,     KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,
    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_BSLS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_F12,   
     RESET,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_SLSH,  
         SCREENSHOT, DESKTOP,    KC_TAB , TG(NAV), KC_NO, TG(NUM), KC_TRNS,      KC_VOLU, KC_VOLD
  ),
};

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_esc[] = {KC_Q, KC_W, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),

};
#endif

