// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


bool shift = false;

enum layer_names {
    camph,
    ctrl,
    cursor,
    pgud,
};


void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(D2);
  setPinOutput(D3);
  writePinLow(D2);
  writePinLow(D3);
}


enum custom_keycodes {
  SHIFT_HOLD = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ C │ A │ M │ - │
     * ├───┼───┼───┼───┤
     * │ P │ H │ O │ R │
     * └───┴───┴───┴───┘
     */
    [camph] = LAYOUT_ortho_2x4(
        KC_C,    KC_A,    KC_M,    MO(ctrl),
        KC_P,    KC_H,    KC_O,    KC_R
    ),
    [ctrl] = LAYOUT_ortho_2x4(
	KC_UNDO, KC_AGAIN, KC_MENU, MO(cursor),
	KC_CUT, KC_COPY, KC_PASTE, SHIFT_HOLD

    ),
    [cursor] = LAYOUT_ortho_2x4(
	KC_INSERT, KC_UP, KC_PRINT_SCREEN, MO(camph),
	KC_LEFT, KC_DOWN, KC_RIGHT, MO(pgud)
    ),
    [pgud] = LAYOUT_ortho_2x4(
	KC_INSERT, KC_PAGE_UP, KC_PRINT_SCREEN, MO(camph),
	KC_HOME, KC_PAGE_DOWN, KC_RIGHT, MO(cursor)
)
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [camph] = {ENCODER_CCW_CW(KC_LEFT, KC_RIGHT),},
    [ctrl] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU),},
    [cursor] = {ENCODER_CCW_CW(KC_BRID,KC_BRIU),},
    [pgud] = {ENCODER_CCW_CW(KC_BRID,KC_BRIU),},
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SHIFT_HOLD:
//      if (record->event.pressed) {
//        register_code(KC_KB_MUTE);
//      } else {
//        unregister_code(KC_KB_MUTE);
//      }
      if(shift)
	unregister_code(KC_LSFT);
      else
	register_code(KC_LSFT);
      shift = !shift;
      break;
  }
  return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case camph:
      writePin(D2, true);
      writePin(D3, false);
      break;
    case ctrl:
      writePin(D2, false);
      writePin(D3, true);
      break;
    case cursor:
      writePin(D2, true);
      writePin(D3, true);
      break;
    }
    return state;
}
