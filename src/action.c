#include "../header/action.h"
#include "../header/random.h"

void writeStudentRecord(student_marks student);

//Creating a student mark recode
void createStudentRecord(){
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

    printSeperationLine();
    //print table headers
    printf("| %-6s | %-20s | %-20s | %-20s | %-20s | %-20s  | \n","count" ,"Student Index", "Assignment 01",
                   "Assignment 02", "Project Marks", "Final Marks");
    printSeperationLine();

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
            printf("| %-6d | %-20s | %-20.2f | %-20.2f | %-20.2f | %-20.2f  | \n",count ,student.student_index, student.assignmt01_marks,
                   student.assignmt02_marks, student.project_marks, student.finalExam_marks);
            count++;
            printSeperationLine();
        }
    }
    
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
    printf("Enter student index number: ");
    scanf("%s", student_index); 


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
            printf("No record to update\n");
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

                printf("Enter assignment 01 marks : ");
                scanf("%f", &student.assignmt01_marks);
                printf("Enter assignment 02 marks : ");
                scanf("%f", &student.assignmt02_marks);
                printf("Enter project marks : ");
                scanf("%f", &student.project_marks);
                printf("Enter finals marks : ");
                scanf("%f", &student.finalExam_marks);

                // write update student data to file
                int wrtRe = fwrite(&student, sizeof(student_marks), 1, file); 

                // check for error in write to file
                if (wrtRe < 0) 
                {
                    printf("Error No: %d\n", errno);
                    perror("fwrite Error: ");
                    exit(1);
                }
                printf("Update Successfully\n");
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
    //read student index number
    printf("Enter student index number: ");
    scanf("%s", student_index);
    bool isFound = false;

    //open file with read write options
    file1 = fopen("student_marks.dat", "r+");
    //open file with read and appending
    file2 = fopen("cpy.dat","a+");
    if (file1 == NULL)
    {
        perror("student_marks.dat: ");
        printf("Error No %d\n", errno);
        exit(1);
    }
    if (file2 == NULL)
    {
        perror("cpy.dat: ");
        printf("Error No %d\n", errno);
        exit(1);
    }

    while (1)
    {
        //read data from file 
        fread(&student, sizeof(student_marks), 1, file1);
        if (feof(file1))
        {
            break;
        }
        if ((errNo = ferror(file1)) > 0)
        {
            perror("fread error: ");
            printf("ferror: %d\n", errNo);
            exit(1);
        }
        else
        {
            //find student and update data
            if(strcmp(student.student_index,student_index) != 0){
                // write student data to file
                int wrtRe = fwrite(&student, sizeof(student_marks), 1, file2); 
                int result;

                // write error handaling
                if (wrtRe < 0) 
                {
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
    
    //file remove error handaling
    result = remove("student_marks.dat");
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
        printf("Delete Successfully\n");
    }else{
        printf("No record to Delete\n");
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

    printf("Generated 100 records\n\n");
}

void printSeperationLine(){
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
}

