# Treasure-Hunt-Game
It is a C++ program that implements a simple game called "Treasure in a Haunted House." The game consists of navigating through different maps by moving the player's character using the arrow keys. Here's a breakdown of the program's structure and main components:

Class Stack<T>: A template class that represents a stack data structure used to store the player's movement path. It has a nested Node class, which represents a node in the stack.

Function prototypes:

LoadTitle(): Displays the game title and waits for any key press to start the game.
LoadMenu(): Displays the main menu options.
LoadMap(): Loads the maps from external text files.
StartGame(): Implements the game logic, allowing the player to navigate through the maps.
Devil_Room(): Handles the Devil Room event in the game.
Treasure_Room(): Handles the Treasure Room event in the game.
Show_Result(): Displays the game result.
Show_Paths(): Displays the movement paths taken by the player.
LoadRules(): Displays the game rules.
Options(): Displays the game options.
main() function: The program's entry point. It starts by calling LoadTitle() to display the game title and waits for a key press to proceed. Then it sets up the maps and initializes the stack objects. It enters a loop that displays the menu options, accepts user input, and executes the corresponding functionality based on the selected option.
