#ifndef MISC_H
#define MISC_H

#include <stdint.h>
#include <string.h>
#include <wchar.h>

#define LIGHT_GREEN     "\033[1;32m"
#define LIGHT_WHITE     "\033[1;37m"
#define LIGHT_GRAY      "\033[0;37m"
#define DARK_GRAY       "\033[1;30m"
#define LIGHT_RED       "\033[1;31m"

void to_superscript_wchar(
    const wchar_t *input,
    wchar_t       *output
);

#endif
