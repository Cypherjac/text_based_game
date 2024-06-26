#include <stdlib.h>
#include <time.h>
#include "read_questions.h"

QuestionArray read_questions(int level, int room){
    QuestionArray Q;
    FILE* questions;

    switch(room){
        case 1:
            questions = fopen("database/questions/number_puzzles.txt", "r");
            break;
        case 2:
            questions = fopen("database/questions/grammar_quizzes.txt", "r");
            break;
        case 3:
            questions = fopen("database/questions/music_trivia.txt", "r");
            break;
        case 4:
            questions = fopen("database/questions/science_trivia.txt", "r");
            break;
        case 5:
            questions = fopen("database/questions/unpredictable.txt", "r");
            break;
        case 6:
            questions = fopen("database/questions/bonus.txt", "r");
            break;
        default:
            questions = fopen("database/questions/bonus.txt", "r");
            break;
    }

    if(questions == NULL){
        perror("Error opening file");
        printf("FILE_OPEN_ERROR");
        return Q;
    }

    // "%99[^;]; %5[^;]; %5[^;]; %5[^;]; %5[^;]; %5[^;]; %d %d %d",

    for(int i = 0; i < 50; i++){
        if(
            fscanf(questions,
                "%200[^;]; %40[^;]; %40[^;]; %40[^;]; %40[^;]; %40[^;]; %d %d %d",
                Q.questions[i].statement,
                Q.questions[i].choices[0],
                Q.questions[i].choices[1],
                Q.questions[i].choices[2],
                Q.questions[i].choices[3],
                Q.questions[i].answer,
                &Q.questions[i].points,
                &Q.questions[i].level,
                &Q.questions[i].multiple_choice
            ) != 9
        ){
            // printf("\nIncorrect formatting for question %d\n", i);
            
            // printf("Question statement: %s\n", Q.questions[i].statement);
            // printf("Choices[0]: %s\n", Q.questions[i].choices[0]);
            // printf("CHoices[1]: %s\n", Q.questions[i].choices[1]);
            // printf("Choices[2]: %s\n", Q.questions[i].choices[2]);
            // printf("Choices[3]: %s\n", Q.questions[i].choices[3]);
            // printf("Answer: %s\n", Q.questions[i].answer);
            // printf("Level: %d\n", Q.questions[i].level);
            // printf("Points: %d\n", Q.questions[i].points);
            // printf("Multiple Choice: %d\n", Q.questions[i].multiple_choice);

            break;
        }
    }

    fclose(questions);
    return Q;
}

void display_question(const Question* question){
    printf("%s | Points->[%d] Level->[%d]\n", question->statement, question->points, question->level);
    if(question->multiple_choice){
        printf("A. %s\n", question->choices[0]);
        printf("B. %s\n", question->choices[1]);
        printf("C. %s\n", question->choices[2]);
        printf("D. %s\n", question->choices[3]);
    }
}

Question get_question(QuestionArray* Q, int level){
    Question question;
    int count = 0;
    for(int i = 0; i < 50; i++){
        if (Q->questions[i].level == level){
            count++;
        }
    }

    if (count == 0){
        printf("No questions of level %d found.\n", level);
        return question;
    }

    int index;
    srand(time(NULL));
    index = rand() % count;
    for(int i = 0; i < 50; i++){
        if(Q->questions[i].level == level){
            if(index == 0){
                question = Q->questions[i];
                return question;
            }
            index--;
        }
    }

    return question;
}
