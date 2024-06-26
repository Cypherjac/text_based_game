#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NO_INPUT 0
#define TOO_LONG 1
#define OK 2
#define BUFFER_LENGTH 100

struct Input
{
    long int accept;
    char *value;
};

int get_line(char *prompt, char *buff, size_t sz){
    int ch, extra;

    if(prompt != NULL){
        printf ("%s", prompt);
        fflush (stdout);
    }
    if(fgets(buff, sz, stdin) == NULL){
        return NO_INPUT;
    }
    if(buff[strlen(buff)-1] != '\n'){
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    buff[strlen(buff)-1] = '\0';

    return OK;
}

struct Input read_input(char *prompt, int buffer){
    struct Input _read_input_;
    // char buff[buffer];
    char* buff = malloc(buffer * sizeof(char)); // To dynamically allocate memory
    int status;

    status = get_line(prompt, buff, sizeof(buff));
    if(status == NO_INPUT){
        // printf ("\nNo input\n");
        _read_input_.accept = NO_INPUT;
        _read_input_.value = "\nNo input\n";
    }
    else if(status == TOO_LONG){
        // printf ("Input too long [%s]\n", buff);
        _read_input_.accept = TOO_LONG;
        _read_input_.value = "Input too long\n";
    }
    else {
        // printf ("OK [%s]\n", buff);
        _read_input_.accept = OK;
        _read_input_.value = buff;
    }

    return _read_input_;
}

char* InputRead(char *prompt, int buffer, bool numeric_only){
    struct Input data = read_input(prompt, buffer);
    int data_accept = data.accept;
    char* data_value = data.value;

    if (data_accept == OK) {
        if(numeric_only) {
            for(size_t i = 0; data_value[i] != '\0'; i++){
                if (!isdigit(data_value[i])) {
                    return "ERROR: INPUT_NOT_NUMERIC";
                }
            }
        }
        return data_value;
    } else {
        return "ERROR: INPUT_NOT_ACCEPTED";
    }
}
