#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

#include "config.h"

int main(void) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALE_PATH);
    textdomain(PACKAGE);

    puts(_("Choose a number between 1 and 100:"));
    int l = 0;
    int r = 100;

    while(r - l > 1) {
        int m = (l + r) / 2;
        printf(_("Is chosen number more than %d? (%s/%s)\n"), m, _("yes"), _("no"));
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

    printf(_("Your chosen number is %d\n"), r);
    return 0;
}
