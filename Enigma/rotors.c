#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct rotor {
    int top, notch;
    char *circuit;
    struct rotor* next;
} Rotor;

void set_circuit (FILE* rotors, char* buff, Rotor** rotor) {
    char src[2], dest[2];
    for (int i = 0; i < 26; ++i) {
        fscanf(rotors, "%s %s %s", src, buff, dest);
        (*rotor)->circuit[(int)src[0]-65] = dest[0];
        fseek(rotors, 2, SEEK_CUR);
    }
}

Rotor* create_rotor (FILE* rotors, char *type, int top, char* buff) {
    Rotor* rotor = malloc(sizeof(Rotor));
    rotor->circuit = malloc(sizeof(char)*26);
    rotor->top = top;
    if (strcmp(type,"I") == 0) {
        fseek(rotors, 78, SEEK_SET);
    } else if (strcmp(type, "I") == 0) {
        fseek(rotors, 320, SEEK_SET);
    } else if (strcmp(type, "III") == 0) {
        fseek(rotors, 566, SEEK_SET);
    } else if (strcmp(type, "IV") == 0) {
        fseek(rotors, 809, SEEK_SET);
    } else {
        fseek(rotors, 1052, SEEK_SET);
    }
    set_circuit(rotors, buff, &rotor);
    fseek(rotors, 2, SEEK_CUR);
    fscanf (rotors, "%s %s", buff, buff);
    rotor->notch = (int)buff[0]-65;
    fclose(rotors);

    return rotor;
}

int rotate(Rotor* rotor) {
    rotor->top = (rotor->top + 1) % 26;
    return (rotor->top + 65 == rotor->notch -1);
}