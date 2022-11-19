#include <stdio.h>
#include "header/action.h"

int main(int argc, char const *argv[])
{
    int choice;
    
     do{
        printf("Enter Your Choice \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printSeperationLine();
            createStudentRecrod();
            break;
        case 2:
            printSeperationLine();
            readAllRecords();
            break;
        case 3:
            exit(0);
            break;
        }
     }while(1);
    return 0;
}
