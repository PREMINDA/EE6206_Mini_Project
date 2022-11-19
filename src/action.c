#include "../header/action.h"
#include "../header/random.h"

void writeStudentRecord(student_marks student);

//Creating a student mark recode
void createStudentRecrod(){
    student_marks data;

    printf("Enter student index : ");
    scanf("%s", data.student_index);
    printf("Enter assignment 01 marks : ");
    scanf("%f", &data.assignmt01_marks);
    printf("Enter assignment 02 marks : ");
    scanf("%f", &data.assignmt02_marks);
    printf("Enter project marks : ");
    scanf("%f", &data.project_marks);
    printf("Enter finals marks : ");
    scanf("%f", &data.finalExam_marks);

    writeStudentRecord(data);
};

//write student data to file
void writeStudentRecord(student_marks student){
    FILE *file;

    // open file with append option
    file = fopen("student_marks.dat", "a+"); 
    if (file == NULL)
    {
        printf("Error opening file: %s\n", strerror(errno));
        exit(1);
    }

    // write one student data to file
    int wrtRe = fwrite(&student, sizeof(student_marks), 1, file); 

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
    printSeperationLine();
    student_marks student;
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

        fread(&student, sizeof(student_marks), 1, file);
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
            printf("| %-20s | %-20.2f | %-20.2f | %-20.2f | %-20.2f  | \n", student.student_index, student.assignmt01_marks,
                   student.assignmt02_marks, student.project_marks, student.finalExam_marks); // print record
            printSeperationLine();
        }
    }
    printf("\n\n");
    fclose(file);
}

void generateRecodes()
{
    student_marks studentData;
    int count = 0;
    while (count < 100)
    {
       char indexNumber[20];
       randomIndex(indexNumber);
       indexNumber[strlen(indexNumber)]='\0';
        // generate random data for each record
        strcpy(studentData.student_index, indexNumber);
        studentData.assignmt01_marks = randomMarks();
        studentData.assignmt02_marks = randomMarks();
        studentData.project_marks = randomMarks();
        studentData.finalExam_marks = randomMarks();
        writeStudentRecord(studentData);
        count++;
    }

    printf("Generated 100 records\n\n");
}

void printSeperationLine(){
    printf("_____________________________________________________________________________________________________________________\n");
}

