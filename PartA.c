#include <stdio.h>
#include "header/action.h"

int main(int argc, char const *argv[])
{
    int choice;
    
     do{
        printSeperationLine();
        printf("Enter Your Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printSeperationLine();
            createStudentRecord();
            break;
        case 2:
            readAllRecords();
            break;
        case 3:
            printSeperationLine();
            generateRecords();
            break;
        case 4:
            printSeperationLine();
            updateRecord();
            break;
        case 5:
            printSeperationLine();
            deleteRecord();
            break;
        case 6:
            exit(0);
            break;
        }
     }while(1);
    return 0;
}
