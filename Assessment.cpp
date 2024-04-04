#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib> // For rand()
#include <ctime> // For time()
using namespace std;

class Player; // Forward declaration of Player

class Space {
public:
    virtual void onLand(Player& player) = 0;
};

class Assessment : public Space {
public:
    Assessment(string name, int motivationalCost, int achievementScore)
        : name(name), motivationalCost(motivationalCost), achievementScore(achievementScore), completed(false) {}

    void onLand(Player& player) override;

    bool isCompleted() const { return completed; }
    void setCompleted(bool c) { completed = c; }

    int getMotivationalCost() const { return motivationalCost; }
    int getAchievementScore() const { return achievementScore; }

private:
    string name;
    int motivationalCost;
    int achievementScore;
    bool completed;
};

class Player {
public:
    Player(string name) : name(name), motivation(100), success(0) {}

    void landOn(Space& space) {
        space.onLand(*this);
    }

    void completeAssessment(Assessment& assessment) {
        motivation -= assessment.getMotivationalCost();
        addSuccess(assessment.getAchievementScore());
        assessment.setCompleted(true);
    }

    void addSuccess(int amount) {
        success += amount;
    }

    void endTurn() {
        cout << name << "'s motivation is " << motivation << " and success is " << success << endl;
    }

    string getName() const { return name; }
    int getMotivation() const { return motivation; }
    int getSuccess() const { return success; }

private:
    string name;
    int motivation;
    int success;
};

void Assessment::onLand(Player& player) {
    if (!isCompleted()) {
        if (player.getMotivation() >= getMotivationalCost()) {
            player.completeAssessment(*this);
            cout << player.getName() << " completes " << name << " for " << getMotivationalCost() << " and achieves " << getAchievementScore() << endl;
        }
    } else {
        int halfScore = getAchievementScore() / 2;
        player.addSuccess(halfScore / 2);
        cout << player.getName() << " helps and achieves " << halfScore << endl;
    }
}

int main() {
    vector<Space*> spaces;
    map<string, Player*> players;

    // Initialize random seed
    srand(time(0));

    // Read from degrees.txt and create spaces
    ifstream file("degrees.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        char type;
        iss >> type;
        if (type == '1') {
            string name;
            int motivationalCost, achievementScore;
            iss >> name >> motivationalCost >> achievementScore;
            spaces.push_back(new Assessment(name, motivationalCost, achievementScore));
        }
    }
    file.close();

    // Create players
    players["Player1"] = new Player("Player1");
    players["Player2"] = new Player("Player2");

    // Game loop
    for (int turn = 0; turn < 10; ++turn) { // Simplified: 10 turns
        for (auto& playerPair : players) {
            Player& player = *playerPair.second;
            // Simplified: Player lands on a random space
            int spaceIndex = rand() % spaces.size();
            Space& space = *spaces[spaceIndex];
            player.landOn(space);
            player.endTurn();
        }
    }

    // Determine the winner
    Player* winner = nullptr;
    for (auto& playerPair : players) {
        if (!winner || playerPair.second->getSuccess() > winner->getSuccess()) {
            winner = playerPair.second;
        }
    }

    cout << "Game Over" << endl;
    for (auto& playerPair : players) {
        cout << playerPair.first << " has achieved " << playerPair.second->getSuccess() << endl;
    }
    cout << winner->getName() << " wins." << endl;

    // Cleanup
    for (Space* space : spaces) {
        delete space;
    }
    for (auto& playerPair : players) {
        delete playerPair.second;
    }

    return 0;
}
