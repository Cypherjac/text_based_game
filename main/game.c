#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "libraries/rooms.h"
#include "libraries/get_line.h"
#include "libraries/constants.h"
#include "libraries/read_questions.h"
#include "libraries/graphics.h"

#define STATEMENT_LENGTH 100
#define ANSWER_LENGTH 20
#define BUFFER_LENGTH 50

void rooms_menu(){
    printf("Choose a room:\n");
    printf("1. Number Puzzles\n");
    printf("2. Grammar Quizzes\n");
    printf("3. Music Trivia\n");
    printf("4. Science Trivia\n");
    printf("5. Unpredictable\n");
}

int main(){

    int rc, room, level, points;
    char name[50];
    bool playing = true, starting = true, started = false, init = false;
    room = 0;
    level = 1;
    points = 0;
    char* input;
    char buffer[BUFFER_LENGTH];

    while(playing){
        if(starting && !started){
            printf("What is your name?\n");
            scanf("%s", &name);

            int buffer;
            while((buffer = getchar()) != '\n' && buffer != EOF){}

            rooms_menu();
            starting = false;
            started = true;
        }
        if(started && !init){
            printf("%s [%d] | ", TEXT_FORMAT(name, "green"), points);
            char* user_input = InputRead("CHOOSE A ROOM >> ", BUFFER_LENGTH, true);

            room = atoi(user_input);

            if(room >= 1 && room <= 5){
                check_current_room("room", room);
                init = true;
            }
            else {
                printf("%s [%d] %s",
                    TEXT_FORMAT("The room number", "red"),
                    room,
                    TEXT_FORMAT("you have entered does not exist!\n", "red"));
                printf("%s", TEXT_FORMAT("Choose a number from 1 to 5\n", "purple"));
            }
        }
        if(init && started){
            QuestionArray Q = read_questions(level, room);
            if(level <= 5){
                Question question_this = get_question(&Q, level);
                display_question(&question_this);

                printf("%s [%d] - %d | ", TEXT_FORMAT(name, "green"), points, room);
                char* user_input = InputRead("ANSWER >> ", BUFFER_LENGTH, false);

                if(strcmp(user_input, question_this.answer) == 0){
                    printf("\nThe answer '%s' is || CORRECT ||\n", user_input);
                    printf("You have gained +%d points\n", question_this.points);
                    points += (int)question_this.points;
                }
                else {
                    printf("\nThe answer '%s' is || INCORRECT ||\n", user_input);
                    printf("You have gained 0 points\n");
                }
                level++;
            }
            else {
                printf("Game has ended!");
                playing = false;
                return 0;
            }
        }
        else {
            
        }
    }

}
