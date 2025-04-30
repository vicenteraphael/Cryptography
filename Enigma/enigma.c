#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct rotor {
    int top;
    int module;
    struct rotor* next;
} Rotor;

Rotor* create_rotor (int ptr) {
    Rotor* rotor = malloc(sizeof(Rotor));
    rotor->top = ptr;
    rotor->module = 27;
    return rotor;
}

int rotate(Rotor* rotor) {
    rotor->top = (rotor->top + 1) % rotor->module;
    if (rotor->top == 0) return ++rotor->top;
    return 0;
}

int get_rotorNumber (FILE* configurations, char* buff) {
    fscanf(configurations, "%s %s %s", buff, buff, buff);
    fseek(configurations, 2, SEEK_CUR);
    return atoi(buff);
}

typedef struct plugboard {
    char* board;
} Plugboard;

Plugboard* create_plugboard () {
    Plugboard* plugboard = malloc(sizeof(Plugboard));
    for (int i = 0; i < 13; ++i) plugboard->board[i] = '\t';
    return plugboard;
}

void set_variables(Rotor** rotor1, Rotor** rotor2, Rotor** rotor3, Plugboard** plugboard) {
    FILE* configurations;
    if ((configurations = fopen("configure.txt", "r")) == NULL) {
        printf ("Error opening the configurations file");
        exit(1);
    }
    fseek(configurations, 72, SEEK_SET);
    char* buff = malloc(sizeof(char)*3);

    *rotor1 = create_rotor(get_rotorNumber(configurations, buff));
    *rotor2 = create_rotor(get_rotorNumber(configurations, buff));
    *rotor3 = create_rotor(get_rotorNumber(configurations, buff));
    
    *plugboard = create_plugboard();
    
    fseek(configurations, 64, SEEK_CUR);

    char src[2], dest[2];
    while (fscanf(configurations, "%s %s %s", src, buff, dest) != EOF) {
        (*plugboard)->board[(int)src[0]-65] = dest[0];
        (*plugboard)->board[(int)dest[0]-65] = src[0];
    }

}

int main() {
    int ans;
    printf ("Welcome to Raphael's adaptation of the Enigma Machine!\nDon't forget to configure your enigma in the 'configure.c' archive.");
    Rotor *rotor1, *rotor2, *rotor3;
    Plugboard *plugboard;
    set_variables(&rotor1, &rotor2, &rotor3, &plugboard);

    while (1) {
        printf ("\n\nDo you want to:\n\n1) Encrypt\n2) Exit\n\n");
        scanf ("%d", &ans);
        switch (ans) {
            case 1:
                            
                break;
            case 2:
                return 0;
            default:
                printf ("*Invalid option*\n");
        }
    }
}