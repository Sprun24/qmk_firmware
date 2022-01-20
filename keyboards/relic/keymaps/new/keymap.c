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
  FN
};

enum combo_events {
  COMBO_ESC,
};

//key overrides

const key_override_t colon_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COLN, KC_SCLN);
// This globally defines all key overrides to be used

const key_override_t **key_overrides = (const key_override_t *[]){
    &colon_key_override,
    NULL // Null terminate the array of overrides!
};


// HOMEROW MODS STUFF

#define LOWERSP LT(NUM, KC_SPC)
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

// Tap Dance declarations
enum {
    TD_QUOT_COLN,
    TD_PUNC,
    TD_LBC,
    TD_RBC,
};
//punctuation cycle
void punctuation_cycle_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            register_code16(KC_DOT);
            break;
        case 2:
            register_code16(KC_COMM);
            break;
        case 3:
            register_code16(KC_QUES);
            break;
        case 4:
            register_code16(KC_EXLM);
            break;
    }
}
void punctuation_cycle_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            unregister_code16(KC_DOT);
            break;
        case 2:
            unregister_code16(KC_COMM);
            break;
        case 3:
            unregister_code16(KC_QUES);
            break;
        case 4:
            unregister_code16(KC_EXLM);
            break;
    }
}

//left bracket cycle
void left_bracket_cycle_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            register_code16(KC_LPRN);
            break;
        case 2:
            register_code16(KC_LBRC);
            break;
        case 3:
            register_code16(KC_LCBR);
            break;
        case 4:
            register_code16(KC_LT);
            break;
    }
}
void left_bracket_cycle_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            unregister_code16(KC_LPRN);
            break;
        case 2:
            unregister_code16(KC_LBRC);
            break;
        case 3:
            unregister_code16(KC_LCBR);
            break;
        case 4:
            unregister_code16(KC_LT);
            break;
    }
}

//right bracket cycle
void right_bracket_cycle_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            register_code16(KC_RPRN);
            break;
        case 2:
            register_code16(KC_RBRC);
            break;
        case 3:
            register_code16(KC_RCBR);
            break;
        case 4:
            register_code16(KC_GT);
            break;
    }
}
void right_bracket_cycle_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            unregister_code16(KC_RPRN);
            break;
        case 2:
            unregister_code16(KC_RBRC);
            break;
        case 3:
            unregister_code16(KC_RCBR);
            break;
        case 4:
            unregister_code16(KC_GT);
            break;
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for QUOT, twice for COLN
    [TD_QUOT_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_COLN),
    [TD_PUNC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, punctuation_cycle_finished, punctuation_cycle_reset),
    [TD_LBC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_bracket_cycle_finished, left_bracket_cycle_reset),
    [TD_RBC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_bracket_cycle_finished, right_bracket_cycle_reset),
};

// Custom auto shifts
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_QUOT:
            return true;
        default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_QUOT:
            register_code16((!shifted) ? KC_Z : KC_CAPS);
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }

    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_QUOT:
            unregister_code16((!shifted) ? KC_Z : KC_CAPS);
            break;
        default:
            return;
    }
}



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*  BASE
 * ┌─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  Q  │  W  │  E  │  R  │  T  │     │  Y  │  U  │  I  │  O  │  P  │BACK │
 * ├─────┴─┬───┴─┬───┴─┬───┴─┬───┴─┐   └─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─────┤
 * │ A/GUI │S/ALT│D/CTL│F/SFT│  G  │     │  H  │J/SFT│K/CTL│L/ALT│QUOT/COLN/SEMICOLN│
 * ├───────┴──┬──┴──┬──┴──┬──┴──┬──┴──┐  └──┬──┴──┬──┴──┬──┴──┬──┴──┬──────┤
 * │  Z/CAPS  │  X  │  C  │  V  │  B  │     │  N  │  M  │PUNC │ DMS │ DMP  │
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
 * long tap on quote for semicolon
 * double tap quote for colon
 * bs key toggles the stupid shit
 * DMS and DMP are dynamic macro start and play keys
 */

  [BASE] = LAYOUT_all(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_GA,    KC_AS,    KC_CD,    KC_SF,    KC_G,    KC_H,    KC_SJ,    KC_CK,    KC_AL,    TD(TD_QUOT_COLN),   
     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    TD(TD_PUNC), KC_NO,  KC_SLSH,  
      SCREENSHOT, DESKTOP,    KC_TAB , LOWERSP, KC_NO, RAISEENT, MO(FN),      KC_VOLD, KC_VOLU
  ),

/*  NUM
 * ┌─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │ HOME│ Up  │END  │     │     │     │  +  │  7  │  8  │  9  │  .  │BACK │
 * ├─────┴─┬───┴─┬───┴─┬───┴─┬───┴─┐   └─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─────┤
 * │ LEFT  │ DOWN│RIGHT│BSLS │     │     │  *  │  4  │  5  │  6  │    0    │
 * ├───────┴──┬──┴──┬──┴──┬──┴──┬──┴──┐  └──┬──┴──┬──┴──┬──┴──┬──┴──┬──────┤
 * │     -    │     │  L  │  R  │  _  │     │  =  │  1  │  2  │  3  │      │
 * └──┬──────┬┴─────┼─────┴─────┴─────┘     └─────┴─────┴──┬──┴───┬─┴────┬─┘
 *    │  SS  │  DT  │                                      │ VOLU │ VOLD │
 *    └──────┴──────┘ ┌─────┬──────────┬──────────┬─────┐  └──────┴──────┘
 *                    │ TAB │  SPACE   │  RETURN  │TO(0)│
 *                    └─────┴──────────┴──────────┴─────┘
 * L and R keys go through ([{< and )]}> in order on taps
 * Auto shift on numbers
 */

  [NUM] = LAYOUT_all(
    KC_HOME,    KC_UP,       KC_END,     KC_NO,    KC_NO,    KC_PLUS,    KC_7,    KC_8,    KC_9,    KC_PDOT,    KC_BSPC,
    KC_LEFT,    KC_DOWN,     KC_RIGHT,   KC_BSLS,  KC_NO,    KC_ASTR,    KC_4,    KC_5,    KC_6,    KC_0,   
     KC_MINS,   KC_NO,       TD(TD_LBC),    TD(TD_RBC),  KC_UNDS,  KC_EQL,     KC_1,    KC_2,    KC_3,    KC_NO,  
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
         SCREENSHOT, DESKTOP,    KC_TAB , TG(NUM), KC_NO, TG(NUM), KC_TRNS,      KC_VOLU, KC_VOLD
  ),
};

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_esc[] = {KC_Q, KC_W, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),

};
#endif

