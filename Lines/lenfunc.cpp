#include <stdio.h>

int length(char* str) {
    int len = 0;
    while (*str != '\0') {
        ++ str;
        len ++;
    }
    return len;
}
