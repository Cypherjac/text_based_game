#define STATEMENT_LENGTH 200
#define ANSWER_LENGTH 40

#ifndef READ_QUESTIONS_H
#define READ_QUESTIONS_H

#include <stdio.h>

typedef struct {
    char statement[STATEMENT_LENGTH];
    char answer[ANSWER_LENGTH];
    char choices[4][40];
    int points;
    int level;
    int multiple_choice;
} Question;

typedef struct {
    Question questions[50];
} QuestionArray;

extern QuestionArray read_questions(int level, int room);
extern void display_question(const Question* question);
extern Question get_question(QuestionArray* Q, int level);

#endif