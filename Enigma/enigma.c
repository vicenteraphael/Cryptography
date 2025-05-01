#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rotors.c"

typedef struct plugboard {
    char* board;
} Plugboard;

Plugboard* create_plugboard () {
    Plugboard* plugboard = malloc(sizeof(Plugboard));
    for (int i = 0; i < 13; ++i) plugboard->board[i] = '\t';
    return plugboard;
}

Rotor* rotorInitialize (FILE* configurations) {
    int top, type; char* buff = malloc(sizeof(char)*10);
    fscanf (configurations, "%s %s: %d", buff, buff, top);
    FILE* rotors;
    if ((rotors = fopen("rotors.txt", "r")) == NULL) {
        printf ("Error opening the rotors file\n");
        exit(1);
    }
    if (buff == "I") {
        type = 1;
    } else if (buff == "II") {
        type = 2;
    } else if (buff == "III") {
        type = 3;
    } else if (buff == "IV") {
        type = 4;
    } else {
        type = 5;
    }
    return create_rotor(rotors, type, top);
}

void set_variables(Rotor** rotor1, Rotor** rotor2, Rotor** rotor3, Plugboard** plugboard) {
    FILE* configurations;
    if ((configurations = fopen("configure.txt", "r")) == NULL) {
        printf ("Error opening the configurations file");
        exit(1);
    }
    fseek(configurations, 72, SEEK_SET);
    char* buff = malloc(sizeof(char)*3);

    *rotor1 = rotorInitialize(configurations);
    *rotor2 = rotorInitialize(configurations);
    *rotor3 = rotorInitialize(configurations);
    
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