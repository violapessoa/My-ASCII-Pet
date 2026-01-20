/* Header file for MyASCIIPet program containing enums and struct for the
* pet simulation. Also contains function prototypes for the struct Pet,
* the minigame for the pet's playing function, and the pet art printers. */

#ifndef PET_H
#define PET_H

// Portrait to dsiplay and of what type
enum petPortrait { IDLE, HAPPY, SAD, SLEEP, EAT, PLAY, BATH };
enum petType { CAT, DOG };

struct Pet {
    char name[11];
    enum petType type;
    enum petPortrait portrait;
    int hunger;
    int happiness;
    int hygiene;
    int energy;
};

/* Validates and changes elements of struct Pet. */
void setType(struct Pet* pet);
void setName(struct Pet* pet);
void displayPortrait(struct Pet* pet, enum petPortrait portrait);
void feed(struct Pet* pet);
void nap(struct Pet* pet);
void play(struct Pet* pet);
void bathe(struct Pet* pet);
void pets(struct Pet* pet);
void validateStats(struct Pet* pet);
void updateMoodPortrait(struct Pet* pet);
void tryIdleMessage(void);

/* Save and load struct Pet data from "savepet.dat" */
int loadPet(struct Pet* pet);
int savePet(struct Pet* pet);

// Starts minigame used in play function for pet located in rps.c
void minigame(struct Pet* pet);

/* Print ASCII portraits for pet's current mood or action. */
void openingArt(void);

// DOG
void printDogIdle(void);
void printDogHappy(void);
void printDogSad(void);
void printDogSleep(void);
void printDogEat(void);
void printDogPlay(void);
void printDogBath(void);

// CAT
void printCatIdle(void);
void printCatHappy(void);
void printCatSad(void);
void printCatSleep(void);
void printCatEat(void);
void printCatPlay(void);
void printCatBath(void);

#endif //PET_H
