# MyASCII Pet 🐾

A console-based ASCII pet simulation written in C. Care for a virtual pet by feeding, playing, bathing, and resting. Includes a **Rock, Paper, Scissors, Lizard, Spock** minigame to boost (or risk!) your pet’s happiness.

---

## Features

* Interactive, menu-driven console interface with input validation
* Multiple pet types: **Dog** or **Cat**, each with ASCII portraits for actions and moods
* Dynamic pet stats: **Hunger, Happiness, Hygiene, Energy**
* Persistent data: save and load pet state using a binary file
* Minigame integration for extra engagement
* Clear, informative feedback for invalid inputs and game actions

---

## Technologies

* **Language:** C
* **Tools:** GCC, Make, Linux terminal

---

## Getting Started

### Prerequisites

* GCC compiler (Linux or Windows with MinGW)
* Terminal / command-line interface

---

## Build and Run

Clone the repository:

```bash
git clone https://github.com/violapessoa/My-ASCII-Pet.git
cd My-ASCII-Pet
```

Build the project:

```bash
make
```

Run the program:

```bash
./bin/myasciipet
```

Clean up compiled files:

```bash
make clean
```

---

## Notes

* The executable is created in the `bin/` directory by the Makefile.
* If you encounter linker errors, ensure all source files (e.g., ASCII art files) are included in the Makefile.

---

Enjoy taking care of your ASCII companion! 🐶🐱
