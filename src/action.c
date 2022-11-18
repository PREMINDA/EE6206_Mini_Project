#include "../header/action.h"
#include "../header/student.h"

//Creating a student mark recode
void createStudentRecrod(){
    StudentData data;

    printf("Enter student index number: ");
    scanf("%s", data.studentIndex);
    printf("Enter assignment 01 marks : ");
    scanf("%f", &data.assignmt1Marks);
    printf("Enter assignment 02 marks : ");
    scanf("%f", &data.assignmt2Marks);
    printf("Enter project marks : ");
    scanf("%f", &data.projectMmarks);
    printf("Enter finals marks : ");
    scanf("%f", &data.finalExamMarks);

    writeOneRecord(data);
};