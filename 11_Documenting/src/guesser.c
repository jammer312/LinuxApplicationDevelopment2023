/** @mainpage Guesser 
 * @copydetails guesser
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#include <argp.h>

#include "config.h"


/** @file guesser.c
 * Implementation
 */

#define _(STRING) STRING

/// @private
const char *argp_program_version = PACKAGE_STRING;
static char doc[] = _("a simple program that guesses a number between 1 and 100");
/// @private
const char *argp_program_bug_address = PACKAGE_BUGREPORT;
static char args_doc[] = "";
static struct argp_option options[] = {
    {"roman", 'r', 0, 0, _("Use roman numbers instead of decimal")},
    {0},
};

#define _(STRING) gettext(STRING)

/// @private
struct arguments{
    int roman;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch(key) {
    case 'r':
        arguments->roman = 1;
        break;
    case ARGP_KEY_ARG:
        argp_usage(state);
        break;
    case ARGP_KEY_END:
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

/** A conversion table from integer to string representation in roman numerals.
 */
char* romanLiterals[] = {
    "",
    "I",
    "II",
    "III",
    "IV",
    "V",
    "VI",
    "VII",
    "VIII",
    "IX",
    "X",
    "XI",
    "XII",
    "XIII",
    "XIV",
    "XV",
    "XVI",
    "XVII",
    "XVIII",
    "XIX",
    "XX",
    "XXI",
    "XXII",
    "XXIII",
    "XXIV",
    "XXV",
    "XXVI",
    "XXVII",
    "XXVIII",
    "XXIX",
    "XXX",
    "XXXI",
    "XXXII",
    "XXXIII",
    "XXXIV",
    "XXXV",
    "XXXVI",
    "XXXVII",
    "XXXVIII",
    "XXXIX",
    "XL",
    "XLI",
    "XLII",
    "XLIII",
    "XLIV",
    "XLV",
    "XLVI",
    "XLVII",
    "XLVIII",
    "XLIX",
    "L",
    "LI",
    "LII",
    "LIII",
    "LIV",
    "LV",
    "LVI",
    "LVII",
    "LVIII",
    "LIX",
    "LX",
    "LXI",
    "LXII",
    "LXIII",
    "LXIV",
    "LXV",
    "LXVI",
    "LXVII",
    "LXVIII",
    "LXIX",
    "LXX",
    "LXXI",
    "LXXII",
    "LXXIII",
    "LXXIV",
    "LXXV",
    "LXXVI",
    "LXXVII",
    "LXXVIII",
    "LXXIX",
    "LXXX",
    "LXXXI",
    "LXXXII",
    "LXXXIII",
    "LXXXIV",
    "LXXXV",
    "LXXXVI",
    "LXXXVII",
    "LXXXVIII",
    "LXXXIX",
    "XC",
    "XCI",
    "XCII",
    "XCIII",
    "XCIV",
    "XCV",
    "XCVI",
    "XCVII",
    "XCVIII",
    "XCIX",
    "C",
};

/** A conversion table from integer to string representation in decimal form.
 */
char* decimalLiterals[] = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
    "17",
    "18",
    "19",
    "20",
    "21",
    "22",
    "23",
    "24",
    "25",
    "26",
    "27",
    "28",
    "29",
    "30",
    "31",
    "32",
    "33",
    "34",
    "35",
    "36",
    "37",
    "38",
    "39",
    "40",
    "41",
    "42",
    "43",
    "44",
    "45",
    "46",
    "47",
    "48",
    "49",
    "50",
    "51",
    "52",
    "53",
    "54",
    "55",
    "56",
    "57",
    "58",
    "59",
    "60",
    "61",
    "62",
    "63",
    "64",
    "65",
    "66",
    "67",
    "68",
    "69",
    "70",
    "71",
    "72",
    "73",
    "74",
    "75",
    "76",
    "77",
    "78",
    "79",
    "80",
    "81",
    "82",
    "83",
    "84",
    "85",
    "86",
    "87",
    "88",
    "89",
    "90",
    "91",
    "92",
    "93",
    "94",
    "95",
    "96",
    "97",
    "98",
    "99",
    "100",
};

/** Convert an integer into string represented in decimal form
 * 
 * @param n an integer from 1 to 100
 * @return string representation of n in decimal form
 */
char* toDecimal(int n) {
    return decimalLiterals[n];
}

/** Convert an integer into its string representation in roman numerals
 * 
 * @param n an integer from 1 to 100
 * @return string representation of n in roman numerals
 */
char* toRoman(int n) {
    return romanLiterals[n];
}

/** Convert a string representation of a number in roman numerals to an integer
 * 
 * @param literal string representation of a number in roman literals
 * @return an integer from 1 to 100 if conversion is successfull or -1 if it is not
 */
int fromRoman(char* literal) {
    for (int i = 1; i <= 100; i++) {
        if (strcasecmp(romanLiterals[i], literal) == 0) {
            return i;
        }
    }
    return -1;
}

/** 
 * @page guesser
 * Guesser
 * 
 * @section SYNOPSIS
 * Usage: guesser [OPTION...] 
 *
 * @section DESCRIPTION
 * a simple program that guesses a number between 1 and 100\n 
 * \n 
 * -r, --roman                Use roman numbers instead of decimal\n 
 * -?, --help                 Give this help list\n 
 *     --usage                Give a short usage message\n 
 * -V, --version              Print program version\n 
 *
 */

int main(int argc, char *args[]) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALE_PATH);
    textdomain(PACKAGE);

    struct arguments arguments;
    arguments.roman = 0;
    argp_parse(&argp, argc, args, 0, 0, &arguments);

    char* (*numToStrFunc)(int) = &toDecimal;
    if (arguments.roman) {
        numToStrFunc = &toRoman;
    }

    printf(_("Choose a number between %s and %s:\n"), (*numToStrFunc)(1), (*numToStrFunc)(100));
    int l = 0;
    int r = 100;

    while(r - l > 1) {
        int m = (l + r) / 2;
        printf(_("Is chosen number more than %s? (%s/%s)\n"), (*numToStrFunc)(m), _("yes"), _("no"));
        char answer[4];
        scanf("%3s", answer);
        if(strcmp(answer, _("yes")) == 0) {
            l = m;
        } else if (strcmp(answer, _("no")) == 0) {
            r = m;
        } else {
            puts(_("Unrecognized answer."));
        }
    }

    printf(_("Your chosen number is %s\n"), (*numToStrFunc)(r));
    return 0;
}
