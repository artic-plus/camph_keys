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


void backlight_init_ports(void) {
    // Optional - runs on startup
    //   Usually you want to configure pins here
  setPinOutput(D2);
  setPinOutput(D3);
  writePinLow(D2);
  writePinHigh(D3);
}
void backlight_set(uint8_t level) {
    // Optional - runs on level change
    //   Usually you want to respond to the new value
    switch (level){
    case 1:
      writePinLow(D2);
      writePinHigh(D3);
      break;
    case 2:
      writePinHigh(D2);
      writePinLow(D3);
      break;
    case 3:
      writePinHigh(D2);
      writePinHigh(D3);
      break;
    }
//  writePin(D2, level && 2);
//  writePin(D3, level && 1);
}

void backlight_task(void) {
    // Optional - runs periodically
    //   Note that this is called in the main keyboard loop,
    //   so long running actions here can cause performance issues
}


/*
void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(D2);
  setPinOutput(D3);
  writePinLow(D2);
  writePinLow(D3);
}
*/


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
        KC_C,    KC_A,    KC_M,    DF(ctrl),
        KC_P,    KC_H,    KC_O,    KC_R
    ),
    [ctrl] = LAYOUT_ortho_2x4(
	KC_UNDO, KC_AGAIN, KC_MENU, DF(cursor),
	KC_CUT, KC_COPY, KC_PASTE, SHIFT_HOLD

    ),
    [cursor] = LAYOUT_ortho_2x4(
	KC_INSERT, KC_UP, KC_PRINT_SCREEN, DF(camph),
	KC_LEFT, KC_DOWN, KC_RIGHT, MO(pgud)
    ),
    [pgud] = LAYOUT_ortho_2x4(
	KC_INSERT, KC_PAGE_UP, KC_PRINT_SCREEN, DF(camph),
	KC_HOME, KC_PAGE_DOWN, KC_END, MO(cursor)
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


layer_state_t default_layer_state_set_kb(layer_state_t state) {
    switch (biton32(default_layer_state)) {
    case camph:
      backlight_set(1);
      break;
    case ctrl:
      backlight_set(2);
      break;
    case cursor:
      backlight_set(3);
      break;
    case pgud:
      backlight_set(2);
    }
    return state;
}

