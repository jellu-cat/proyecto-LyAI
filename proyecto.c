#include <stdio.h>
#include <string.h>

// TODO: Validar fin del archivo y mandar error si no se ha cerrado
// el comentario multilínea
// TODO: Permir la lectura de otra línea si el autómata terminó con
// Qf
// Manejar errores

void print_string(char *string) {
    int i = 0;

    while (string[i] != '\0') {
        printf("%c", string[i]);
        i++;
    }
    printf("\n");
}

void print_state(char *string, int i, char state) {
    char character = string[i];
    if (state == 'F') {
        printf("%c, Q(F)\n", character);
    } else if (state == 'E') {
        printf("%c, Q(E)\n", character);
    } else {
        printf("%c (%d), Q(%c)\n", character, character, state);
    }
}

int error_message(int error, char *file) {
    /*
     * Imprime mensajes de error relacionados con el manejo de
     * archivos.
     */
    char message[100];
    switch (error) {
    case 1:
        strcpy(message, "Archivo no encontrado.");
        break;
    case 2:
        strcpy(message, "Se recibió más de un archivo.");
        break;
    case 3:
        strcpy(message, "No se recibió archivo.");
        break;
    }
    
    if (error > 0) {
        error = 2;
    }
    if (error != 0) {
        printf("ERROR: %s\n", message);
    }
    return error;
}

int error_state_message(char error) {
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
    
    if (error > 1) {
        error = 2;
    }
    if (error != 0) {
        printf("ERROR: %s\n", message);
    }
    return error;
}

char statec_0(char character, char state) {
    if (character == '/') {
        state = '1';
    } else {
        state = 'E';
        printf("Cadena no valida, no es un comentario: ");
    }
    return state;
}

char statec_1(char character, char state) {
    if (character == '/') {
        state = '2';
    } else if (character == '*') {
        state = '4';
    } else {
        state = 'E';
        printf("Cadena no valida, no es un comentario: ");
    }
    return state;
}

char statec_2(char character, char state) {
    
    if (character == '\n') {
        state = 'F';
    } else if (character >= 32 && character <= 126) {
        state = '3';
    } else {
        state = 'E';
        printf("Cadena no valida: ");
    }
    return state;
}

char statec_3(char character, char state) {
    if (character >= 32 && character <= 126) {
        state = '3';
    } else if (character == '\n') {
        state = 'F';
    } else {
        state = 'E';
        printf("Error en el comentario: ");
    }
    return state;
}

char statec_4(char character, char state) {
    if (character == '*') {
        state = '6';
    } else if (character != '/') {
        state = '5';
    } else {
        state = 'E';
        printf(
               "Se coloco un caracter no permitido para el comentario multilinea: ");
    }
    return state;
}

char statec_5(char character, char state) {
    
    if (character == '*') {
        state = '6';
    } else if (character != '/') {
        state = '5';
    } else {
        state = 'E';
        printf(
               "Se coloco un caracter no permitido para el comentario multilinea: ");
    }
    return state;
}

char statec_6(char character, char state) {
    if (character == '/') {
        state = 'F';
    } else {
        state = 'E';
        printf("No se cerro correctamente el comentario multilinea: ");
    }
    return state;
}

char statec_final(char character, char state) {
    if (character == '\0' || character == '\n') {
        state = 'F';
    } else {
        state = 'E';
        printf("No se llego al estado final, error de sintaxis: ");
    }
    return state;
}

char automata_comentarios(char *string) {
    
    int i = 0;
    int iter = 0;

    char state = '0';
    char character = string[i];
    
    printf("Entrada: ");
    print_string(string);
    printf("\n");
    
    while (character != '\0') {
        switch (state) {
        case '0':
            state = statec_0(character, state);
            break;
        case '1':
            state = statec_1(character, state);
            break;
        case '2':
            state = statec_2(character, state);
            break;
        case '3':
            state = statec_3(character, state);
            break;
        case '4':
            state = statec_4(character, state);
            break;
        case '5':
            state = statec_5(character, state);
            break;
        case '6':
            state = statec_6(character, state);
            break;
        case 'F':
            state = statec_final(character, state);
            break;
        }
        
        print_state(string, i, state);
        
        if (state == 'E') {
            break;
        }
        i++;
        character = string[i];
    }
    
    if (state == 'E') {
        state = i + 48;
    }
    
    if (character == '\0' && state != 'F') {
        state = '.';
    }
    
    return state;
}

char statef_0(char character, char state) {
    if (character == 'c') {
        state = '1';
    } else {
        state = 'E';
        printf("Cadena no valida, no es una instrucción cin o cout: ");
    }
    return state;
}

char statef_1(char character, char state) {
    if (character == 'o') {
        state = '2';
    } else if (character == 'i') {
        state = 'g';
    } else {
        state = 'E';
        printf("Cadena no valida, no es una instrucción cin o cout: ");
    }
    return state;
}

char statef_2(char character, char state) {
    if (character == 'u') {
        state = '3';
    } else {
        state = 'E';
        printf("Cadena no valida, no es una instrucción cout: ");
    }
    return state;
}

char statef_3(char character, char state) {
    if (character == 't') {
        state = '4';
    } else {
        state = 'E';
        printf("Cadena no valida, no es una instrucción cout: ");
    }
    return state;
}

char statef_4(char character, char state) {
    if (character == ' ') {
        state = '5';
    } else if (character == '<') {
        state = '6';
    } else {
        state = 'E';
        printf("Cadena no valida, sintaxis de cout incorrecta (<): ");
    }
    return state;
}

char statef_5(char character, char state) {
    if (character == '\t') {
        state = '5';
    } else if (character == '<') {
        state = '6';
    } else {
        state = 'E';
        printf("Cadena no valida, sintaxis de cout incorrecta (<): ");
    }
    return state;
}

char statef_6(char character, char state) {
    if (character == '<') {
        state = '7';
    } else {
        state = 'E';
        printf("Cadena no valida, sintaxis de cout incorrecta (falta segundo <): ");
    }
    return state;
}

char statef_7(char character, char state) {
    
    if (character == 32) {
        state = '7';
    } else if (character == '\t') {
        state = '8';
    } else if (character == 34) {
        state = '9';
    } else if (character >= 48 && character <= 57) {
        state = 'c';
    } else if (character >= 65 && character <= 122) {
        state = 'd';
    } else {
        state = 'E';
        printf("Cadena no valida, sintaxis de cout incorrecta: ");
    }
    return state;
}

char statef_8(char character, char state) {
    if (character == '\t') {
        state = '8';
    } else if (character == 34) {
        state = '9';
    } else if (character >= 48 && character <= 57) {
        state = 'c';
    } else if (character >= 65 && character <= 122) {
        state = 'd';
    } else {
        state = 'E';
        printf("Cadena no valida, sintaxis de cout incorrecta: ");
    }
    return state;
}

char statef_9(char character, char state) {
    if (character == '"') {
        state = 'b';
    } else if (character >= 0 && character <= 128) {
        state = 'a';
    }
    
    else {
        state = 'E';
        printf("No se cerro correctamente la cadena a imprimir: ");
    }
    return state;
}

char statef_a(char character, char state) {
    if (character == '"') {
        state = 'b';
    } else if (character >= 0 && character <= 128) {
        state = 'a';
    }
    
    else {
        state = 'E';
        printf("No se cerro correctamente la cadena a imprimir: ");
    }
    return state;
}

char statef_b(char character, char state) {
    if (character == ';') {
        state = 'F';
    } else if (character == 32) {
        state = 'b';
    }
    
    else if (character == '<') {
        state = '6';
    } else {
        state = 'E';
        printf("No se cerro correctamente la instrucción o no se agregaron "
               "cadenas/variables adicionales: ");
    }
    return state;
}

char statef_c(char character, char state) {
    if (character == ';') {
        state = 'F';
    } else if (character >= 48 && character <= 57) {
        state = 'c';
    } else {
        state = 'E';
        printf("No se cerro correctamente la instrucción o no se agregaron "
               "cadenas/variables adicionales: ");
    }
    return state;
}

char statef_d(char character, char state) {
    if (character == ';') {
        state = 'F';
    } else if (character >= 0 && character <= 128) {
        state = 'e';
    } else {
        state = 'E';
        printf("No se cerro correctamente la instrucción o se agregaron "
               "cadenas/variables adicionales: ");
    }
    return state;
}

char statef_e(char character, char state) {
    if (character == ';') {
        state = 'F';
    } else if (character >= 0 && character <= 128) {
        state = 'e';
    } else {
        state = 'E';
        printf("No se cerro correctamente la instrucción o se agregaron "
               "cadenas/variables adicionales: ");
    }
    return state;
}

// Saltar aqui cuando se encuentra la i

char statef_g(char character, char state) {
    if (character == 'n') {
        state = 'h';
    } else {
        state = 'E';
        printf("Cadena no valida, sintaxis de cin incorrecta: ");
    };
    return state;
}

char statef_h(char character, char state) {
    
    if (character == ' ') {
        state = 'i';
    } else if (character == '>') {
        state = 'j';
    } else {
        state = 'E';
        printf("Cadena no valida, sintaxis de cout incorrecta (> o espacio): ");
    }
    return state;
}

char statef_i(char character, char state) {
    
    if (character == ' ') {
        state = 'i';
    } else if (character == '>') {
        state = 'j';
    } else {
        state = 'E';
        printf("Cadena no valida, sintaxis de cout incorrecta (> o espacio): ");
    }
    return state;
}

char statef_j(char character, char state) {
    
    if (character == '>') {
        state = 'k';
    } else {
        state = 'E';
        printf(
               "Cadena no valida, sintaxis de cout incorrecta (falta el segundo >): ");
    }
    return state;
}

char statef_k(char character, char state) {
    
    if (character == ' ') {
        
        state = 'l';
    } else if (character == '_' || character >= 65 || character <= 90) {
        state = 'm';
    } else {
        state = 'E';
        printf("Cadena no valida, variable con sintaxis incorrecta: ");
    }
    return state;
}

char statef_l(char character, char state) {
    if (character == ' ') {
        state = 'l';
    } else if (character == '_' || character >= 65 && character <= 90) {
        state = 'm';
    } else {
        state = 'E';
        printf("Cadena no valida, variable con sintaxis incorrecta: ");
    }
    return state;
}

char statef_m(char character, char state) {
    if (character >= 65 && character <= 90 ||
        character >= 97 && character <= 122 || character == '*') {
        state = 'n';
    } else {
        state = 'E';
        printf("Cadena no valida, variable con caracteres invalidos: ");
    }
    return state;
}

char statef_n(char character, char state) {
    if (character == ';') {
        state = 'F';
    } else if (character >= 48 && character <= 57 ||
               character >= 65 && character <= 90 ||
               character >= 97 && character <= 122) {
        state = 'n';
    } else {
        state = 'E';
        printf("No se cerro correctamente la instrucción: ");
    }
    return state;
}

char statef_final(char character, char state) {
    if (character == '\0' || character == '\n') {
        state = 'F';
    } else {
        state = 'E';
        printf("No se llego al estado final, error de sintaxis: ");
    }
    return state;
}

char automata_funciones(char *string) {
    
    int i = 0;
    int iter = 0;
    
    char state = '0';
    char character = string[i];
    
    printf("Entrada: ");
    print_string(string);
    printf("\n");
    
    while (character != '\0') {
        switch (state) {
        case '0':
            state = statef_0(character, state);
            break;
        case '1':
            state = statef_1(character, state);
            break;
        case '2':
            state = statef_2(character, state);
            break;
        case '3':
            state = statef_3(character, state);
            break;
        case '4':
            state = statef_4(character, state);
            break;
        case '5':
            state = statef_5(character, state);
            break;
        case '6':
            state = statef_6(character, state);
            break;
        case '7':
            state = statef_7(character, state);
            break;
        case '8':
            state = statef_8(character, state);
            break;
        case '9':
            state = statef_9(character, state);
            break;
            
            // estado 10
        case 'a':
            state = statef_a(character, state);
            break;
            // estado 11
        case 'b':
            state = statef_b(character, state);
            break;
            // estado 12
        case 'c':
            state = statef_c(character, state);
            break;
            // estado 13
        case 'd':
            state = statef_d(character, state);
            break;
            // estado 14
        case 'e':
            state = statef_e(character, state);
            break;
            // Aqui ingresar los otros, de g a n
            
            // estado 15
        case 'g':
            state = statef_g(character, state);
            break;
            // estado 16
        case 'h':
            state = statef_h(character, state);
            break;
            // estado 17
        case 'i':
            state = statef_i(character, state);
            break;
            // estado 18
        case 'j':
            state = statef_j(character, state);
            break;
            // estado 19
        case 'k':
            state = statef_k(character, state);
            break;
            // estado 20
        case 'l':
            state = statef_l(character, state);
            break;
            // estado 21
        case 'm':
            state = statef_m(character, state);
            break;
            // estado 22
        case 'n':
            state = statef_n(character, state);
            break;
            
        case 'F':
            state = statef_final(character, state);
            break;
        }
        
        print_state(string, i, state);
        
        if (state == 'E') {
            break;
        }
        i++;
        character = string[i];
    }
    
    if (state == 'E') {
        state = i + 48;
    }
    
    if (character == '\0' && state != 'F') {
        state = '.';
    }
    
    return state;
}

int main(int argc, char *argv[]) {
    
    // variables de lectura de archivo
    FILE *f;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    // -------------------------------
    
    // argumentos del programa
    char *string = argv[1];
    // -----------------------
    
    char state = '0'; // 48
    int exit = 0;
    
    if (argc == 2) {
        f = fopen(argv[1], "r");
        if (!f) {
            exit = 1;
            exit = error_message(exit, argv[1]);
        }
        
        else {
            while ((read = getline(&line, &len, f)) != -1) {
                printf("------------\n");
                char character = line[0];
                if (character == '/') {
                    state = automata_comentarios(line);
                }
                if (character == 'c') {
                    state = automata_funciones(line);
                }
            }
        }
    }
    
    else if (argc > 2) {
        exit = 2;
        exit = error_message(exit, argv[1]);
    } else if (argc == 1) {
        exit = 3;
        exit = error_message(exit, argv[1]);
    }
    
    if (state != 'E') {
        exit = 0;
    }
    
    return exit;
}
