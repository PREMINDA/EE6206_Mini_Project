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

//read all recodes from file
void readAllRecords(){
    printSeperationLine();
    student_marks student;
    FILE *file;
    int errNo;

    //open file with read option
    file = fopen("student_marks.dat", "r");
    if (file == NULL)
    {
        perror("doc1.txt: ");
        printf("Error No %d\n", errno);
        exit(1);
    }

    while (1)
    {
        //read one data from file 
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
    printf("\n");
    fclose(file);
}

//get record count


void updateRecode(){

    student_marks student;
    FILE *file;
    int errNo;
    // get the number of records in the file
    char student_index[20];
    printf("Enter student index number: ");
    scanf("%s", student_index); // get the student index number to update
    student_marks output;
    student_marks updatedRecord;


    //open file with read option
    file = fopen("student_marks.dat", "r+");
    if (file == NULL)
    {
        perror("doc1.txt: ");
        printf("Error No %d\n", errno);
        exit(1);
    }

    while (1)
    {
        //read one data from file 
        fread(&student, sizeof(student_marks), 1, file);
        if (feof(file))
        {
            printf("No recode to found\n");
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
            //find student and update data
            if(strcmp(student.student_index,student_index) == 0){
                fseek(file,-sizeof(student_marks),SEEK_CUR);

                printf("Enter assignment 01 marks : ");
                scanf("%f", &student.assignmt01_marks);
                printf("Enter assignment 02 marks : ");
                scanf("%f", &student.assignmt02_marks);
                printf("Enter project marks : ");
                scanf("%f", &student.project_marks);
                printf("Enter finals marks : ");
                scanf("%f", &student.finalExam_marks);

                // write one student data to file
                int wrtRe = fwrite(&student, sizeof(student_marks), 1, file); 

                // check for error in write to file
                if (wrtRe < 0) 
                {
                    printf("Error No: %d\n", errno);
                    perror("fwrite Error: ");
                    exit(1);
                }
                printf("Update Sucessfully\n");
                break;

            }
        }
    }
    printf("\n");
    fclose(file);
}

//Generate random recodes
void generateRecodes()
{
    student_marks studentData;
    int count = 0;
    while (count < 100)
    {
       char indexNumber[20];
       randomIndex(indexNumber);
       indexNumber[strlen(indexNumber)]='\0';
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

