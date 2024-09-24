#include "misc.h"

void to_superscript_wchar(
    const wchar_t *input,
    wchar_t       *output
) {
    const wchar_t *superscripts = L"⁰¹²³⁴⁵⁶⁷⁸⁹";

    for (int i = 0; input[i] != L'\0'; i++) {
        if (input[i] >= L'0' && input[i] <= L'9') {
            output[i] = superscripts[input[i] - L'0'];
        } else {
            output[i] = input[i];
        }
    }

    output[wcslen(input)] = L'\0';
}