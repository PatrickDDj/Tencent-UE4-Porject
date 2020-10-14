#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *file = fopen("2.bin","w");
    unsigned short a = 10;

    char c[100];
    memcpy(c, &a, sizeof(a));

    fwrite(c, sizeof(char), 2, file);

    fclose(file);


    FILE *file = fopen("2.bin","r");
    unsigned short a;

    char c[100];
    // memcpy(c, &a, sizeof(a));

    fread(c, sizeof(char), 2, file);
    memcpy(&a, c, 2);

    fclose(file);

    printf("%d\n", a);



    return 0;
    
}

