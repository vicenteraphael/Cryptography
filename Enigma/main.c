#include <stdio.h>
#include <stdlib.h>
#include "variables.c"

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