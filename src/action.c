#include "../header/action.h"

void writeStudentRecord(StudentData student);

//Creating a student mark recode
void createStudentRecrod(){
    StudentData data;

    printf("Enter student index : ");
    scanf("%s", data.studentIndex);
    printf("Enter assignment 01 marks : ");
    scanf("%f", &data.assignmt1Marks);
    printf("Enter assignment 02 marks : ");
    scanf("%f", &data.assignmt2Marks);
    printf("Enter project marks : ");
    scanf("%f", &data.projectMmarks);
    printf("Enter finals marks : ");
    scanf("%f", &data.finalExamMarks);

    writeStudentRecord(data);
};

//write student data to file
void writeStudentRecord(StudentData student){
    FILE *file;

    // open file with append option
    file = fopen("student_marks.dat", "a+"); 
    if (file == NULL)
    {
        printf("Error opening file: %s\n", strerror(errno));
        exit(1);
    }

    // write one student data to file
    int wrtRe = fwrite(&student, sizeof(StudentData), 1, file); 

    // check for error in write to file
    if (wrtRe < 0) 
    {
        printf("Error No: %d\n", errno);
        perror("fwrite Error: ");
        exit(1);
    }

    // close file
    fclose(file); 
}