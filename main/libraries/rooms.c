#include <stdio.h>
#include <string.h>

// TODO: Update struct values
struct Room
{
    const char *name;
    const char *description;
}

// TODO: Update number of rooms to 5 or more
rooms[] = {
    {"number_puzzles", "a room filled with number puzzles"},
    {"grammar_quizzes", "a room filled with grammar quizzes"},
    {"science_trivia", "a room filled with science questions"},
    {"music_trivia", "a room filled with music questions"},
    {"unpredictable", "a room filled with unpredictable questions. Could be hard or easy, Good luck!"},
};

#define number_of_rooms (sizeof rooms / sizeof *rooms)
 
static unsigned int player_location = 0;

void check_current_room(const char *noun, int location){
    if(noun != NULL && strcmp(noun, "room") == 0){
        printf("You are in %s.\n", rooms[location].description);
    }
    else {
        printf("Command not identified!\n");
    }
}

void switch_rooms(const char *noun){
    unsigned i;
    for(i = 0; i < number_of_rooms; i++){
        if(noun != NULL && strcmp(noun, rooms[i].name) == 0){
            if(i == player_location){
                printf("You are the farthest you can get!\n");
            }
            else {
                printf("OK.\n");
                player_location = i;
                check_current_room("room", i);
            }
            return;
        }
    }
    printf("Room not available.\n");
}

struct Room fetch_room(char room){
    struct Room fetch_room_details;
    fetch_room_details.name =  "Grade is not within range!";
    fetch_room_details.description = "CHECK ENTERED GRADE";
    return fetch_room_details;
}