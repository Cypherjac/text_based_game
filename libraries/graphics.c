// Text Graphics using ANSI Escape sequences

#include <stdio.h>
#include <stdbool.h>

struct Options
{
    char *color;
    bool *bold;
    bool *underline;
    bool *italic;
};

// TODO:
// Text graphics initializer
int text_graphic(){
    printf("\033[31;1;4mHello\033[0m");
    printf("\033[31;3;4mHello\033[0m");
    printf("\033[31;5mHello\033[0m");
    printf("\033[31;6mHello\033[0m");
    printf("\033[31;51;4mHello\033[0m");

    return 0;
}

int main(){
    text_graphic();
}