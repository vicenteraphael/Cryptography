#include <stdio.h>
#include <stdlib.h>

void set_to_default(FILE* configure) {
    if ((configure = fopen("configure.txt", "w+")) == NULL) {
        printf ("Error opening file");
        exit(1);
    }
    fprintf(configure, "ENIGMA MACHINE CONFIGURATIONS\n\nROTORS' NUMBERS DISPLAYED AT THE WINDOW:\n\n");
    fprintf(configure, "ROTOR I: %d\nROTOR II: %d\nROTOR III: %d\n\nPLUGBOARD:", 10, 10, 10);
    fclose(configure);
    printf ("THE CONFGURATIONS WERE RESTARTED SUCCESFULLY");
}

void display_configurations(FILE* configure, char *location) {
    if ((configure = fopen(location, "r")) == NULL) {
        printf ("Error opening file");
        exit(1);
    }

    int maxlen = 10000;
    char buff[maxlen];

    printf ("------------------------------------------------\n");
    while (fgets(buff, maxlen, configure)) {
        printf ("%s", buff);
    }
    printf ("\n------------------------------------------------");
    
    fclose(configure);
}

void reconfigure (FILE* configure) {
    int rotor, rotorTop, plugPairs;
    int rotors[] = {0, 0, 0, 0, 0};
    char srcPlug[13][2], destPlug[13][2], cardinals[3][3] = {{'s', 't'}, {'n', 'd'}, {'r', 'd'}};
    char roman[5][4] = {{'I'}, {'I', 'I'}, {'I', 'I', 'I'}, {'I', 'V'}, {'V'}};
    
    if ((configure = fopen("configure.txt", "w+")) == NULL) {
        printf ("Error opening the file\n");
        exit(1);
    }

    printf ("------------------------------------------------\nENIGMA MACHINE CONFIGURATIONS\n\nROTORS' NUMBERS DISPLAYED AT THE TOP:\n\n");
    fprintf(configure, "%s", "ENIGMA MACHINE CONFIGURATIONS\n\nROTORS' NUMBERS DISPLAYED AT THE WINDOW:\n");
    
    for (int i = 1; i <= 3; ++i) {
        while (1) {
            printf ("Choose one of the %d rotors to be the %d%s rotor: ", 6-i, i, cardinals[i-1]);
            scanf ("%d", &rotor);
            if (rotor > 0 && rotor < 6) {
                if (!rotors[rotor-1]) {
                    rotors[rotor-1] = 1;
                    while (1) {
                        printf ("Set its window number (1-26): ");
                        scanf ("%d", &rotorTop);
                        if (rotorTop > 0 && rotorTop < 27) break;
                        printf ("*Invalid option*\n");
                    }
                    break;
                } else {
                    printf ("That rotor is already being used.\n");
                }
            } else {
                printf ("*Invalid option*\n");
            }
        }
        fprintf (configure, "\nROTOR %s: %d", roman[rotor-1], rotorTop);
    }

    printf ("\n\nPLUGBOARD:\n\nEnter number of pairs of letters to be plugged:\n");
    scanf ("%d", &plugPairs);
    printf("For each of the following %d line(s), enter a pair of plugged letters separated by a blank space.\nI.e: 'A B':\n\n", plugPairs);
    fflush(stdin);
    for (int i = 0; i < plugPairs; ++i) {
        scanf ("%s %s", srcPlug[i], destPlug[i]);
    }
    fprintf(configure, "\n\nPLUGBOARD:\n");
    for (int i = 0; i < plugPairs; ++i) {
        fprintf(configure, "\n%s -> %s", srcPlug[i], destPlug[i]);
    }
    printf ("\n------------------------------------------------");
    
    fclose(configure);
}

int main() {
    int ans;
    FILE* configure;
    printf ("Welcome to Enigma's configurations options!");
    while (1) {
        printf("\n\nDo you want to:\n\n1) Set configurations to default\n2) Reconfigure\n3) Display rotors' configurations\n4) Display Enigma's current configurations\n5) Exit\n\n");
        scanf ("%d", &ans);
        switch (ans) {
            case 1:
                set_to_default(configure);
                break;
            case 2:
                reconfigure(configure);
                break;
            case 3:
                display_configurations(configure, "rotors.txt");
                break;
            case 4:
                display_configurations(configure, "configure.txt");
                break;
            case 5:
                return 0;
            default:
                printf ("*Invalid option*\n");
                break;
        }
    }
}