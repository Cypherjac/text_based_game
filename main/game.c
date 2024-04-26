#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

#include "libraries/rooms.h"
#include "libraries/get_line.h"
#include "libraries/constants.h"
#include "libraries/read_questions.h"
#include "libraries/graphics.h"

#define STATEMENT_LENGTH 200
#define ANSWER_LENGTH 40
#define BUFFER_LENGTH 50

char* ASCII[100] = {
"                                                   ____    _    __  __ _____   ____   ___   ___  __  __ ____  ",       
"                                                  / ___|  / \\  |  \\/  | ____| |  _ \\ / _ \\ / _ \\|  \\/  / ___| ",           
"                                                 | |  _  / _ \\ | |\\/| |  _|   | |_) | | | | | | | |\\/| \\___ \\ ",
"                                                 | |_| |/ ___ \\| |  | | |___  |  _ <| |_| | |_| | |  | |___) |",
"                                                  \\____/_/   \\_\\_|  |_|_____| |_| \\_\\___/ \\___/|_|  |_|____/ ",                                           
"/ |   | \\ | |_   _ _ __ ___ | |__   ___ _ __   ",                        
"| |   |  \\| | | | | '_ ` _ \\| '_ \\ / _ \\ '__|          .           ",
"| |_  | |\\  | |_| | | | | | | |_) |  __/ |    .        ;       *               *          .",   
"|_(_) |_| \\_|\\__,_|_| |_| |_|_.___/ \\_\\__|_|       - --+- -         ",
"       _ __  _   _ _______| | ___  ___                 !                         *                *             *          .      .",
"      | '_ \\| | | |_  /_  / |/ _ \\/ __|                .     .        *   '*        .                     .",
"      | |_) | |_| |/ / / /| |  __/\\__ \\   .      *                           *         *",
" ____ | .__/_\\__,_/___/___|_|\\___||___/               .                            *                   *       '                        .     ,",
"|___ \\|_|  / ___|_ __ __ _ _ __ ___  _ __ ___   __ _ _ __   *              .               *                *                *", 
"  __) |   | |  _| '__/ _` | '_ ` _ \\| '_ ` _ \\ / _` | '__|                        *                 *",
" / __/ _  | |_| | | | (_| | | | | | | | | | | | (_| | |               *                  *                   *                  *",
"|_____(_)  \\____|_|  \\__,_|_| |_| |_|_| |_| |_|\\__,_|_|    *                .                      .                                     *",
"            __ _ _   _(_)___________  ___                                   .                      ;            *          .",   
"           / _` | | | | |_  /_  / _ \\/ __|           *        *             :       ,          - --+- -                                          *",
"          | (_| | |_| | |/ / / /  __/\\__ \\               .                  !           .          !                 ,             .",
"           \\__, |\\__,_|_/___/___\\___||___/        *              *          |        .             .",
" _____    __  |_|          _                    _        .                  |_         +                .              '",
"|___ /   |  \\/  |_   _ ___(_) ___    __ _ _   _(_)___________  ___       ,  | `.                       O",
"  |_ \\   | |\\/| | | | / __| |/ __|  / _` | | | | |_  /_  / _ \\/ __|--- --+-<#>-+- ---  --  -          .        .      *           .          *           *", 
" ___) |  | |  | | |_| \\__ \\ | (__  | (_| | |_| | |/ / / /  __/\\__ \\      `._|_,'                     /",
"|____(_) |_|__|_|\\__,_|___/_|\\___|  \\__, |\\__,_|_/___/___\\___||___/         T                 :     /        .               *             *                *",   
"| || |    / ___|  ___(_) ___ _ __   ___ ___                                 |                   ,  O",
"| || |_   \\___ \\ / __| |/ _ \\ '_ \\ / __/ _ \\              *                 !                     /",
"|__   _|   ___) | (__| |  __/ | | | (_|  __/      *                         :         . :    #/##/#                          *          .",   
"   |_|(_) |____/ \\___|_|\\___|_| |_|\\___\\___|          *                     .       *     ###/##O#  #",
"          | |_ _ __(_)_   _(_) __ _               .                                      ###/##/#  #*#",
"          | __| '__| \\ \\ / / |/ _` |          *                        .                 ##/##/#  #*##                   *                *",                 
"          | |_| |  | |\\ V /| | (_| |                                                     #/##O#  #*##",
"           \\__|_|  |_| \\_/ |_|\\__,_|                     .     *               .           #/# #*#",
" ____  _           _                               *                                  .    /          .                         .",
"| ___|| | | |_ __ | | ___ __   _____      ___ __    ___________________^/\\___^--____/\\____O______________/\\/\\---/\\___________---______________/===\\___",
"|___ \\| | | | '_ \\| |/ / '_ \\ / _ \\ \\ /\\ / / '_ \\                     /\\^   ^  ^    ^                  ^^ ^  '\\ ^          ^       ---",
" ___) | |_| | | | |   <| | | | (_) \\ V  V /| | | |   .                      --           -            --  -      -         ---  __       ^",
"|____(_)___/|_| |_|_|\\_\\_| |_|\\___/ \\_/\\_/ |_| |_|           .        --  __                      ___--  ^  ^                         --  __"                     
};

void graphics_menu(){
    for(int i = 0; i < 39; ++i) {
        printf("%s", ASCII[i]);
        printf("\n");
    }
}

int record_scores(char* contents, int score){
    FILE *recordsFile;

    recordsFile = fopen("database/scores/records.txt", "a");

    if(recordsFile == NULL){
        printf("Unable to find records.txt\n");
        fclose(recordsFile);
        return 1;
    }

    fprintf(recordsFile, "%s: %d\n", contents, score);
    fclose(recordsFile);

    printf("Your score has been recorded successfully!\n");
}

void rules(){
    printf("\n---- RULES OF THE GAME -----\n");
    printf("The quizzes either have multiple choice answers or are open-ended\n");
    printf("Open ended quizzes are answered normally (CASE INSENSITIVE)\n");
    printf("For multiple choice questions, write either A, B, C or D to choose the correct response\n");
    printf("-- Press ENTER to PASS a question --\n");
    printf("Quizzes are weighted differently based on their difficulty\n");
    printf("----- EXPECT ANYTHING! -----\n\n");
    printf("----- GOOD LUCK :) -----\n\n");
}

void rooms_menu(){
    printf("\nChoose a room:\n");
    printf("1. Number Puzzles\n");
    printf("2. Grammar Quizzes\n");
    printf("3. Music Trivia\n");
    printf("4. Science Trivia\n");
    printf("5. Unpredictable\n");
}

int main(){

    int rc, initial_room, room, level, points, streak, fstreak, fstreak_count;
    char name[50];
    bool playing = true, starting = true, started = false, init = false, streak_done = false;
    room = 0;
    level = 1;
    points = 0;
    streak = 0, fstreak = 0, fstreak_count = 0;
    char* input;
    char buffer[BUFFER_LENGTH];

    while(playing){
        if(starting && !started){
            rules();
            printf("What is your name?\n");
            scanf("%s", &name);

            int buffer;
            while((buffer = getchar()) != '\n' && buffer != EOF){}

            graphics_menu();
            rooms_menu();
            starting = false;
            started = true;
        }
        if(started && !init){
            printf("%s [%d] | ", TEXT_FORMAT(name, "green"), points);
            char* user_input = InputRead("CHOOSE A ROOM >> ", BUFFER_LENGTH, true);

            room = atoi(user_input);
            initial_room = room;

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
            QuestionArray BQ = read_questions(level, 6);
            Question question_this;
            if(level <= 5){
                if(streak_done){
                    room = initial_room;
                    question_this = get_question(&Q, level);
                }
                else if(!streak_done && streak == 3){
                    level--;
                    printf("\n%s\n", TEXT_FORMAT("You are on FIRE!!", "yellow"));
                    printf("%s\n", TEXT_FORMAT("A 3 win-streak!", "yellow"));
                    printf("%s\n", TEXT_FORMAT("You have earned yourself a bonus question", "green"));
                    streak_done = true;
                    question_this = get_question(&BQ, level);
                }
                else {
                    Q = read_questions(level, room);
                    question_this = get_question(&Q, level);
                }

                if(fstreak_count <= 2){
                    if(fstreak == 3){
                        int rooms[] = {1, 2, 3, 4, 5};
                        int other_rooms[4];
                        printf("\n%s\n", TEXT_FORMAT("3 fail-streak!!", "red"));
                        printf("%s\n", TEXT_FORMAT("A portal will be opened to another room shortly!", "blue"));
                        
                        int _index = 0;
                        for(int i = 0; i < 5; ++i) {
                            if(rooms[i] != 2) {
                                other_rooms[_index] = rooms[i];
                                ++_index;
                            }
                        }

                        int index;
                        srand(time(NULL));
                        index = rand() % 4;
                        room = other_rooms[index];

                        check_portal_room("room", room);

                        level -= 2;
                        fstreak = 0;
                        fstreak_count++;
                    }
                }

                display_question(&question_this);

                printf("%s [%d] - %d | ", TEXT_FORMAT(name, "green"), points, room);
                char* user_input = InputRead("ANSWER >> ", BUFFER_LENGTH, false);

                if(strcasecmp(user_input, question_this.answer) == 0){
                    printf("\nThe answer '%s' is || CORRECT ||\n", user_input);
                    printf("You have gained +%d points\n", question_this.points);
                    points += (int)question_this.points;
                    streak++;
                    fstreak = 0;
                }
                else {
                    printf("\nThe answer '%s' is || INCORRECT ||\n", user_input);
                    printf("You have gained 0 points\n");
                    streak = 0;
                    fstreak++;
                }
                level++;

            }
            else {
                printf("\n%s\n", TEXT_FORMAT("Your final SCORE:", "green"));
                printf("%d\n", points);
                printf("%s\n", TEXT_FORMAT("GAME OVER!", "red"));
                record_scores(name, points);
                playing = false;
                return 0;
            }
        }
        else {
            
        }
    }

}
