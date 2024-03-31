// Text Graphics using ANSI Escape sequences

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
    printf("\033[31;1;4mHello\033[0m\n");
    printf("\033[31;3;4mHello\033[0m\n");
    printf("\033[31;5mHello\033[0m\n");
    printf("\033[31;6mHello\033[0m\n");
    printf("\033[31;51;4mHello\033[0m\n");

    return 0;
}

void text_emphasis(char* text){
    printf("\033[32;1m%s\033[0m\n", text);
}

void TEXT_GREEN(char* text){
    printf("\033[32;1m%s\033[0m\n", text);
}

void TEXT_YELLOW(char* text){
    printf("\033[33;2m%s\033[0m\n", text);
}

void TEXT_BLUE(char* text){
    printf("\033[34;3m%s\033[0m\n", text);
}

void TEXT_PURPLE(char* text){
    printf("\033[35;5m%s\033[0m\n", text);
}

char* TEXT_FORMAT(const char* text, const char* color){
    char* prefix = "\033[32;1m";
    char* suffix = "\033[0m";

    if(strcmp(color, "green") == 0){
        prefix = "\033[32;1m";
    } else if(strcmp(color, "blue") == 0){
        prefix = "\033[34;1m";
    } else if(strcmp(color, "yellow") == 0){
        prefix = "\033[33;1m";
    } else if(strcmp(color, "purple") == 0){
        prefix = "\033[35;1m";
    } else if(strcmp(color, "red") == 0){
        prefix = "\033[31;1m";
    }

    int totalLength = strlen(prefix) + strlen(text) + strlen(suffix);

    char* finalString = (char*)malloc(totalLength + 1);

    if(finalString) {
        strcpy(finalString, prefix);
        strcat(finalString, text);
        strcat(finalString, suffix);
    }
    else{
        printf("Error: Memory allocation failed.\n");
    }

    return finalString;
}

// int main(){
//     // text_graphic();
//     // text_emphasis("whaddup");
//     // TEXT_GREEN("HOLA HERE");
//     // TEXT_YELLOW("RIGHT THERE");
//     // TEXT_BLUE("HOLA HERE");
//     // TEXT_PURPLE("RIGHT THERE");
//     printf("%s", TEXT_FORMAT("HELLO", "green"));
//     printf("%s", TEXT_FORMAT("HELLO", "red"));
//     printf("%s", TEXT_FORMAT("HELLO", "purple"));
//     printf("%s", TEXT_FORMAT("HELLO", "yellow"));
// }