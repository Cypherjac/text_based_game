#define STATEMENT_LENGTH 100
#define ANSWER_LENGTH 20

#ifndef READ_QUESTIONS_H
#define READ_QUESTIONS_H

#include <stdio.h>

typedef struct {
    char statement[STATEMENT_LENGTH];
    char answer[ANSWER_LENGTH];
    char choices[4][20];
    int points;
    int level;
} Question;

typedef struct {
    Question questions[30];
} QuestionArray;

extern QuestionArray read_questions(int level, int room);
extern void display_question(const Question* question);
extern Question get_question(QuestionArray* Q, int level);

#endif