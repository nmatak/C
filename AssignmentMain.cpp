//Nazif Matak G20853201

#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "CSpace.h";
#include "CSpace.cpp"; 

using namespace std;


//int Random()
//{
  //  return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 10.0f + 1);
//}


class CPlayer {
public:
    string name;
    int year = 1;
    int motivation;
    int success;
    int position;

    // Constructor
    CPlayer(const string& n, int m, int s, int p) : name(n), motivation(m), success(s), position(p) {}
};


void playGame(vector<CPlayer>& players, vector<CSpace*>& spaces) {
    cout << "Welcome to Scumbag College" << endl;
    // srand(static_cast<unsigned int> (time(0)));

    for (int round = 1; round <= 20; ++round) {
        cout << "Round " << round << endl;
        for (auto& player : players) {
            // Simulate player's turn and movement
            cout << player.name << "'s turn." << endl;
            int spinResult = 1 + rand() % 10;  // Simulating spinning the spinner
            cout << player.name << " spins " << spinResult << endl;
            // Calculate the new position of the player on the board
            int currentPosition = player.position;
            int newPosition = (currentPosition + spinResult) % spaces.size();
            player.position = newPosition; //updates the players position
            // Output the name of the space that the player landed on
            cout << player.name << " lands on " << spaces[newPosition]->name << endl;
            //cout << "New position for " << player.name << ": " << newPosition << endl;
            // Code for spinning the spinner and moving the player on the board

            // Check if the player completed a full circuit
            bool completedCircuit = newPosition < currentPosition;

            // Check if the player lands on or passes over the "Welcome Week" space during the second round or later
            if (spaces[newPosition]->name == "Welcome Week" || spaces[newPosition]->name == "Programming Task") {
                player.motivation += 250;
                player.year++;
                cout << player.name << " attends Welcome Week and starts year " << player.year << " more motivated!" << endl;
            }

            // Code for spinning the spinner and moving the player on the board
            player.position = newPosition;
        }


        //if (spaces[newPosition]->name == "Welcome Week" && (newPosition >= 0 || spaces[newPosition]->name=spaces[1,2,3])) {
        //    // Increase player's motivation by 250 and increment year
        //    player.motivation += 250;
        //    player.year++;
        //    cout << player.name << " attends Welcome Week and starts year " << player.year << " more motivated!" << endl;
        //}

        //// Code for spinning the spinner and moving the player on the board
        //player.position = newPosition; //updates the players position
    }

    cout << " -----------------------------------" << endl;
    cout << "Game Over" << endl;
    
}
// }



int main() {
    // Read in the spaces from degrees.txt
    //vector<CSpace*> spaces = readSpacesFromFile("degrees.txt");

    // Display the spaces (for testing)
    //for (const auto& space : spaces) {
      //  cout << "Type: " << space->type << ", Name: " << space->name << std::endl;
    //}

    // Create two players
    CPlayer vyvyan("Vyvyan", 1000, 0, 0);  // Starting at position 0
    CPlayer rick("Rick", 1000, 0, 0);      // Starting at position 0

    // Vector to store the players
    vector<CPlayer> players = { vyvyan, rick };
    vector<CSpace*> spaces = readSpacesFromFile("degrees.txt");

    // Simulate playing 20 rounds of the game
    playGame(players, spaces);

    // Clean up allocated memory
    for (auto& space : spaces) {
        delete space;
    }

    return 0;
}