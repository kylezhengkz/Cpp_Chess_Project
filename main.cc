#include "board.h"
#include "textdisplay.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "startposition.h"
#include "usermover.h"
#include <stdexcept>
#include "computer.h"
#include "cpu.h"
#include "captureevaluator.h"
#include "checkmatefinder.h"
#include "checkmateexception.h"
#include "stalemateexception.h"
class MoveList;

int main() {
    Board* currentPosition = new Board();
    TextDisplay* textDisplay = new TextDisplay(currentPosition);
    currentPosition->attach(textDisplay);
    // game [human OR computer[1-4]] [human OR computer[1-4]]
    // resign
    // move [square name] [square name]
    // setup
    //      + [piece initial] [square name]
    //      - [square name]
    //      = colour
    // done

    int colourTurn = WHITE; // white's turn by default (unless otherwise specified in setup)
    int turn[] = {HUMAN, HUMAN}; // user versus user by default
    int score[] = {0, 0};
    int turnTracker = 0;
    Computer* computer1;
    Computer* computer2;
    vector<Computer*> computers;
    computers.emplace_back(nullptr);
    computers.emplace_back(nullptr);
    // Computer* computer = new CPU(&currentPosition, &colourTurn);
    // computer = new CaptureEvaluator(computer);
    
    bool gameInProgress = false;
    while (true) {
        if (gameInProgress && turn[turnTracker] == COMPUTER) {
            cout << "Computer's turn..." << endl;
            try {
                computers[turnTracker]->selectBestMove();
                (*currentPosition).notifyObservers();
                cout << textDisplay;
                if (turnTracker == 1) {
                    turnTracker = 0;
                } else {
                    turnTracker++;
                }
                colourTurn = -colourTurn;
                continue;
            } catch (exception& e) { // checkmate or stalemate
                cout << e.what() << endl;
                cout << "Deleting computers" << endl;
                cout << "Please use setup/default command to start a new game" << endl;
                gameInProgress = false;
                delete computers[0];
                delete computers[1];
                turn[0] = HUMAN;
                turn[1] = HUMAN;
                delete currentPosition;
                textDisplay = nullptr;
                currentPosition = new Board();
                textDisplay = new TextDisplay(currentPosition);
                currentPosition->attach(textDisplay);
                if (turnTracker == 1) {
                    turnTracker = 0;
                } else {
                    turnTracker++;
                }
                score[turnTracker]++;
                cout << "Current Score:" << endl; 
                cout << "White: " << score[0] << endl; 
                cout << "Black: " << score[1] << endl;
                colourTurn = WHITE;
            }
        }

        if (gameInProgress) {
            Board copy = *currentPosition;
            Computer* checkmateChecker = new CPU(&copy, &colourTurn);
            try {
                checkmateChecker->selectBestMove();
            } catch (CheckmateException& e) {
                cout << e.what() << endl;
                gameInProgress = false;
                delete computers[0];
                delete computers[1];
                turn[0] = HUMAN;
                turn[1] = HUMAN;
                delete checkmateChecker;
                textDisplay = nullptr;
                currentPosition = new Board();
                textDisplay = new TextDisplay(currentPosition);
                currentPosition->attach(textDisplay);
                if (turnTracker == 1) {
                    turnTracker = 0;
                } else {
                    turnTracker++;
                }
                score[turnTracker]++;
                cout << "Current Score:" << endl; 
                cout << "White: " << score[0] << endl; 
                cout << "Black: " << score[1] << endl;
                colourTurn = WHITE;
            } catch(StalemateException& e) {
                cout << e.what() << endl;
                gameInProgress = false;
                delete computers[0];
                delete computers[1];
                turn[0] = HUMAN;
                turn[1] = HUMAN;
                delete checkmateChecker;
                textDisplay = nullptr;
                currentPosition = new Board();
                textDisplay = new TextDisplay(currentPosition);
                currentPosition->attach(textDisplay);
                cout << "Current Score (no change):" << endl; 
                cout << "White: " << score[0] << endl; 
                cout << "Black: " << score[1] << endl;
                colourTurn = WHITE;
            }
        }

        string line;
        if (!getline(cin, line)) {
            break;
        }
        istringstream iss(line);

        string cmd;
        if (!(iss >> cmd)) {
            cout << "No input received" << endl;
            continue;
        } else if (cmd == "game" || cmd == "Game" || cmd == "GAME") {
            string turn1str;
            int turn1;
            if (!(iss >> turn1str)) {
                cout << "Expected user or computer input, but didn't receive one" << endl;
                continue;
            } else if (turn1str == "human" || turn1str == "Human" || turn1str == "HUMAN") {
                turn1 = HUMAN;
            } else if (turn1str.substr(0, 8) == "computer" || turn1str.substr(0, 8) == "Computer" || turn1str.substr(0, 8) == "COMPUTER") {
                if (turn1str.substr(8) == "[1]") {
                    computer1 = new CPU(currentPosition, &colourTurn);
                    computers[0] = computer1;
                    turn1 = COMPUTER;
                } else if (turn1str.substr(8) == "[2]") {
                    computer1 = new CPU(currentPosition, &colourTurn);
                    computer1 = new CaptureEvaluator(computer1);
                    computers[0] = computer1;
                    turn1 = COMPUTER;
                } else if (turn1str.substr(8) == "[3]") {
                    computer1 = new CPU(currentPosition, &colourTurn);
                    computer1 = new CaptureEvaluator(computer1);
                    computer1 = new CheckmateFinder(computer1);
                    computers[0] = computer1;
                    turn1 = COMPUTER;
                } else if (turn1str.substr(8) == "[4]") {
                    
                } else {
                    cout << "Invalid level" << endl;
                    continue;
                }
            } else {
                cout << "Invalid input" << endl;
                continue;
            }

            string turn2str;
            int turn2;
            if (!(iss >> turn2str)) {
                cout << "Expected user or computer input, but didn't receive one" << endl;
                continue;
            } else if (turn2str == "human" || turn2str == "Human" || turn2str == "HUMAN") {
                turn2 = HUMAN;
            } else if (turn2str.substr(0, 8) == "computer" || turn2str.substr(0, 8) == "Computer" || turn2str.substr(0, 8) == "COMPUTER") {
                if (turn2str.substr(8) == "[1]") {
                    computer2 = new CPU(currentPosition, &colourTurn);
                    computers[1] = computer2;
                    turn2 = COMPUTER;
                } else if (turn2str.substr(8) == "[2]") {
                    computer2 = new CPU(currentPosition, &colourTurn);
                    computer2 = new CaptureEvaluator(computer2);
                    computers[1] = computer2;
                    turn2 = COMPUTER;
                } else if (turn2str.substr(8) == "[3]") {
                    computer2 = new CPU(currentPosition, &colourTurn);
                    computer2 = new CaptureEvaluator(computer2);
                    computer2 = new CheckmateFinder(computer2);
                    computers[1] = computer2;
                    turn2 = COMPUTER;
                } else if (turn2str.substr(8) == "[4]") {
                    
                } else {
                    cout << "Invalid level" << endl;
                    continue;
                }
            } else {
                cout << "Invalid input" << endl;
                continue;
            }

            turn[0] = turn1;
            turn[1] = turn2;
            gameInProgress = true;
        } else if (cmd == "move" || cmd == "MOVE" || cmd == "Move") {
            string squareOne;
            if (!(iss >> squareOne)) {
                cout << "Expected a square input, but didn't receive one" << endl;
                continue;
            }
            string squareTwo;
            if (!(iss >> squareTwo)) {
                cout << "Expected two square inputs, but only received one" << endl;
                continue;
            }

            try {
                UserMover::moveUser((*currentPosition), cin, squareOne, squareTwo, colourTurn);
                (*currentPosition).notifyObservers();
                cout << textDisplay;
                if (turnTracker == 1) {
                    turnTracker = 0;
                } else {
                    turnTracker++;
                }
                colourTurn = -colourTurn;
            } catch (exception& e) {
                cout << e.what() << endl;
            }
        } else if (cmd == "setup" || cmd == "SETUP" || cmd == "Setup") {
            try {
                StartPosition::setup(cin, currentPosition, cout, textDisplay, colourTurn);
                if (colourTurn == WHITE) {
                    turnTracker = 0;
                } else {
                    turnTracker = 1;
                }
            } catch (exception& e) {
                cout << e.what() << endl;
                cout << "Setup cancedlled" << endl;
                (*currentPosition).reNullify();
            }
        } else if (cmd == "default" || cmd == "DEFAULT" || cmd == "Default") {
            StartPosition::defaultStartingPosition(currentPosition);
            // update text and graphical display
            (*currentPosition).notifyObservers();
            cout << textDisplay;
        } else if (cmd == "resign") {
            gameInProgress = false;
            delete computers[0];
            delete computers[1];
            turn[0] = HUMAN;
            turn[1] = HUMAN;
            textDisplay = nullptr;
            currentPosition = new Board();
            textDisplay = new TextDisplay(currentPosition);
            currentPosition->attach(textDisplay);
            if (turnTracker == 1) {
                turnTracker = 0;
            } else {
                turnTracker++;
            }
            score[turnTracker]++;
            cout << "Current Score:" << endl; 
            cout << "White: " << score[0] << endl; 
            cout << "Black: " << score[1] << endl;
            colourTurn = WHITE;
        } else {
            cout << "Invalid command" << endl;
        }
    }
    cout << "Final Score:" << endl; 
    cout << "White: " << score[0] << endl; 
    cout << "Black: " << score[1] << endl;
    colourTurn = WHITE;
}

