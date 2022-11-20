#include <stdio.h>    // printf function
#include <stdlib.h>   // exit function
#include <errno.h>    // error handling


// structure of Student Data
typedef struct student_marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

typedef enum dataType{MIN,MAX,COUNT,AVG}dataType;

float getStudentData(dataType markstype);

int main(int argc, char const *argv[])
{

    int studentCount = getStudenCount(COUNT);
    float avg = getStudenCount(AVG);
    printf("avg %f\n",avg/studentCount);
    return 0;
}



//function for calculate min max avg and count
float getStudentData(dataType datatype){
    FILE* file = fopen("student_marks.dat","r");
    student_marks student;
    float retunValue = 0;
    int errNo;
    float min = 100;
    float max = 0;
    float avg = 0;
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
            switch (datatype)
            {
            case COUNT:
                retunValue++;
                break;
            case MIN:
                if(student.assignmt01_marks<min)min = student.assignmt01_marks;
                retunValue = min;
                break;
            case MAX:
                if(student.assignmt01_marks>max)max = student.assignmt01_marks;
                retunValue = max;
                break;
            case AVG:
                avg += student.assignmt01_marks;
                break;
            default:
                break;
            }
            
            
        }
    }
    if(datatype == AVG)retunValue = avg;
    fclose(file);
    return retunValue;
}