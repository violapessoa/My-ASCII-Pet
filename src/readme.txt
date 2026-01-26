This program is a simple virutal pet simulator. The user creates a pet,
gives it a name, and interacts with it by feeding, playing, bathing, sleeping,
and petting it. The pet has stats such as hunger, happiness, hygiene and
energy which change based on the actions the player chooses. The game also
displays different ASCII art depending on the pet's mood and type. A minigame is
available when playing with the pet, and it can also display random idle
messages at times.

The program automatically loads a saved pet from "savepet.dat" when it
starts (if the data exists), and it saves the pet again when the user chooses to
quit the program.

The program contains a simple Makefile to compile all object files
together. All that is needed it to enter 'make' in the shell, and then
to run './bin/myasciipet'. Nothing further is required. The save will load
itself.
If you do not wish to load from a save again, simply delete 'savepet.dat'
which contains the save data of the pet struct.

Challenges included input handling, keeping ASCII art formatted correctly,
implementing the save/load system for the pet, and balancing the pet's
stats.

Input handling required some external online research as I did not want
the user to be able to overload non-integer input in the menu or put a pet
name of over 10 chars.
The ASCII art took a bit of debugging because of its backslashes. They
needed double backslashes to make sure they didn't become escape sequences.
The save/load system was tricky because I initially wanted it to be a .txt
file. I realized that if users were not going to be editting this file
that there was no reason to make it a .txt or humnan-readable. I opted instead
for binary write and reads into a .dat file.
Balancing the pet's stats took quite a long time to figure out.
After many trials, I decided I did not want floating point numbers as this
made it far too complex, and I stuck with low ints 0 - 10 to keep it
manageable for such a simple program. The stats are all adjusted
differently depending on the pet action, and this, too, was just trial and error to
try and keep things fair. The pet starts with all 5s for stats because there
islittle incentive to play if the pet is already happy and well cared for,
but would also be overwhelming and annoying to start off with all low
stats.

