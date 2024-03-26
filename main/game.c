#include <stdio.h>

#include "libraries/rooms.h"
#include "libraries/get_line.h"
#include "libraries/constants.h"

int main(){

    int rc;

    char buff[10];

    check_current_room("room", 2);

    InputRead("Text-prompt test> ", 10);

    return 0;
}