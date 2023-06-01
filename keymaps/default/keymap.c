// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool mute = false;

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(D2);
  setPinOutput(D3);
  writePinLow(D2);
  writePinLow(D3);
}


enum custom_keycodes {
  MUTE_AND_TOGGLE = SAFE_RANGE,
  VOLD_LED,
  VOLU_LED,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ C │ A │ M │ - │
     * ├───┼───┼───┼───┤
     * │ P │ H │ O │ R │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_2x4(
        KC_C,    KC_A,    KC_M,    MUTE_AND_TOGGLE,
        KC_P,    KC_H,    KC_O,    KC_R
    )
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    {ENCODER_CCW_CW(VOLD_LED, VOLU_LED),},
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MUTE_AND_TOGGLE:
      if (record->event.pressed) {
        register_code(KC_KB_MUTE);
        mute = !mute;
        writePin(D2, mute);
      } else {
        unregister_code(KC_KB_MUTE);
      }
      break;
    case VOLD_LED:
      if (record->event.pressed) {
        register_code(KC_VOLD);
        writePin(D2, true);
      } else {
        unregister_code(KC_VOLD);
        if (!mute)
          writePin(D2, false);
      }
      break;
    case VOLU_LED:
      if (record->event.pressed) {
        register_code(KC_VOLU);
        mute = false;
        writePin(D2, false);
        writePin(D3, true);
      } else {
        unregister_code(KC_VOLU);
        writePin(D3, false);
      }
      break;
  }
  return true;
}
