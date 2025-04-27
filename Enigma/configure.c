#include <stdio.h>
#include <stdlib.h>

void set_to_default(FILE* configure) {
    if ((configure = fopen("configure.txt", "w+")) == NULL) {
        printf ("Error opening file");
        exit(1);
    }
    fprintf(configure, "%s", "ENIGMA MACHINE CONFIGURATIONS\n\nROTORS' NUMBERS DISPLAYED AT THE TOP:\n\n");
    fprintf(configure, "%s %d\n%s %d\n%s %d\n\n", "1st ROTOR:", 10, "2nd ROTOR:", 10, "3rd ROTOR:", 10);
    fprintf(configure, "%s", "(THE MODULE PROPORTION FOR ALL ROTORS IS 26)\n\nPLUGBOARD (THE PLUGBOARD IS EMPTY BY DEFAULT):");
    fclose(configure);
    printf ("THE CONFIGURATIONS WERE RESTARTED SUCCESFULLY");
}

void display_configurations(FILE* configure) {
    if ((configure = fopen("configure.txt", "r")) == NULL) {
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
    int rotorTop, plugPairs;
    char cardinals[3][3] = {{'s', 't'}, {'n', 'd'}, {'r', 'd'}};
    char srcPlug[13][2], destPlug[13][2];
    configure = fopen("configure.txt", "w+");
    printf ("------------------------------------------------\nENIGMA MACHINE CONFIGURATIONS\n\nROTORS' NUMBERS DISPLAYED AT THE TOP:\n\n");
    fprintf(configure, "%s", "ENIGMA MACHINE CONFIGURATIONS\n\nROTORS' NUMBERS DISPLAYED AT THE TOP:\n");
    for (int i = 1; i <= 3; ++i) {
        while (1) {
            printf ("%d%s ROTOR: ", i, cardinals[i-1]);
            scanf ("%d", &rotorTop);
            if (rotorTop > 0 && rotorTop < 27) break;
            printf ("*ROTORS' NUMBERS ARE RESTRICTED BETWEEN 1 AND 26*\n");
        }
        fprintf (configure, "%s%d%s %s %d", "\n", i, cardinals[i-1], "ROTOR:", rotorTop);
    }
    printf ("\n(THE MODULE PROPORTION FOR ALL ROTORS IS 26)\n\n");
    fprintf (configure, "%s", "\n\n(THE MODULE PROPORTION FOR ALL ROTORS IS 26)\n\n");
    printf ("PLUGBOARD:\n\nEnter number of pairs of letters to be plugged:\n");
    scanf ("%d", &plugPairs);
    printf("For each of the following %d line(s), enter a pair of plugged letters separated by a blank space.\nI.e: 'A B':\n\n", plugPairs);
    fflush(stdin);
    for (int i = 0; i < plugPairs; ++i) {
        scanf ("%s %s", srcPlug[i], destPlug[i]);
    }
    fprintf(configure, "PLUGBOARD:\n");
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
        printf("\n\nDo you want to:\n\n1) Set configurations to default\n2) Reconfigure\n3) Display current configurations\n4) Exit\n\n");
        scanf ("%d", &ans);
        switch (ans) {
            case 1:
                set_to_default(configure);
                break;
            case 2:
                reconfigure(configure);
                break;
            case 3:
                display_configurations(configure);
                break;
            case 4:
                return 0;
            default:
                printf ("*Invalid option*\n");
                break;
        }
    }
}