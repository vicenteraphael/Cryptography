#include "rotors.c"
#include <string.h>

typedef struct plugboard {
    char* board;
} Plugboard;

Plugboard* create_plugboard () {
    Plugboard* plugboard = malloc(sizeof(Plugboard));
    plugboard->board = malloc(sizeof(char)*13);
    for (int i = 0; i < 13; ++i) plugboard->board[i] = '\0';
    return plugboard;
}


Rotor* rotorInitialize (FILE* configurations, char* buff, char* type) {
    int top;
    fscanf (configurations, "%s %s %d", buff, type, &top);
    type[strlen(type)-1] = '\0';
    fseek(configurations, 5, SEEK_CUR);

    FILE* rotors;
    if ((rotors = fopen("rotors.txt", "r")) == NULL) {
        printf ("Error opening the rotors file\n");
        exit(1);
    }

    return create_rotor(rotors, type, top, buff);
}

void set_variables(Rotor** rotor1, Rotor** rotor2, Rotor** rotor3, Plugboard** plugboard) {
    FILE* configurations;
    if ((configurations = fopen("configure.txt", "r")) == NULL) {
        printf ("Error opening the configurations file");
        exit(1);
    }

    fseek(configurations, 73, SEEK_SET);
    char* buff = malloc(sizeof(char)*10), *type = malloc(sizeof(char)*4);

    *rotor1 = rotorInitialize(configurations, buff, type);
    *rotor2 = rotorInitialize(configurations, buff, type);
    *rotor3 = rotorInitialize(configurations, buff, type);
    
    *plugboard = create_plugboard();
    
    fseek(configurations, 64, SEEK_CUR);

    char src[2], dest[2];
    while (fscanf(configurations, "%s %s %s", src, buff, dest) != EOF) {
        (*plugboard)->board[(int)src[0]-65] = dest[0];
        (*plugboard)->board[(int)dest[0]-65] = src[0];
    }

}