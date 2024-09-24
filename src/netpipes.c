#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "demo.h"

int32_t main() {
    setlocale(LC_CTYPE, "");

    int32_t error = demo();
    if(error) {
        fprintf(stderr, "\n+===============+");
        fprintf(stderr, "| MALFUNCTION %d |\n", error);
        fprintf(stderr, "+===============+");
    }
    return error;
}

