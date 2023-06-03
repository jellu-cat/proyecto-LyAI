#include <stdio.h>
#include<string.h>

void error_message(int exit){
    char message[100];
    switch (exit) {
    case 1:
        strcpy(message, "Archivo no encontrado.");
        break;
    }
    if (exit != 0){
        printf("ERROR: %s\n", message);
    }
}

int main(){
    FILE *f;
    char c[1000];
    int exit = 0;

    f = fopen("prueba-1.txt", "r");
    if (!f) exit = 1;
    else{
        while(fgets(c, 1000, f)){
            char line[1000];
            strcpy(line, c);
            printf("%s", line);
        }
    }

    error_message(exit);
    return exit;
}
