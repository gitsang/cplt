#include <locale.h>
#include <stdio.h>
#include <time.h>

int t_locale() {
    time_t currtime;
    struct tm* timer;
    char buffer[80] = {0};
    struct lconv* lc;

    time(&currtime);
    timer = localtime(&currtime);


    printf("Locale is: %s\n", setlocale(LC_ALL, "en_US"));
    strftime(buffer,80, "%c", timer);
    printf("Date is: %s\n", buffer);
    lc = localeconv();
    printf ("Currency symbol is: %s\n", lc->currency_symbol);
    printf ("International Currency symbol is: %s\n", lc->int_curr_symbol);


    printf("Locale is: %s\n", setlocale(LC_ALL, "de_DE"));
    strftime(buffer,80, "%c", timer);
    printf("Date is: %s\n", buffer);
    lc = localeconv();
    printf ("Currency symbol is: %s\n", lc->currency_symbol);
    printf ("International Currency symbol is: %s\n", lc->int_curr_symbol);

    return(0);
}

int main() {
    t_locale();

    return 0;
}
