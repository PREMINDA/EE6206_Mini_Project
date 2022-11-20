#include <stdio.h>    // printf function
#include <stdlib.h>   // exit function
#include <errno.h>    // error handling
#include <unistd.h>   // low IO


// structure of Student Data
typedef struct student_marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

typedef enum summeryData{MIN,MAX,COUNT,AVG,LESS5}summeryData;

float getStudentSummery(summeryData markstype);

int main(int argc, char const *argv[])
{
    //file descriptor 1 2 and 3
    int file_des1[2];
    int file_des2[2];
    int file_des3[2];

    //get all student count
    int studentCount = getStudentSummery(COUNT);

    //reate and cheack errors for file descriptors 1 2 and 3
    if(pipe(file_des1)==-1){
        perror("pipe1 error: ");
        printf("Error No: %d\n",errno);
        exit(0);//exit from the process

    }else if(pipe(file_des2)==-1){
        perror("pipe2 error: ");
        printf("Error No: %d\n",errno);
        exit(0);//exit from the process

    }else if(pipe(file_des3)==-1){
        perror("pipe2 error: ");
        printf("Error No: %d\n",errno);
        exit(0);//exit from the process

    }else{
        //create Process 1
        pid_t PID1 = fork();
        if(PID1 == -1){
            perror("PID1 error: ");
            printf("Error No: %d\n",errno);
            exit(0);
        }else if(PID1 == 0){
            //inside chiled 1
            //get MIN marks
            float min = getStudentSummery(MIN);
            
            close(file_des1[0]);
            //write data in to file descriptor
            if(write(file_des1[1],&min,sizeof(float))<0){
                perror("Write error number: ");
                printf("Error No: %d\n",errno);
                exit(0);
            }
            close(file_des1[1]);

        }else{
            //create Process 2
            pid_t PID2 = fork();
            if(PID2 == -1){
                perror("PID2 error: ");
                printf("Error No: %d\n",errno);
                exit(0);
            }else if(PID2 == 0){
                //inside childe 2
                //get MAX mark
                float max = getStudentSummery(MAX);
                
                close(file_des2[0]);
                //write data in to file descriptor
                if(write(file_des2[1],&max,sizeof(float))<0){
                    perror("Write error number: ");
                    printf("Error No: %d\n",errno);
                    exit(0);
                }
                close(file_des2[1]);
            }else{
                //create Process 3
                pid_t PID3 = fork();
                if(PID3 == -1){
                    perror("PID3 error: ");
                    printf("Error No: %d\n",errno);
                    exit(0);
                }else if(PID3 == 0){
                    //inside childe 3
                    //get AVG marks
                    float avg = getStudentSummery(AVG);
                    avg /=studentCount;

                    close(file_des3[0]);
                    //write data in to file descriptor
                    if(write(file_des3[1],&avg,sizeof(float))<0){
                        perror("Write error number: ");
                        printf("Error No: %d\n",errno);
                        exit(0);
                    }
                    close(file_des3[1]);
                }else{
                    float minMarks,maxMarks,avgMarks;
                    int lessThan5;

                    //read data comes from pipes
                    close(file_des1[1]);
                    if(read(file_des1[0],&minMarks,sizeof(int))<0){
                        perror("read error number: ");
                        printf("Error No: %d\n",errno);
                        exit(0);
                    }
                    close(file_des1[0]);

                    //read data comes from pipes
                    close(file_des2[1]);
                    if(read(file_des2[0],&maxMarks,sizeof(int))<0){
                        perror("read error number: ");
                        printf("Error No: %d\n",errno);
                        exit(0);
                    }
                    close(file_des2[0]);

                    //read data comes from pipes
                    close(file_des3[1]);
                    if(read(file_des3[0],&avgMarks,sizeof(int))<0){
                        perror("read error number: ");
                        printf("Error No: %d\n",errno);
                        exit(0);
                    }
                    close(file_des3[0]);

                    //get count less than 5%
                    lessThan5 = getStudentSummery(LESS5);

                    printf("MIN marks = %.2f\nMAX marks =  %.2f\nAVG marks = %f\nCount less than 5%% = %d\n",minMarks,maxMarks,avgMarks,lessThan5);
                }
            }
        }
    }

    return 0;
}


//function for calculate min max avg and count
float getStudentSummery(summeryData datatype){
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
            //student count
            case COUNT:
                retunValue++;
                break;
            //find minimum
            case MIN:
                if(student.assignmt01_marks<min)min = student.assignmt01_marks;
                retunValue = min;
                break;
            //find maximum
            case MAX:
                if(student.assignmt01_marks>max)max = student.assignmt01_marks;
                retunValue = max;
                break;
            //find avg
            case AVG:
                avg += student.assignmt01_marks;
                break;
            //find count mark lessthan 5%
            case LESS5:
                if(student.assignmt01_marks*6.66667<5.0000){
                    retunValue++;
                }
            default:
                break;
            }
            
            
        }
    }
    if(datatype == AVG)retunValue = avg;
    fclose(file);
    return retunValue;
}