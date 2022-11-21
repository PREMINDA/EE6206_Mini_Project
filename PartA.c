#define _GNU_SOURCE
#include <stdio.h>  // for printf function
#include <stdlib.h> // for exit function
#include <string.h> // for manipulating arrays of characters.
#include <errno.h>  // for error handling
#include <stdbool.h>//boolean values  

typedef struct student_marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

typedef enum recordInfo{COUNT,GET}recordInfo;

void createStudentRecord(void);
void readAllRecords(void);
void printSeperationLine(void);
void generateRecords(void);
void updateRecord(void);
void deleteRecord(void);
void findStudent(void);
int getRecodeInfo(char student_index[20],recordInfo info);
void writeStudentRecord(student_marks student);
float randomMarks(int margin);
void randomIndex(char indexNumber[20]);
void printStudentData(student_marks student,int count);
void printTableHeader();
void red ();
void yellow();
void reset ();
void green ();
void cyan ();
void blue();

int main(int argc, char const *argv[])
{
    int choice = 0;
    char term;

     do{
        printf("\n");
        blue();
        printf("1. Find Record \n");
        printf("2. Create Record \n");
        printf("3. Update Record \n");
        printf("4. Delete Record \n");
        printf("5. Read All Records \n");
        printf("6. Generate Records(100) \n");
        printf("7. Exit \n\n");
        reset();
        printSeperationLine();
        yellow();
        printf("Enter Your Choice : ");
        
        if(scanf("%d%c", &choice, &term) != 2 || term != '\n'){
            printf("Invalid Option");
            break;
        };
        reset();
        switch (choice)
        {
            case 1:
                printSeperationLine();
                findStudent();
                break;
            case 2:
                printSeperationLine();
                createStudentRecord();
                break;
            case 3:
                printSeperationLine();
                updateRecord();
                break;
            case 4:
                printSeperationLine();
                deleteRecord();
                break;
            case 5:
                readAllRecords();
                break;
            case 6:
                printSeperationLine();
                generateRecords();
                break;
            case 7:
                exit(0);
                break;
            default:
                printf("Invalid Option \n");
                break;
        }
     }while(1);
    return 0;
}

//Creating a student mark recode
void createStudentRecord(){
    student_marks data;

    yellow();
    printf("Enter student index : ");
    scanf("%s", data.student_index);

    if(getRecodeInfo(data.student_index,COUNT) == 0){
        printf("Enter assignment 01 marks : ");
        scanf("%f", &data.assignmt01_marks);
        printf("Enter assignment 02 marks : ");
        scanf("%f", &data.assignmt02_marks);
        printf("Enter project marks : ");
        scanf("%f", &data.project_marks);
        printf("Enter finals marks : ");
        scanf("%f", &data.finalExam_marks);
        reset();
        writeStudentRecord(data);
        printf("\n");
        green();
        printf("Recode Successfully created \n");
        reset();
        printSeperationLine();
    }else{
        reset();
        printf("\n");
        red();
        printf("Student already in records\n");
        reset();
        printSeperationLine();
    };

    
};

void findStudent(){
    char student_index[20];
    yellow();
    printf("Enter student index : ");
    scanf("%s", student_index);
    reset();
    getRecodeInfo(student_index,GET);
}

//write student data to file
void writeStudentRecord(student_marks student){
    FILE *file;

    // open file with read and append option
    file = fopen("student_marks.dat", "a+"); 
    if (file == NULL)
    {
        printf("Error opening file: %d\n",errno);
        perror("fopen Error: \n");
        exit(1);
    }

    // write student data to file
    int wrtRe = fwrite(&student, sizeof(student_marks), 1, file); 

    // check for error when write to file
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
    int count = 1;
    cyan();
    printTableHeader();
    reset();
    //open file with read option
    file = fopen("student_marks.dat", "r");
    if (file == NULL)
    {
        perror("doc1.txt: ");
        printf("Error No %d\n", errno);
        exit(1);
    }
    green();
    while (1)
    {
        //read data from file one by by
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
            //print records
            printStudentData(student,count);
            count++;
            printSeperationLine();
        }
    }
    reset();
    printf("\n");
    fclose(file);
}

//update recode
void updateRecord(){

    student_marks student;
    FILE *file;
    int errNo;
    char student_index[20];
    //get the index of the student to update
    yellow();
    printf("Enter student index number: ");
    scanf("%s", student_index);
    reset(); 


    //open file with read write option
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
            printf("\n");
            red();
            printf("No record to update\n");
            reset();
            printSeperationLine();
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
                //move position one step back
                fseek(file,-sizeof(student_marks),SEEK_CUR);

                yellow();
                printf("Enter assignment 01 marks : ");
                scanf("%f", &student.assignmt01_marks);
                printf("Enter assignment 02 marks : ");
                scanf("%f", &student.assignmt02_marks);
                printf("Enter project marks : ");
                scanf("%f", &student.project_marks);
                printf("Enter finals marks : ");
                scanf("%f", &student.finalExam_marks);
                reset();
                // write update student data to file
                int wrtRe = fwrite(&student, sizeof(student_marks), 1, file); 

                // check for error in write to file
                if (wrtRe < 0) 
                {
                    printf("Error No: %d\n", errno);
                    perror("fwrite Error: ");
                    exit(1);
                }
                green();
                printf("\n");
                printf("Update Successfully\n");
                reset();
                printSeperationLine();
                break;

            }
        }
    }
    printf("\n");
    fclose(file);
}

//delete record from file
void deleteRecord(){
    student_marks student;
    FILE *file1,*file2;
    int errNo;
    char student_index[20];
    yellow();
    printf("Enter student index number: ");
    scanf("%s", student_index);
    reset();
    bool isFound = false;
    //open file with read write options
    file1 = fopen("student_marks.dat", "r+");
    //open file with read and appending
    file2 = fopen("cpy.dat","a+");
    if (file1 == NULL){
        perror("student_marks.dat: ");
        printf("Error No %d\n", errno);
        exit(1);
    }
    if (file2 == NULL){
        perror("cpy.dat: ");
        printf("Error No %d\n", errno);
        exit(1);
    }
    while (1){
        //read data from file 
        fread(&student, sizeof(student_marks), 1, file1);
        if (feof(file1)){
            break;
        }
        if ((errNo = ferror(file1)) > 0){
            perror("fread error: ");
            printf("ferror: %d\n", errNo);
            exit(1);
        }
        else{
            //find student and update data
            if(strcmp(student.student_index,student_index) != 0){
                // write student data to file
                int wrtRe = fwrite(&student, sizeof(student_marks), 1, file2); 
                int result;
                // write error handaling
                if (wrtRe < 0){
                    printf("Error No: %d\n", errno);
                    perror("fwrite Error: ");
                    exit(1);
                } 
            }else{
                isFound = true;
            }
        }
    }
    int result;
    printf("\n");
    fclose(file1);
    fclose(file2);
    result = remove("student_marks.dat");
    //file remove error handaling
    if (result != 0) {
        printf("Error No: %d\n", errno);
        perror("file remove Error: ");
        exit(1);
    }
    //file rename error handaling
    result = rename("cpy.dat","student_marks.dat");

    if (result != 0) {
        printf("Error No: %d\n", errno);
        perror("file rename Error: ");
        exit(1);
    }
    if(isFound){
        green();
        printf("Delete Successfully\n");
        reset();
        printSeperationLine();
    }else{
        red();
        printf("No record to Delete\n");
        reset();
        printSeperationLine();
    }
    
}



    

//Generate random records
void generateRecords()
{
    student_marks studentData;
    int count = 0;
    while (count < 100)
    {
       char indexNumber[20];
       randomIndex(indexNumber);
       indexNumber[strlen(indexNumber)]='\0';
        strcpy(studentData.student_index, indexNumber);
        studentData.assignmt01_marks = randomMarks(15);
        studentData.assignmt02_marks = randomMarks(15);
        studentData.project_marks = randomMarks(20);
        studentData.finalExam_marks = randomMarks(50);
        writeStudentRecord(studentData);
        count++;
    }

    blue();
    printf("Generated 100 records\n\n");
    reset();
}

//cheack weather student is available and get search student info
int getRecodeInfo(char student_index[20],recordInfo info){
    FILE* file = fopen("student_marks.dat","r");
    int errNo;
    int count = 1;
    student_marks student;
    int isAlreadyInData = 0;
    if (file == NULL)
    {
        printf("Error opening file: %d\n",errno);
        perror("fopen Error: \n");
        exit(1);
    }

    while (1)
    {
        //read data from file
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
            //find student already in dataset
            if(strcmp(student.student_index,student_index) == 0){
                isAlreadyInData = 1;
                if(info == GET){
                    cyan();
                    printTableHeader();
                    reset();
                    green();
                    printStudentData(student,count);
                    printSeperationLine();
                    reset();
                    printSeperationLine();
                }
            }
            count++;
        }
    }
    fclose(file);
    if(isAlreadyInData == 0 && info == GET){
        printf("\n");
        red();
        printf("No record to found\n");
        reset();
        printSeperationLine();
    };
    return isAlreadyInData;
}

//print table header
void printTableHeader(){
    printSeperationLine();
    printf("| %-6s | %-20s | %-20s | %-20s | %-20s | %-20s  | \n","count" ,"Student Index", "Assignment 01",
                   "Assignment 02", "Project Marks", "Final Marks");
    printSeperationLine();
}

//print student Marks;
void printStudentData(student_marks student,int count){
    printf("| %-6d | %-20s | %-20.2f | %-20.2f | %-20.2f | %-20.2f  | \n",count ,student.student_index, student.assignmt01_marks,
                   student.assignmt02_marks, student.project_marks, student.finalExam_marks);
}

//generate random marks
float randomMarks(int margin){
    float random = ((((float)(rand()%100))+1)/100)*(float)margin;
    return random;
}

//generate random data
void randomIndex(char indexNumber[20]){
    const char* prefix = "EG/2018/";
    int randomID = 1000+(rand()%9000);

    char *num;

    if (asprintf(&num, "%d", randomID) == -1) {
        perror("asprintf");
    } else {
        strcat(strcpy(indexNumber, prefix), num);
        free(num);
    }
}

void red () {
  printf("\033[1;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}

void green () {
  printf("\033[0;32m");
}

void blue () {
  printf("\033[0;34m");
}

void cyan () {
  printf("\033[0;36m");
}


void printSeperationLine(){
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
}
