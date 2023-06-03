#include <stdio.h>
#include<string.h>

int error_message(int error){
    /*
     * Imprime mensajes de error relacionados con el manejo de
     * archivos.
     */
    char message[100];
    switch (error) {
    case 1:
        strcpy(message, "Archivo no encontrado.");
        break;
    }

    if(error > 0){
        error = 2;
    }
    if (error != 0){
        printf("ERROR: %s\n", message);
    }
    return error;
}

int error_state_message(char error){
    /*
     * Se encarga de imprimir los mensajes de error y convertir los
     * estados de error del autómata en los estados de salida del
     * programa.
     * El programa sale únicamente con tres estados:
     * 0 si no hubo ningún error
     * 1 si no se encontró el archivo
     * 2 si hubo algún error en el autómata
     */
    char message[100];
    switch (error) {
    case '1':
        strcpy(message, "Archivo no encontrado.");
        break;
    }

    if(error > 1){
        error = 2;
    }
    if (error != 0){
        printf("ERROR: %s\n", message);
    }
    return error;
}

char automat(char* string){
    char state = '0';
    return state;
}

int main(){
    FILE *f;
    char c[1000];

    char state = '0'; // 48
    int exit = 0;

    f = fopen("test-1.txt", "r");
    if (!f){
        exit = 1;
        exit = error_message(exit);
    }
    else{
        while(fgets(c, 1000, f)){
            char line[1000];
            strcpy(line, c);
            printf("%s", line);
            state = automat(line);
        }
    }

    if (state != 'E'){
        exit = 0;
    }

    return exit;
}
