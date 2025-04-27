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

void set_variables() {
    FILE* configurations;
    if ((configurations = fopen("configure.txt", "r")) == NULL) {
        printf ("Error opening the configurations file");
        exit(1);
    }
    fseek(configurations, 72, SEEK_SET);
    char* buff = malloc(sizeof(char)*3);

    Rotor* rotor1 = create_rotor(get_rotorNumber(configurations, buff));
    Rotor* rotor2 = create_rotor(get_rotorNumber(configurations, buff));
    Rotor* rotor3 = create_rotor(get_rotorNumber(configurations, buff));
    
    char* plugboard = malloc(sizeof(char)*13);
    
    fseek(configurations, 62, SEEK_CUR);

}

int main() {
    int ans;
    printf ("Welcome to Raphael's adaptation of the Enigma Machine!\nDon't forget to configure your enigma in the 'configure.c' archive.");
    while (1) {
        printf ("\n\nDo you want to:\n\n1) Encrypt\n2) Exit\n\n");
        scanf ("%d", &ans);
        switch (ans) {
            case 1:
                set_variables();
                break;
            case 2:
                return 0;
            default:
                printf ("*Invalid option*\n");
        }
    }
}