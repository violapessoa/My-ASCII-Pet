/* Main file for execution of MyASCII Pet program. Contains menuing
* and validation of user input to interact with pet. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "pet.h"

int main() {
    srand(time(NULL)); //seeding for random idle messages

    openingArt();
    sleep(1);

    // LOAD SAVE DATA, if it exists
    int input = 0;
    struct Pet pet;

    printf("Checking for saved pet...\n");

    if (loadPet(&pet)) {
        printf("Save file found! Welcome back, %s!\n", pet.name);
        sleep(2);
    }
    else {
        printf("No save data found. Creating a new pet.\n");
        sleep(2);

        struct Pet newPet = { "", 0, 0, 5, 5, 5, 5 };
        pet = newPet;

        printf("Welcome to MY ASCII Pet!\n");
        setType(&pet);
        setName(&pet);
    }

    // MAIN INPUT LOOP
    while (input != 6) {
        updateMoodPortrait(&pet);

        char buffer[32]; // for handling non-integer input
        printf("What would you like to do?\n1. Feed\n2. Play\n"
            "3. Sleep\n4. Bathe\n5. Pet\n6. Quit\n");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            continue; // handles any EOF cases

        if (sscanf(buffer, "%d", &input) != 1) {
            printf("Invalid input. Please enter a number 1-6.\n");
            sleep(2);
            continue;
        }

        switch (input) {
        case 1: feed(&pet); break;
        case 2: play(&pet); break;
        case 3: nap(&pet); break;
        case 4: bathe(&pet); break;
        case 5: pets(&pet); break;
        case 6: break;
        default:
            printf("Invalid input. Please enter a number 1-6.\n");
            sleep(2);
        }
    }

    printf("Saving your pet...\n");
    savePet(&pet);
    sleep(1);
    printf("See you soon, %s!\n", pet.name);
    sleep(1);
    return 0;
}
