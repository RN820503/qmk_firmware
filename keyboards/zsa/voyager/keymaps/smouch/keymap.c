
#include QMK_KEYBOARD_H
#include "version.h"

enum layer_names {
    _DEF,
    _PM,
    _NUM,
    _SYM,
    _NAV
};

enum custom_keycodes {
    SS_Qu = SAFE_RANGE,
    SS_Th,
    SS_Ch,
    SS_Sh,
    SS_Gh,
    SS_Wh,
    SS_Ph
};

/*  KEY POSITION Names
    LN5 LN4 LN3 LN2 LN1 LN0     RN0 RN1 RN2 RN3 RN4 RN5
    LT5 LT4 LT3 LT2 LT1 LT0     RT0 RT1 RT2 RT3 RT4 RT5
    LM5 LM4 LM3 LM2 LM1 LM0     RM0 RM1 RM2 RM3 RM4 RM5
    LB5 LB4 LB3 LB2 LB1 LB0     RB0 RB1 RB2 RB3 RB4 RB5
                    LH1 LH0     RH0 RH1
*/

/*  Base (alpha) Layer Hands Down Vibranuim-F
            Building for ZSA Voyager
    ⎋   3   2   1    0   4           7   6   5    9   8   Cap
    ⇥   x   w   m⌃   g   j           +=  .:  /    "!  '?  `
    num s   c⌥  n⌘   t⇧  k           ,;  a⇧  e⌘   i⌥  h⌃  ⌦
    tg  f   p   l    d   v      	 -   u   o    y   b   \
                         r   ⌫   ⏎   ␣
*/

// Num row
#define LN5 KC_ESC
#define LN4 KC_3
#define LN3 KC_2
#define LN2 KC_1
#define LN1 KC_0
#define LN0 KC_4

#define RN0 KC_7
#define RN1 KC_6
#define RN2 KC_5
#define RN3 KC_9
#define RN4 KC_8
#define RN5 KC_CAPS

// top row
#define LT5 KC_TAB
#define LT4 KC_X
#define LT3 KC_W
#define LT2 KC_M
#define LT1 KC_G
#define LT0 KC_J

#define RT0 KC_PLUS
#define RT1 KC_DOT
#define RT2 KC_SLSH
#define RT3 KC_DQUO
#define RT4 KC_QUOT
#define RT5 KC_GRV

// middle row
#define LM5 TG(_NUM)
#define LM4 LCTL_T(KC_S)
#define LM3 LALT_T(KC_C)
#define LM2 LGUI_T(KC_N)
#define LM1 LSFT_T(KC_T)
#define LM0 KC_K

#define RM0 KC_COMM
#define RM1 RSFT_T(KC_A)
#define RM2 RGUI_T(KC_E)
#define RM3 RALT_T(KC_I)
#define RM4 RCTL_T(KC_H)
#define RM5 KC_DEL

// bottom row
#define LB5 DF(_PM)
#define LB4 KC_F
#define LB3 KC_P
#define LB2 KC_L
#define LB1 KC_D
#define LB0 KC_V

#define RB0 KC_MINS
#define RB1 KC_U
#define RB2 KC_O
#define RB3 KC_Y
#define RB4 KC_B
#define RB5 KC_BSLS

// thumb row
#define LH1 LT(_NAV, KC_R)
#define LH0 LT(_SYM, KC_BSPC)

#define RH0 LT(_SYM, KC_ENT)
#define RH1 LT(_NUM, KC_SPC)

#define ___x___ KC_NO  // visual aid to null keys

// layer momentaries
// #define OS_SYM OSL(_SYM)

// layer tap
// #define SPC_NUM LT(_NUM, KC_SPC)
// #define R_NAV LT(_NAV, KC_R)
// #define ENT_SYM LT(_SYM, KC_ENT)
// #define MY_PRNS LT(0, KC_1)

// One Shots
// #define OSMSFT OSM(MOD_LSFT)
// #define OSMCMD OSM(MOD_LGUI)
// #define OSMOPT OSM(MOD_LALT)
// #define OSMCTL OSM(MOD_LCTL)

#include "g/keymap_combo.h"

uint8_t  saved_mods = 0;
static uint16_t keyhold_timer; // for handling Qu combo


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*  Base (alpha) Layer Hands Down Vibranuim-F
            Building for ZSA Voyager
    ⎋   3   2@  1$   0#  4           7   6   5   9   8  Cap
    ⇥   x   w   m    g   j           +=  .:  /   "!  '? `
    num s⌃  c⌥  n⌘   t⇧  k           ,;  a⇧  e⌘  i⌥  h⌃ ⌦
    tg  f   p   l    d   v      	 -   u   o   y   b  \
                         r   ⌫   ⏎   ␣
  */
  [_DEF] = LAYOUT_voyager(
    LN5, LN4, LN3, LN2, LN1, LN0,   RN0, RN1, RN2, RN3, RN4, RN5,
    LT5, LT4, LT3, LT2, LT1, LT0,   RT0, RT1, RT2, RT3, RT4, RT5,
    LM5, LM4, LM3, LM2, LM1, LM0,   RM0, RM1, RM2, RM3, RM4, RM5,
    LB5, LB4, LB3, LB2, LB1, LB0,   RB0, RB1, RB2, RB3, RB4, RB5,
    LH1, LH0, RH0, RH1
  ),

  /*  Hands Down Promethium (canonical)
    ⎋   3   2@  1$   0#  4           7   6(  5&  9)  8  Cap
    ⇥   v   w   g    m   j           +=  .:  /   "!  '? `
    num s⌃  n⌥  t⌘   h⇧  k           ,;  a⇧  e⌘  i⌥  c⌃ ⌦
    tg  f   p   d    l   x      	 -   u   o   y   b  \
                         r   ⌫   ⏎   ␣
  */
  [_PM] = LAYOUT_voyager(
    LN5,       LN4,  LN3,  LN2,  LN1,  LN0,    RN0, RN1, RN2, RN3, RN4, RN5,
    LT5,       KC_V, LT3,  KC_G, KC_M, LT0,    RT0, RT1, RT2, RT3, RT4, RT5,
    LM5,       LM4,  KC_N, KC_T, KC_H, LM0,    RM0, RM1, RM2, RM3, KC_C, RM5,
    DF(_DEF),  LB4,  LB3,  KC_D, KC_L, KC_X,   RB0, RB1, RB2, RB3, RB4, RB5,
    LH1, LH0,  RH0,  RH1
  ),


  /*
    ⇥   *   7   8   9   -       	+   .   /
        /   1   2   3   +       	,   ⇧   ⌘   ⌥
        ,   4   5   6   =       	-   ⌫
    	                0   .   ⏎   mo
  *
  [_NUM] = LAYOUT_voyager(
    _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
    _______, KC_ASTR, KC_7,    KC_8,    KC_9,    KC_MINS,                  _______, _______, _______, _______, _______, _______,
    _______, KC_SLSH, KC_1,    KC_2,    KC_3,    KC_PLUS,                  _______, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, ___x___,
    _______, KC_COMM, KC_4,    KC_5,    KC_6,    KC_EQL,                   _______, KC_BSPC, KC_TAB,  KC_ENT,  ___x___, _______,
                                                 KC_0,    KC_DOT, _______, _______
  ),
  */

 /*	BEAKL Numpad
			+	/	*	=
    ⇥   -   5   2   3   :
        7   .   1   0   4       	,   ⇧   ⌘   ⌥	⌃
        ,   6   9   8   ⏎       	-
    	                ␣   ⌫   ⏎   mo
  */
  [_NUM] = LAYOUT_voyager(
    _______, _______, KC_PLUS, KC_SLSH, KC_ASTR, KC_EQL,                    _______, _______, _______, _______, _______, _______,
    _______, KC_MINS, KC_5,    KC_2,    KC_3,    KC_COLN,                   _______, _______, _______, _______, _______, _______,
    _______, KC_7,    KC_DOT,  KC_1,    KC_0,    KC_4,                      _______, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, ___x___,
    _______, KC_COMM, KC_6,    KC_9,    KC_8,    KC_ENT,                    _______, ___x___, ___x___, ___x___, ___x___, _______,
                                                 KC_SPC,  _______, _______, _______
  ),

  /* Pascal Getreuer Mod
    *
    *		<   >	@			       &   [   ]
    *   !   -   +   =   `          \   :   (   )   ?
    *   ^   /   *   #   ~		   |   $   {   }   %
	* 					mo		mo
  *
  [_SYM] = LAYOUT_voyager(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, QK_BOOT,
    _______, ___x___, KC_LABK, KC_RABK, KC_AT,   ___x___,                   ___x___, KC_AMPR, KC_LBRC, KC_RBRC, ___x___, _______,
    _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_GRV,                    KC_BSLS, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES, _______,
    _______, KC_CIRC, KC_SLSH, KC_ASTR, KC_HASH, KC_TILD,                   KC_PIPE, KC_DLR,  KC_LCBR, KC_RCBR, KC_PERC, _______,
                                                 _______, _______, _______, _______
  ),
  */

  /* BEAKL Symbols
    *		@	$	#					~	^	`
    *		<   =	>			       	[   _   ]
    *   \   (   -   )   +          	%   {   ;   }   !
    *       *   :	/   		      	|   ~   &
  */
  [_SYM] = LAYOUT_voyager(
    _______, _______, KC_AT,   KC_DLR,  KC_HASH, _______,                   _______, KC_TILD, KC_CIRC, KC_GRV,  _______, QK_BOOT,
    _______, ___x___, KC_LABK, KC_EQL,  KC_RABK, ___x___,                   ___x___, KC_LBRC, KC_UNDS, KC_RBRC, ___x___, _______,
    _______, KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,                   KC_PERC, KC_LCBR, KC_LPRN, KC_RCBR, KC_EXLM, _______,
    _______, ___x___, KC_ASTR, KC_COLN, KC_SLSH, ___x___,                   ___x___, KC_PIPE, KC_TILD, KC_AMPR, ___x___, _______,
                                                 KC_SPC,  _______, _______, _______
  ),

  /*    F1     F2      F3	   F4	  F5			           F6	   F7	   F8	F9	    F10	    F11
    	       ⌘Q      Scap    Sclp                            vol+    home    up	end             F12
    	⌃      ⌥       ⌘       ⇧             		           vol-    left    dn	rght	del
    	undo   cut     cpy     pst    redo                     mute     ⌫      ⇥     ⏎
                                                               dsk-    dsk+
  */
  [_NAV] = LAYOUT_voyager(
    _______, KC_F1,   KC_F2,   KC_F3,     KC_F4,         KC_F5,                          KC_F6,   KC_F7,      KC_F8,   KC_F9,      KC_F10,  KC_F11,
    _______, ___x___, G(KC_Q), LSG(KC_4), C(S(G(KC_4))), ___x___,                        KC_VOLU, G(KC_LEFT), KC_UP,   G(KC_RGHT), ___x___, KC_F12,
    ___x___, KC_LCTL, KC_LALT, KC_LGUI,   KC_LSFT,       ___x___,                        KC_VOLD, KC_LEFT,    KC_DOWN, KC_RGHT,    KC_DEL,  ___x___,
    ___x___, G(KC_Z), G(KC_X), G(KC_C),   G(KC_V),       LSG(KC_Z),                      KC_MUTE, KC_BSPC,    KC_TAB,  KC_ENT,     ___x___, ___x___,
                                                         _______,   _______, C(KC_LEFT), C(KC_RIGHT)
  )

};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	    case LM1:
        case RM1:
            return TAPPING_TERM - 25;

    	case LB4:
        case LM3:
        case LM2:
        case RM2:
        case RM3:
        case RB4:
            return TAPPING_TERM + 75;

        default:
            return TAPPING_TERM;
    }
};

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LM1:
        case RM1:
            return true;    // Immediately select the hold action when another key is tapped.

        default:
            return false;   // Do not select the hold action when another key is tapped.
    }
};

void add_h_digragh(void) {
    unregister_mods(MOD_MASK_SHIFT);
    tap_code(KC_H); // send "h" honouring CAPSLK state
};

// program custom keycode functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case SS_Qu:  // send "qu" if held
		    saved_mods = get_mods();
            if (record->event.pressed) {
                keyhold_timer = 0;
                register_code(KC_Q);

                if (!(saved_mods & (MOD_MASK_GUI + MOD_MASK_ALT + MOD_MASK_CTRL))) {// Only allow shift or caps
                    keyhold_timer = timer_read(); // time held, or since last pressed alone
                    clear_mods();
                    tap_code(KC_U);
                    set_mods(saved_mods);
                }
                return false; // handled it

            } else {
                unregister_code(KC_Q);
                if (timer_elapsed(keyhold_timer) > TAPPING_TERM) {
                    tap_code(KC_BSPC);
                }
                keyhold_timer = 0;
                return false; // handled it
            }
            return true;  // Didn't handle this
            break;

     // the H digraphs
        case SS_Th:
            if (record->event.pressed) {
                tap_code(KC_T); // send "T" honouring caps
			    add_h_digragh();
            }
            break;
        case SS_Ch:
            if (record->event.pressed) {
                tap_code(KC_C); // send "C" honouring caps
                add_h_digragh();
            }
            break;
        case SS_Sh:
            if (record->event.pressed) {
                tap_code(KC_S); // send "C" honouring caps
                add_h_digragh();
            }
            break;
        case SS_Gh:
            if (record->event.pressed) {
                tap_code(KC_G); // send "G" honouring caps
                add_h_digragh();
            }
            break;
        case SS_Wh:
            if (record->event.pressed) {
                tap_code(KC_W); // send "W" honouring caps
                add_h_digragh();
            }
            break;
        case SS_Ph:
            if (record->event.pressed) {
                tap_code(KC_P); // send "P" honouring caps
                add_h_digragh();
            }
            break;
    }
    return true;
};

// Key overrides
const key_override_t two_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_AT);		/* shift 2 is @ */
const key_override_t one_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_1, KC_DLR);		/* shift 1 is $ */
const key_override_t zero_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_HASH);		/* shift 0 is # */
const key_override_t six_key_override =  ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_LPRN);		/* shift 6 is ( */
const key_override_t five_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_5, KC_AMPR);		/* shift 5 is & */
const key_override_t nine_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_RPRN);		/* shift 9 is ) */
const key_override_t plus_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_PLUS, KC_EQL);	/* shift + is = */
const key_override_t dot_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);	/* shift . is : */
const key_override_t comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);	/* shift , is ; */
const key_override_t slsh_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_ASTR);	/* shift / is * */
const key_override_t dquo_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DQUO, KC_QUES);	/* shift " is ? */
const key_override_t quot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_EXLM);	/* shift ' is ! */
const key_override_t bspc_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);	/* shift ⌫ is ⌦ */

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&two_key_override,
	&one_key_override,
	&zero_key_override,
    &six_key_override,
    &five_key_override,
    &nine_key_override,
    &plus_key_override,
    &dot_key_override,
    &comm_key_override,
    &slsh_key_override,
    &dquo_key_override,
    &quot_key_override,
    &bspc_key_override,
};
