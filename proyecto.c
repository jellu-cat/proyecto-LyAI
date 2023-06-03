#include <stdio.h>
#include<string.h>

// TODO: Agregar el archivo a leer como segundo argumento
// TODO: Validar fin del archivo y mandar error si no se ha cerrado
// el comentario multilínea

void print_string(char* string){
    int i = 0;

    while(string[i] != '\0'){
        printf("%c", string[i]);
        i++;
    }
    printf("\n");
}

void print_state(char* string, int i, char state){
    char character = string[i];
    if(state == 'F'){
        printf("%c, Q(F)\n", character);
    } else if(state == 'E'){
        printf("%c, Q(E)\n", character);
    } else {
        printf("%c (%d), Q(%c)\n", character, character, state);
    }
}

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

char automata_comentarios(char* string){
    char state = '0';
    int i = 0;
    int iter = 0;
    char character = string[i];

    printf("Entrada autómata comentarios: ");
    print_string(string);

    while (character != '\0'){

        switch (state) {
        }

        print_state(string, i, state);

        if(state == 'E'){
            break;
        }
        i++;
        character = string[i];
    }

    if(state == 'E'){
        state = i + 48;
    }


    if(character == '\0' && state != 'F'){
        state = '.';
    }
    return state;
}

char automata_funciones(char* string){
    char state = '0';
    int i = 0;
    int iter = 0;
    char character = string[i];

    printf("Entrada autómata funciones: ");
    print_string(string);

    while (character != '\0'){

        switch (state) {
        }

        print_state(string, i, state);

        if(state == 'E'){
            break;
        }
        i++;
        character = string[i];
    }

    if(state == 'E'){
        state = i + 48;
    }


    if(character == '\0' && state != 'F'){
        state = '.';
    }
    return state;
}

int main(){
    FILE *f;
    char c[1000];
    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    char state = '0'; // 48
    int exit = 0;

    f = fopen("test-1.txt", "r");
    if (!f){
        exit = 1;
        exit = error_message(exit);
    }
    else{
        while((read = getline(&line, &len, f)) != -1){
            printf("------------\n");
            char character = line[0];
            if(character == '/'){
                state = automata_comentarios(line);
            }
            if(character == 'c'){
                state = automata_funciones(line);
            }
        }
    }

    if (state != 'E'){
        exit = 0;
    }

    return exit;
}
