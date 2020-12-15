#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <cctype>
#include <cmath>
#include <set>

using namespace std;

// Methods and threads
void introduction();
void loadDicts();
void game();
bool isHigherWord(string input);
bool isLowerWord(string input);
bool isVictoryWord(string input);
string to_lower(string input);

// Variables and word sets
string username;
const int BASE_GUESS = 50;
set<string> higherWords;
set<string> lowerWords;
set<string> victoryWords;

int main()
{
    thread loading(introduction);
    thread dictionaries(loadDicts);
    loading.join();
    dictionaries.join();
    game();
    return 0;
}

void introduction() {
    cout << "Hi there!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "My name is Program! What's yours?" << endl;
    cin >> username;
    cout << "Hi, " << username << "! Why don't we play a guessing game?" << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Think of a number between 1 and 100, and then I'll try to guess what it is!" << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "When I guess a number, you tell me if the number you are thinking of is higher or lower than my guess, or if my guess was correct." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Ready? Let's go!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
}

void loadDicts() {
    ifstream higherFile ("higherwords.txt", ifstream::in);
    ifstream lowerFile ("lowerwords.txt", ifstream::in);
    ifstream victoryFile ("victorywords.txt", ifstream::in);
    string currentLine;
    if (higherFile.is_open()) {
        while (getline(higherFile, currentLine)) {
            higherWords.insert(currentLine);
        }
    } else {
        cerr << "WARNING: \"higherwords.txt\" was not found.  The only word to indicate that your number is higher than the program's guess is \"higher\"" << endl;
        higherWords.insert("higher");
    }
    higherFile.close();
    if (lowerFile.is_open()) {
        while (getline(lowerFile, currentLine)) {
            lowerWords.insert(currentLine);
        }
    } else {
        cerr << "WARNING: \"lowerwords.txt\" was not found.  The only word to indicate that your number is lower than the program's guess is \"lower\"" << endl;
        lowerWords.insert("lower");
    }
    lowerFile.close();
    if (victoryFile.is_open()) {
        while (getline(victoryFile, currentLine)) {
            victoryWords.insert(currentLine);
        }
    } else {
        cerr << "WARNING: \"victorywords.rxt\" was not found.  The only word to indicate that the program guess your number is \"correct\"" << endl;
        victoryWords.insert("correct");
    }
    victoryFile.close();
}

void game() {
    string answer = "";
    int addOrSubtract; // The number to add or subtract from the current guess, if the current guess is incorrect
    int counter = 1; // How many turns there have been so far
    int currentGuess = BASE_GUESS;
    while (!isVictoryWord(to_lower(answer))) {
        cout << "Is the number you are thinking of " << currentGuess << "? ";
        cin >> answer;
        addOrSubtract = BASE_GUESS / pow(2, counter);
        if (addOrSubtract == 0)
            addOrSubtract = 1;
        if (isHigherWord(to_lower(answer))) {
            currentGuess = currentGuess + addOrSubtract;
            counter += 1;
        } else if (isLowerWord(to_lower(answer))) {
            currentGuess = currentGuess - addOrSubtract;
            counter += 1;
        } else if (!isVictoryWord(to_lower(answer))) {
            cout << "I'm sorry, I didn't understand. Please tell me if the number you are thinking of is higher or lower than my guess, or if my guess is correct." << endl;
        }
    }
    cout << "I see! The answer was " << currentGuess << ". What fun!" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Would you like to play again? ";
    cin >> answer;
    if (answer[0] == 'y')
        game();
}

bool isHigherWord(string input) {
    return higherWords.find(input) != higherWords.end();
}

bool isLowerWord(string input) {
    return lowerWords.find(input) != lowerWords.end();
}

bool isVictoryWord(string input) {
    return victoryWords.find(input) != victoryWords.end();
}

string to_lower(string input) {
    string output = "";
    for (uint i = 0; i < input.length(); i++) {
        output += tolower(input[i]);
    }
    return output;
}
