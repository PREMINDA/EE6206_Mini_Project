#include <stdio.h>
#include "header/action.h"


int main(int argc, char const *argv[])
{
    int choice = 0;
    char term;
    
     do{

        printf("1. Create Record \n");
        printf("2. Update Record \n");
        printf("3. Delete Record \n");
        printf("4. Read All Records \n");
        printf("5. Generate Records(100) \n");
        printf("6. Exit \n\n");
        
        printSeperationLine();
        printf("Enter Your Choice : ");
        if(scanf("%d%c", &choice, &term) != 2 || term != '\n'){
            printf("Invalid Option");
            break;
        };
    
        switch (choice)
        {
        case 1:
            printSeperationLine();
            createStudentRecord();
            break;
        case 2:
            printSeperationLine();
            updateRecord();
            break;
        case 3:
            printSeperationLine();
            deleteRecord();
            break;
        case 4:
            readAllRecords();
            break;
        case 5:
            printSeperationLine();
            generateRecords();
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("Invalid Option \n");
            break;
        }
     }while(1);
    return 0;
}
