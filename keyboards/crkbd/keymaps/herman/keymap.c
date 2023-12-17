// Copyright 2022 Mark Stosberg (@markstos)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45 //Switch to fast animation when over words per minute

#ifdef OLED_ENABLE
#include "demon.c"
#endif

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC,
  NEXT_TAB,
  PREV_TAB,
  NEXT_WORD,
  PREV_WORD,
  MCOPY,
  MPASTE,
  JTSEARCH,
  FORMAT_CODE,
};

enum combos {
  DF_DASH,
  ER_UNDERSCORE,
  CV_SEMICOLON,
  JK_ESC,
  SD_COLON
};

const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM er_combo[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};

combo_t key_combos[] = {
  // Add commonly used dash, underscore, and semicolon to home row
  [DF_DASH]         = COMBO(df_combo, KC_MINS),
  [ER_UNDERSCORE]   = COMBO(er_combo, LSFT(KC_MINS)),
  [CV_SEMICOLON]    = COMBO(cv_combo, KC_SEMICOLON),
  [SD_COLON]        = COMBO(sd_combo, KC_COLON),
  // For Vim, put Escape on the home row
  [JK_ESC]    = COMBO(jk_combo, KC_ESC),
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNC,
};

// For _QWERTY layer
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_AGR  OSM(MOD_RALT)
#define OSL_FUN  OSL(_FUNC)
#define GUI_ENT  GUI_T(KC_ENT)
#define GUI_SPC  GUI_T(KC_SPC)
#define LOW_TAB  LT(_LOWER, KC_TAB)
#define RSE_BSP  LT(_RAISE, KC_BSPC)
#define OSM_SFT  OSM(MOD_LSFT)

// For _RAISE layer
#define CTL_ESC  LCTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  MT(MOD_LCTL, KC_TAB),  KC_Q,  KC_W,  KC_E,   KC_R,  KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_DEL  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LALT),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_QUOT ,LCA(KC_NO) ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LGUI),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    OSM(MOD_LSFT), GUI_ENT, LOW_TAB,   RSE_BSP ,KC_SPC  ,OSM(MOD_LSFT)
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT(
  //,----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, LCA(KC_NO) ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                       KC_RCBR, KC_RBRC, KC_COMM,KC_DOT,  KC_SLSH,  _______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_TRNS, LOWER,    KC_TRNS, KC_TRNS, KC_COLON
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT(
  //,--------------------------------------------------------.                    ,------------------------------------------------------.
      _______, KC_DEL , XXXXXXX, KC_UNDS, KC_PLUS, KC_LT,                           XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_PIPE, _______,
  //|--------+--------+--------+--------+--------+-----------|                    |--------+--------+--------+--------+--------+----------|
      _______, KC_HOME, KC_END , KC_MINS, KC_EQL , KC_GT,                            KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,    KC_APP, _______,
  //|--------+--------+--------+--------+--------+-----------|                    |--------+--------+--------+--------+--------+----------|
      _______, PREV_WORD, NEXT_WORD, MCOPY, MPASTE, KC_SCLN,                        PREV_TAB, NEXT_TAB, KC_PGDN, KC_PGUP, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------------|
                                   OSM(MOD_LSFT), KC_TRNS,  XXXXXXX,   RAISE  , KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNC] = LAYOUT(
  //,--------------------------------------------------------------.                    ,--------------------------------------------------------------.
    _______, KC_F1  , KC_F2  , KC_F3   , KC_F4 ,  KC_F5 ,                                KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,QK_BOOT ,
  //|--------+--------+--------+--------+--------+-----------------|                    |--------+--------+--------+--------+--------+-----------------|
    _______, KC_F11 , KC_F12 , XXXXXXX,  JTSEARCH, FORMAT_CODE,                            XXXXXXX , XXXXXXX, XXXXXXX, KC_PAGE_DOWN, KC_PAGE_UP, _______ ,
  //|--------+--------+--------+--------+--------+-----------------|                    |--------+--------+--------+--------+--------+------------------|
    _______, KC_LCAP, XXXXXXX, XXXXXXX, GUI_SPC, KC_MISSION_CONTROL,                     KC_MPLY , KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,XXXXXXX ,
  //|--------+--------+--------+--------+-------+--------+---------|  |--------+--------+--------+--------+--------+--------+---------------------------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, FUNC   , XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LT(_RAISE, KC_BSPC):
            return TAPPING_TERM_THUMB;
      case LT(_LOWER, KC_TAB):
            return TAPPING_TERM_THUMB;
      default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NEXT_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LEFT_GUI) SS_DOWN(X_LEFT_ALT) SS_TAP(X_RIGHT) SS_UP(X_LEFT_GUI) SS_UP(X_LEFT_ALT));
            }
            break;
        case PREV_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LEFT_GUI) SS_DOWN(X_LEFT_ALT) SS_TAP(X_LEFT) SS_UP(X_LEFT_GUI) SS_UP(X_LEFT_ALT));
            }
        break;
        case PREV_WORD:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LEFT_ALT) SS_TAP(X_LEFT) SS_UP(X_LEFT_ALT));
            }
        break;
        case NEXT_WORD:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LEFT_ALT) SS_TAP(X_RIGHT) SS_UP(X_LEFT_ALT));
            }
        break;
        case MCOPY:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LEFT_GUI) SS_TAP(X_C) SS_UP(X_LEFT_GUI));
            }
        break;
        case MPASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LEFT_GUI) SS_TAP(X_V) SS_UP(X_LEFT_GUI));
            }
        break;
        case JTSEARCH:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LEFT_GUI) SS_DOWN(X_LEFT_SHIFT) SS_TAP(X_P) SS_UP(X_LEFT_GUI) SS_UP(X_LEFT_SHIFT));
            }
        break;
        case FORMAT_CODE:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LEFT_GUI) SS_DOWN(X_LEFT_ALT) SS_TAP(X_L) SS_UP(X_LEFT_GUI) SS_UP(X_LEFT_ALT));
        }
        break;
    }
    return true;
};

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0};
    oled_write_P(crkbd_logo, false);
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_anim();
  } else {
    oled_render_logo();
  }
  return false;
}
#endif
