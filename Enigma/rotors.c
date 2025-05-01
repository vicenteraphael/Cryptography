#include <stdio.h>
#include <stdlib.h>

typedef struct rotor {
    int top, notch;
    char* circuit;
    struct rotor* next;
} Rotor;

void set_circuit (FILE* rotors, char* buff, Rotor** rotor) {
    char *src = malloc(sizeof(char)), *dest = malloc(sizeof(char));
    for (int i = 0; i < 26; ++i) {
        fscanf(rotors, "%s %s %s", src, buff, dest);
        (*rotor)->circuit[(int)src-65] = dest;
        (*rotor)->circuit[(int)dest-65] = dest;
        fseek(rotors, 2, SEEK_CUR);
    }
}

Rotor* create_rotor (FILE* rotors, int type, int top) {
    Rotor* rotor = malloc(sizeof(Rotor));
    char* buff = malloc(sizeof(char)*10000);
    buff = malloc(sizeof(char)*1000);
    if (type == 1) {
        fseek(rotors, 78, SEEK_CUR);
    } else if (type == 2) {
        fseek(rotors, 260, SEEK_CUR);
    } else if (type == 3) {
        fseek(rotors, 442, SEEK_CUR);
    } else if (type == 4) {
        fseek(rotors, 624, SEEK_CUR);
    } else if (type == 5) {
        fseek(rotors, 806, SEEK_CUR);
    }
    set_circuit(rotors, buff, &rotor);
    fseek(rotors, 2, SEEK_CUR);
    fscanf (rotors, "%s %d", buff, rotor->notch);
    rotor->notch -= 65;

    return rotor;
}

int rotate(Rotor* rotor) {
    rotor->top = (rotor->top + 1) % 26;
    if (rotor->top + 65 == (int) rotor->notch -1) return 1;
    return 0;
}