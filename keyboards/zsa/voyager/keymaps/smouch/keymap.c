
#include QMK_KEYBOARD_H

enum layer_names {
    DEF,
    NUM,
    SYM,
    NAV,
    GAM,
};

enum custom_keycodes {
    SS_Qu = SAFE_RANGE,
};

/*  KEY POSITION Names
    LN5 LN4 LN3 LN2 LN1 LN0     RN0 RN1 RN2 RN3 RN4 RN5
    LT5 LT4 LT3 LT2 LT1 LT0     RT0 RT1 RT2 RT3 RT4 RT5
    LM5 LM4 LM3 LM2 LM1 LM0     RM0 RM1 RM2 RM3 RM4 RM5
    LB5 LB4 LB3 LB2 LB1 LB0     RB0 RB1 RB2 RB3 RB4 RB5
                    LH1 LH0     RH0 RH1
*/

/*  Hands Down Promethium
    ⎋   3   2@  1$   0#  4           7   6   5   9   8  vol↑
    ⇥   v   w   g2   m   j           =_  .:  '2  -+  /  vol↓
    z   s⌃  n⌥  t3   h⌘  k           ,;  a⌘  e1  i⌥  c⌃ q
    tg  f   p   d    l   x      	 `   u   o   y   b  tg
                         r⇧  ⌫   ⏎   ␣⇧
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
#define RN5 KC_VOLU

// top row
#define LT5 KC_TAB
#define LT4 KC_V
#define LT3 KC_W
#define LT2 LT(SYM, KC_G)
#define LT1 KC_M
#define LT0 KC_J

#define RT0 KC_EQL
#define RT1 KC_DOT
#define RT2 LT(SYM, KC_QUOT)
#define RT3 KC_MINS
#define RT4 KC_SLSH
#define RT5 KC_VOLD

// middle row
#define LM5 KC_Z
#define LM4 LCTL_T(KC_S)
#define LM3 LALT_T(KC_N)
#define LM2 LT(NAV, KC_T)
#define LM1 LGUI_T(KC_H)
#define LM0 KC_K

#define RM0 KC_COMM
#define RM1 RGUI_T(KC_A)
#define RM2 LT(NUM, KC_E)
#define RM3 RALT_T(KC_I)
#define RM4 RCTL_T(KC_C)
#define RM5 KC_Q

// bottom row
#define LB5 KC_NO
#define LB4 KC_F
#define LB3 KC_P
#define LB2 KC_D
#define LB1 KC_L
#define LB0 KC_X

#define RB0 KC_GRV
#define RB1 KC_U
#define RB2 KC_O
#define RB3 KC_Y
#define RB4 KC_B
#define RB5 TG(GAM)

// thumb row
#define LH1 LSFT_T(KC_R)
#define LH0 KC_BSPC

#define RH0 KC_ENT
#define RH1 RSFT_T(KC_SPC)

#define ___x___ KC_NO  // visual aid to null keys



// #include "g/keymap_combo.h"

uint8_t  saved_mods = 0;
static uint16_t keyhold_timer; // for handling Qu combo


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*  Hands Down Promethium
    ⎋   3   2@  1$   0#  4           7   6   5   9   8  vol↑
    ⇥   v   w   g2   m   j           =_  .:  '2  -+  /  vol↓
    z   s⌃  n⌥  t3   h⌘  k           ,;  a⌘  e1  i⌥  c⌃ q
    tg  f   p   d    l   x      	 `   u   o   y   b  tg
                         r⇧  ⌫   ⏎   ␣⇧
*/
  [DEF] = LAYOUT_voyager(
    LN5, LN4, LN3, LN2, LN1, LN0,           RN0, RN1, RN2, RN3, RN4, RN5,
    LT5, LT4, LT3, LT2, LT1, LT0,           RT0, RT1, RT2, RT3, RT4, RT5,
    LM5, LM4, LM3, LM2, LM1, LM0,           RM0, RM1, RM2, RM3, RM4, RM5,
    LB5, LB4, LB3, LB2, LB1, LB0,           RB0, RB1, RB2, RB3, RB4, RB5,
                             LH1, LH0, RH0, RH1
  ),

 /*	BEAKL-19 Numpad
		⇥	+	=	*
    ⇥   -   5   2   3   :
        7   .   1   0   4       	,   ⌘  (mo)  ⌥	 ⌃
        /   6   9   8   ,
    	                ␣   ⌫   ⏎   lk
  */
  [NUM] = LAYOUT_voyager(
    _______, KC_TAB,  KC_PLUS, KC_EQL, KC_ASTR,  ___x___,                   _______, _______, _______, _______, _______, _______,
    _______, KC_MINS, KC_5,    KC_2,    KC_3,    KC_COLN,                   _______, _______, _______, _______, _______, _______,
    QK_LLCK, KC_7,    KC_DOT,  KC_1,    KC_0,    KC_4,                      _______, KC_RGUI, _______, KC_RALT, KC_RCTL, _______,
    _______, KC_SLSH, KC_6,    KC_9,    KC_8,    KC_COMM,                   _______, ___x___, ___x___, ___x___, ___x___, _______,
                                                 KC_SPC,  _______, _______, _______
  ),

  /* BEAKL-27 Symbols
    *       @   $   #                       ^
    *       <   =   >                   [   _   ]
    *   \   (   -   )   +          	%   {   ;   }   !
    *       *   :	/       		 	&   ~   |
  */
  [SYM] = LAYOUT_voyager(
    _______, _______, KC_AT,   KC_DLR,  KC_HASH, _______,                   _______, _______, KC_CIRC, _______, _______, _______,
    _______, ___x___, KC_LABK, KC_EQL,  KC_RABK, ___x___,                   ___x___, KC_LBRC, KC_UNDS, KC_RBRC, ___x___, _______,
    _______, KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,                   KC_PERC, KC_LCBR, KC_SCLN, KC_RCBR, KC_EXLM, _______,
    _______, ___x___, KC_ASTR, KC_COLN, KC_SLSH, ___x___,                   ___x___, KC_AMPR, KC_TILD, KC_PIPE, ___x___, _______,
                                                 KC_SPC,  _______, _______, _______
  ),


  /* Getreuer Symbols
    *
    *	`	<   >	-	|		    ^  	{   }   $   \
    *   !   *   /   =   &          	#   (   )   ;   "
    *   ~   +   [	]   %		    @ 	:   ,   .	'
  *
  [SYM] = LAYOUT_voyager(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, KC_GRV , KC_LABK, KC_RABK, KC_MINS, KC_PIPE,                   KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR , KC_BSLS, _______,
    QK_LLCK, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL,  KC_AMPR,                   KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_DQUO, QK_LLCK,
    _______, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC,                   KC_AT  , KC_COLN, KC_COMM, KC_DOT , KC_QUOT, _______,
                                                 KC_SPC , _______, _______, _______
  ),
  */

  /*
    	                        Sclp                       Pgup    home    up	end
    	⌃      ⌥       (mo)     ⌘            		       Pgdn    left    dn	rght	del
    	                        Scap                       undo    ←wrd    wrd→ ←line→
                                        ⇧
  */
  [NAV] = LAYOUT_voyager(
    _______, _______, _______, _______, _______,       _______,                   _______, _______,    _______, _______,    _______, _______,
    _______, ___x___, ___x___, _______, C(S(G(KC_4))), ___x___,                   KC_PGUP, G(KC_LEFT), KC_UP,   G(KC_RGHT), ___x___, _______,
    ___x___, KC_LCTL, KC_LALT, _______, KC_LGUI,       ___x___,                   KC_PGDN, KC_LEFT,    KC_DOWN, KC_RGHT,    KC_DEL,  QK_LLCK,
    ___x___, ___x___, ___x___, ___x___, LSG(KC_4),     ___x___,                   G(KC_Z), ___x___,    ___x___, ___x___,    ___x___,  _______,
                                                       KC_LSFT, _______, C(KC_LEFT), C(KC_RGHT)
  ),

  /*	Game
	⎋	3	2	1	3   4
    ⇥   ⇥   q   w   e   r
    z   ⇧   s   a   d   f       	,   ⌘  (mo)  ⌥	 ⌃
    v   ⌃   F2  F1  F3  F4                           tg
    	                ␣   c   ⏎   ␣⇧
  */
  [GAM] = LAYOUT_voyager(
    _______, _______, KC_2,  KC_1,  KC_3,  KC_4,                         _______, _______, _______, _______, _______, _______,
    _______, KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,                         _______, _______, _______, _______, _______, _______,
    KC_Z,    KC_LSFT, KC_A,  KC_S,  KC_D,  KC_F,                         _______, KC_RGUI, _______, KC_RALT, KC_RCTL, _______,
    KC_V,    KC_LCTL, KC_F2, KC_F1, KC_F3, KC_F4,                        _______, ___x___, ___x___, ___x___, ___x___, _______,
                                               KC_SPC, KC_C, C(KC_LEFT), C(KC_RGHT)
  ),

};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	    case LH1:
        case RH1:
            return TAPPING_TERM - 25;

    	case LM4:
        case LM3:
        case LM2:
        case LM1:
        case RM1:
        case RM2:
        case RM3:
        case RM4:
            return TAPPING_TERM + 75;

        default:
            return TAPPING_TERM;
    }
};

// Handedness for Chordal Hold
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        '*', '*', '*', '*', '*', '*',            '*', '*', '*', '*', '*', '*',
        '*', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', '*',
        'L', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', 'R',
        '*', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', '*',
                                 '*', '*',  '*', '*'
    );

// program custom keycode functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case SS_Qu:  // send "qu" on tap, bspc "u" if held
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

        /* case SELWBAK:  // Backward word selection.
            if (record->event.pressed) {
                select_word_register('B');
            } else {
                select_word_unregister();
            }
            break;

        case SELWORD:  // Forward word selection.
            if (record->event.pressed) {
                select_word_register('W');
            } else {
                select_word_unregister();
            }
            break;

        case SELLINE:  // Line selection.
            if(record->event.pressed) {
                select_word_register('L');
            } else {
                select_word_unregister();
            }
            break; */
    }
    return true;
};

// define combo names
enum combos
{
    H_V,
    H_Z,
    H_Qu,
    Hat,
    Hexlm,
    Hques,
    Hcoln,
    Hscln,
    Hndsh,
    Hmdsh,
    Hunds,
    Heql,
    Htild,
    Hesc,
    Htab,
    Hlsft,
    Hrsft,
    Hbspw,
    Hquit,
    Hundo,
    Hcopy,
    Hcut,
    Hpste,
    Hsall,
    Hpstm,
    Hlprn,
    Hrprn,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

// define keys that make up combos
const uint16_t PROGMEM V_combo[] = {LT3, LT2, COMBO_END}; // "v"
const uint16_t PROGMEM Z_combo[] = {LT3, LT1, COMBO_END}; // "z"
const uint16_t PROGMEM Qu_combo[] = {LT2, LT1, COMBO_END}; // "qu"
const uint16_t PROGMEM at_combo[] = {RT0, RT1, COMBO_END}; // "@"
const uint16_t PROGMEM exlm_combo[] = {RT1, RT2, COMBO_END}; // "!"
const uint16_t PROGMEM ques_combo[] = {RT2, RT3, COMBO_END}; // "?"
const uint16_t PROGMEM coln_combo[] = {RT1, RT3, COMBO_END}; // ":"
const uint16_t PROGMEM scln_combo[] = {RM0, RM1, COMBO_END}; // ";"
const uint16_t PROGMEM ndsh_combo[] = {RB0, RB1, COMBO_END}; // "–"
const uint16_t PROGMEM mdsh_combo[] = {RB0, RB2, COMBO_END}; // "—"
const uint16_t PROGMEM unds_combo[] = {RB1, RB3, COMBO_END}; // "–"
const uint16_t PROGMEM eql_combo[] = {RB2, RB3, COMBO_END}; // "="
const uint16_t PROGMEM tild_combo[] = {RB1, RB4, COMBO_END}; // "~"
const uint16_t PROGMEM esc_combo[] = {LM4, LM1, COMBO_END}; // "⎋"
const uint16_t PROGMEM tab_combo[] = {LM3, LM1, COMBO_END}; // "⇥"
const uint16_t PROGMEM lsft_combo[] = {LM3, LM2, COMBO_END}; // "os⇧"
const uint16_t PROGMEM rsft_combo[] = {RM2, RM3, COMBO_END}; // "os⇧"
const uint16_t PROGMEM bspw_combo[] = {RM1, RM3, COMBO_END}; // "⌫"
const uint16_t PROGMEM quit_combo[] = {LT0, LM0, COMBO_END}; // "⌘Q"
const uint16_t PROGMEM undo_combo[] = {LB4, LB3, COMBO_END}; // "⌘Z"
const uint16_t PROGMEM copy_combo[] = {LB3, LB2, COMBO_END}; // "⌘C"
const uint16_t PROGMEM pste_combo[] = {LB2, LB1, COMBO_END}; // "⌘V"
const uint16_t PROGMEM cut_combo[] = {LB3, LB1, COMBO_END}; // "⌘X"
const uint16_t PROGMEM sall_combo[] = {LB4, LB1, COMBO_END}; // "⌘A"
const uint16_t PROGMEM pstm_combo[] = {LB4, LB0, COMBO_END}; // "Paste & Match Style"
const uint16_t PROGMEM lprn_combo[] = {LM2, LM1, COMBO_END}; // "("
const uint16_t PROGMEM rprn_combo[] = {RM1, RM2, COMBO_END}; // ")"

// map combo names to their keys and the key they trigger
combo_t key_combos[] =
{
    [H_V] = COMBO(V_combo, KC_V),
    [H_Z] = COMBO(Z_combo, KC_Z),
    [H_Qu] = COMBO(Qu_combo, SS_Qu),
    [Hat] = COMBO(at_combo, KC_AT),
    [Hexlm] = COMBO(exlm_combo, KC_EXLM),
    [Hques] = COMBO(ques_combo, KC_QUES),
    [Hcoln] = COMBO(coln_combo, KC_COLN),
    [Hscln] = COMBO(scln_combo, KC_SCLN),
    [Hndsh] = COMBO(ndsh_combo, A(KC_MINS)),
    [Hmdsh] = COMBO(mdsh_combo, A(S(KC_MINS))),
    [Hunds] = COMBO(unds_combo, KC_UNDS),
    [Heql] = COMBO(eql_combo, KC_EQL),
    [Htild] = COMBO(tild_combo, KC_TILD),
    [Hesc] = COMBO(esc_combo, KC_ESC),
    [Htab] = COMBO(tab_combo, KC_TAB),
    [Hlsft] = COMBO(lsft_combo, OSM(MOD_LSFT)),
    [Hrsft] = COMBO(rsft_combo, OSM(MOD_RSFT)),
    [Hbspw] = COMBO(bspw_combo, A(KC_BSPC)),
    [Hquit] = COMBO(quit_combo, G(KC_Q)),
    [Hundo] = COMBO(undo_combo, G(KC_Z)),
    [Hcopy] = COMBO(copy_combo, G(KC_C)),
    [Hpste] = COMBO(pste_combo, G(KC_V)),
    [Hcut] = COMBO(cut_combo, G(KC_X)),
    [Hsall] = COMBO(sall_combo, G(KC_A)),
    [Hpstm] = COMBO(pstm_combo, A(S(G(KC_V)))),
    [Hlprn] = COMBO(lprn_combo, KC_LPRN),
    [Hrprn] = COMBO(rprn_combo, KC_RPRN),
};

// Key overrides
const key_override_t two_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_AT);		/* shift 2 is @ */
const key_override_t one_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_1, KC_DLR);		/* shift 1 is $ */
const key_override_t zero_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_HASH);		/* shift 0 is # */
const key_override_t eql_key_override =  ko_make_basic(MOD_MASK_SHIFT, KC_EQL, KC_UNDS);	/* shift = is _ */
const key_override_t dot_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);	/* shift . is : */
const key_override_t comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);	/* shift , is ; */
const key_override_t mins_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, KC_PLUS);	/* shift - is + */
const key_override_t bspc_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);	/* shift ⌫ is ⌦ */

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&two_key_override,
	&one_key_override,
	&zero_key_override,
    &eql_key_override,
    &dot_key_override,
    &comm_key_override,
    &mins_key_override,
    &bspc_key_override,
};

/* const custom_shift_key_t custom_shift_keys[] = {
    {KC_EQL, KC_UNDS},  // Shift = is _
    {KC_DOT, KC_COLN},  // Shift . is :
    {KC_MINS, KC_PLUS}, // Shift - is +
    {KC_COMM, KC_SCLN}, // Shift , is ;
    {KC_BSPC, KC_DEL},  // Shift ⌫ is ⌦
};
 */
