/* Contains the functions for the ASCII pet simulator. Validates stats and holds
 * the functions to allow different actions with the pet, like eating, bathing,
 * etc. Also saves and loads save data from file 'savepet.txt'. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "pet.h"

/* Sets the type of pet for the ASCII pet. Allows users to chose either
 * a dog or cat and validates the input. */
void setType(struct Pet* pet) {
    int type;
    do {
        printf("Please choose a pet type. 1 for Dog, 2 for Cat: ");
        scanf("%d", &type);
        getchar(); // clear newline
        if (type == 1) {
            pet->type = DOG;
            return;
        }
        else if (type == 2) {
            pet->type = CAT;
            return;
        }
        printf("Invalid choice.\n");
    } while (type != 1 && type != 2);
}

/* Validate and let user select valid name of pet. */
void setName(struct Pet* pet) {
    char choice = 0;
    while (choice != 'Y' && choice != 'y') {
        printf("Enter pet name (max 10 characters): ");

        if (fgets(pet->name, 11, stdin) != NULL) {
            // remove trailing newline if present
            size_t len = strlen(pet->name);
            if (len > 0 && pet->name[len - 1] == '\n') {
                pet->name[len - 1] = '\0';
            } else {
                // flush extra input left in buffer if name > 10 chars
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
        }
        // check if input is empty or only whitespace
        int empty = 1;
        int i;
        for (i = 0; pet->name[i] != '\0'; i++) {
            if (!isspace(pet->name[i])) {
                empty = 0;
                break;
            }
        }

        if (empty) {
            printf("Name cannot be empty or just spaces.\n");
            continue;
        }

        // confirm name
        printf("Is \"%s\" okay? Y/N: ", pet->name);
        choice = getchar();

        // clear leftover chars from input buffer
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}//setName

/* Feed the pet and adjusts stats and portrait to display as needed. */
void feed(struct Pet* pet) {
    system("clear"); //clear console for displaying new portrait
    printf("Feeding %s...\n", pet->name);
    displayPortrait(pet, EAT);

    ++(pet->happiness);
    --(pet->hygiene);
    (pet->hunger) += 3;
    validateStats(pet);

    sleep(3);
    system("clear");
    printf("Yummy! %s enjoyed their meal.\n", pet->name);
    displayPortrait(pet, HAPPY);
    sleep(3);
}//feed

/* Lets pet sleep and adjusts stats and portrait to display as needed. */
void nap(struct Pet* pet) {
    system("clear"); //clear console for displaying new portrait
    printf("%s is sleeping...\n", pet->name);
    displayPortrait(pet, SLEEP);

    --(pet->hunger);
    pet->energy += 5;
    validateStats(pet);

    sleep(3);
    system("clear");
    printf("%s had a nice nap.\n", pet->name);
    displayPortrait(pet, HAPPY);
    sleep(3);
}//nap

/* Plays with the pet and adjusts stats and portrait to display as needed. */
void play(struct Pet* pet) {
    system("clear"); //clear console for displaying new portrait
    printf("Let's play!\n");
    displayPortrait(pet, PLAY);

    pet->happiness += 2;
    pet->hygiene -= 3;
    pet->hunger -= 2;
    pet->energy -= 3;
    validateStats(pet);

    sleep(3);
    system("clear");
    minigame(pet);
    system("clear");
    printf("%s enjoyed playing with you!\n", pet->name);
    displayPortrait(pet, HAPPY);
    sleep(3);
}//play

/* Bathes the pet and adjusts stats and portrait to display as needed. */
void bathe(struct Pet* pet) {
    system("clear"); //clear console for displaying new portrait
    printf("%s is splashing around...\n", pet->name);
    displayPortrait(pet, BATH);

    --(pet->happiness);
    pet->hygiene += 5;
    --(pet->energy);
    validateStats(pet);

    sleep(3);
    system("clear");
    printf("What a nice bath!\n");
    displayPortrait(pet, HAPPY);
    sleep(3);
}//bathe

/* Pets the pet and adjusts stats and portrait to display as needed. */
void pets(struct Pet* pet) {
    system("clear"); //clear console for displaying new portrait
    printf("<3 <3 <3 <3 <3 <3 <3 <3\n");
    displayPortrait(pet, HAPPY);

    ++(pet->happiness);
    validateStats(pet);

    sleep(2);
}//pets

/* Set portrait of pet and display proper portrait through select petPortrait. */
void displayPortrait(struct Pet* pet, enum petPortrait portrait) {
    pet->portrait = portrait; // set action to newest pet portrait
    if (pet->type == DOG) {
        switch (pet->portrait) {
        case IDLE: printDogIdle(); break;
        case HAPPY: printDogHappy(); break;
        case SAD: printDogSad(); break;
        case SLEEP: printDogSleep(); break;
        case EAT: printDogEat(); break;
        case PLAY: printDogPlay(); break;
        case BATH: printDogBath(); break;
        }
    }
    else if (pet->type == CAT) {
        switch (pet->portrait) {
        case IDLE: printCatIdle(); break;
        case HAPPY: printCatHappy(); break;
        case SAD: printCatSad(); break;
        case SLEEP: printCatSleep(); break;
        case EAT: printCatEat(); break;
        case PLAY: printCatPlay(); break;
        case BATH: printCatBath(); break;
        }
    }
}//displayPortrait

/* Select the proper mood portrait of SAD, IDLE, or HAPPY based on
 * the sum of pet stats.
 * To be used after a pet action to display status of pet to let user know
 * of pet's ailments, if any. */
void updateMoodPortrait(struct Pet* pet) {
    system("clear");
    tryIdleMessage();
    int stats[] = { pet->hunger, pet->happiness, pet->hygiene, pet->energy };
    const char* statNames[] = { "HUNGRY", "UNHAPPY", "DIRTY", "TIRED" };

    int lowThreshold = 3; // 1 - 3 = stats too low, pet unhappy
    int highThreshold = 8;

    // Finds number of stats in the stat array, flexible to add more later
    int numStats = sizeof(stats) / sizeof(stats[0]);
    int sum = 0;
    int lowCount = 0;

    printf("%s is: ", pet->name);

    // List low stats
    int i;
    for (i = 0; i < numStats; ++i) {
        sum += stats[i];
        if (stats[i] <= lowThreshold) {
            printf("%s ", statNames[i]);
            lowCount++;
        }
    }
    // No stats are too low, Pet is feeling OK
    if (lowCount == 0) {
        printf("OK");
    }
    printf("\n");

    // Pick appropraite portrait based on pet's stats
    if (lowCount >= 2) {
        displayPortrait(pet, SAD); //too many stats low, pet is SAD
    }
    else if (sum >= highThreshold * numStats) {
        displayPortrait(pet, HAPPY); //high stats, pet is HAPPY
    }
    else {
        //Pet has middle stats that are not too high or low
        displayPortrait(pet, IDLE);
    }
}//updateMoodPortrait

/* Validates stats and ensures they never exceed max of 10 or minimum of 0. */
void validateStats(struct Pet* pet) {
    if (pet->hunger < 0) pet->hunger = 0;
    if (pet->happiness < 0) pet->happiness = 0;
    if (pet->hygiene < 0) pet->hygiene = 0;
    if (pet->energy < 0) pet->energy = 0;

    if (pet->hunger > 10) pet->hunger = 10;
    if (pet->happiness > 10) pet->happiness = 10;
    if (pet->hygiene > 10) pet->hygiene = 10;
    if (pet->energy > 10) pet->energy = 10;
}//validateStats

/* Prints random idle message for pet liveliness based on 33% chance. */
void tryIdleMessage() {
    if (rand() % 3 == 0) { // about 33% chance
        // Random idle messages to print after actions
        const char* idleMessages[] = {
            "Your pet wiggles its tail.",
            "Your pet lets out a happy chirp.",
            "Your pet looks at you with big curious eyes.",
            "Your pet scratches behind its ear.",
            "Your pet seems restless and looks around.",
            "Your pet hums quietly.",
            "Your pet rolls over lazily.",
            "Your pet paces around a bit."
        };
        // size of random messages array
        const int idleMessageCount =
        sizeof(idleMessages) / sizeof(idleMessages[0]);

        int index = rand() % idleMessageCount;

        printf("%s\n", idleMessages[index]);
    }
}//showIdleMessage

/* Saves struct Pet data in binary file "savepet.dat".
 * Returns 0 if failed or 1 if success. */
int savePet(struct Pet* pet) {
    FILE* fp;
    if ((fp = fopen("savepet.dat", "wb")) == NULL) {
        perror("Save failed! :(");
        return 0; // saved data == false
    }
    fwrite(pet, sizeof(struct Pet), 1, fp);
    fclose(fp);
    return 1; // saved data == true
}//savePet

/* Loads struct Pet data. Returns 0 if failed or 1 if success. */
int loadPet(struct Pet* pet) {
    FILE* fp;
    if ((fp = fopen("savepet.dat", "rb")) == NULL) {
        return 0; // no save found
    }
    fread(pet, sizeof(struct Pet), 1, fp);
    fclose(fp);
    return 1;
}//loadPet
