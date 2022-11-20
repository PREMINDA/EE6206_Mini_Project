#include "../header/random.h"

//generate random marks
float randomMarks(int margin)
{
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