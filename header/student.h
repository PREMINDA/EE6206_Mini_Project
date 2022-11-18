#ifndef STUDENT_H_
#define STUDENT_H_

typedef struct StudentData // structure definition for student marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} StudentData;
#endif