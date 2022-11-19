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

void readAllRecords(){
    StudentData student;
    FILE *file;
    int errNo;

    file = fopen("student_marks.dat", "r"); // open file for writing and reading
    if (file == NULL)
    {
        perror("doc1.txt: ");
        printf("Error No %d\n", errno);
        exit(1);
    }

    while (1) // read each record from file with error handling
    {

        fread(&student, sizeof(StudentData), 1, file);
        if (feof(file))
        {
            break;
        }
        if ((errNo = ferror(file)) > 0)
        {
            perror("fread dox1.txt: ");
            printf("ferror: %d\n", errNo);
            exit(1);
        }
        else
        {
            printf("| %-20s | %-20.2f | %-20.2f | %-20.2f | %-20.2f  | \n", student.studentIndex, student.assignmt1Marks,
                   student.assignmt2Marks, student.projectMmarks, student.finalExamMarks); // print record
            printSeperationLine();
        }
    }
    printf("\n\n");
    fclose(file);
}

void printSeperationLine(){
    printf("_____________________________________________________________________________________________________________________\n");
}