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
            createStudentRecrod();
            break;
        case 2:
            readAllRecords();
            break;
        case 3:
            printSeperationLine();
            generateRecodes();
            break;
        case 4:
            printSeperationLine();
            updateRecode();
            break;
        case 5:
            exit(0);
            break;
        }
     }while(1);
    return 0;
}
