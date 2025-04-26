#include <stdio.h>
#include <stdlib.h>

typedef struct rotor {
    int top;
    int module;
    struct rotor* next;
} Rotor;

Rotor* create_rotor (int ptr) {
    Rotor* rotor = malloc(sizeof(Rotor));
    rotor->top = ptr;
    rotor->module = 26;
    return rotor;
}

int rotate(Rotor* rotor) {
    rotor->top = (rotor->top + 1) % rotor->module;
    if (rotor->top == 0) return 1;
    return 0;
}

int menu (int var, char message[]) {
    while (1) {
        printf ("%s", message);
        scanf ("%d", &var);
        if (var == 1 || var == 2 || var == 3) {
            return var;
        }
        printf ("*Invalid option*\n");
    }
}

void set_to_default(FILE* configure) {
    if ((configure = fopen("configure.txt", "w+")) == NULL) {
        printf ("Error opening file");
        exit(1);
    }
    fprintf(configure, "%s", "ENIGMA MACHINE CONFIGURATIONS\n\nROTORS' NUMBERS DISPLAYED AT THE TOP:\n\n");
    fprintf(configure, "%s", "ROTOR1: ");
    fprintf(configure, "%d\n", 10);
    fprintf(configure, "%s", "ROTOR2: ");
    fprintf(configure, "%d\n", 10);
    fprintf(configure, "%s", "ROTOR3: ");
    fprintf(configure, "%d\n\n", 10);
    fprintf(configure, "%s", "(THE MODULE PROPORTION FOR ALL ROTORS IS 26)\n\nPLUGBOARD:\n");
    for (int letter = 65; letter <= 90; ++letter) {
        fprintf(configure, "\n%c", letter);
        fprintf(configure, "%s", " -> ");
        fprintf(configure, "%s", "NULL");
    }
    printf ("\n");
    fclose(configure);
}

void display_configurations(FILE* configure) {
    if ((configure = fopen("configure.txt", "r")) == NULL) {
        printf ("Error opening file");
        exit(1);
    }
    int maxlen = 10000;
    char buff[maxlen];
    while (fgets(buff, maxlen, configure)) {
        printf ("%s", buff);
    }
    printf("\n");
    fclose(configure);
}

void reconfigure (FILE* configure) {
    int rotorTop;
    char plug[2];
    configure = fopen("configure.txt", "w+");
    printf ("ENIGMA MACHINE CONFIGURATIONS\n\nROTORS' NUMBERS DISPLAYED AT THE TOP:\n");
    fprintf(configure, "%s", "ENIGMA MACHINE CONFIGURATIONS\n\nROTORS' NUMBERS DISPLAYED AT THE TOP:\n\n");
    for (int i = 1; i <= 3; ++i) {
        printf ("ROTOR%d: ", i);
        scanf ("%d", &rotorTop);
        fprintf (configure, "%s%d %s %d", "\nROTOR", i, ":", rotorTop);
    }
    printf ("\n(THE MODULE PROPORTION FOR ALL ROTORS IS 26)\n\n");
    fprintf (configure, "%s", "\n(THE MODULE PROPORTION FOR ALL ROTORS IS 26)\n\n");
    printf ("PLUGBOARD (leave NULL for non-plugged letters):\n");
    fprintf(configure, "PLUGBOARD:\n");
    for (int letter = 65; letter <= 90; ++letter) {
        printf ("\n%c -> ", letter);
        scanf ("%s", plug);
        fprintf (configure, "\n%c %s %s", letter, "->", plug);
    }
    fclose(configure);
}

void configure () {
    int ans = menu(ans, "Do you want to:\n\n1) Set configurations to default\n2) Reconfigure\n3) Display current configuration\n\n");
    FILE* configure;
    if (ans == 1) {
        set_to_default(configure);
    }
    else if (ans == 2) {
        reconfigure(configure);
    }
    else if (ans == 3) {
        display_configurations(configure);
    }
}

int main() {
    int ans;
    printf ("Welcome to Raphael's program adaptation of the Enigma Machine!");
    while (1) {
        ans = menu(ans, "Do you wish to:\n\n1) Encrypt \n2) Configure\n3) Exit\n\n");
        if (ans == 3) {
            return 0;
        }
        else if (ans == 2) {
            configure();
        }    
    }
}