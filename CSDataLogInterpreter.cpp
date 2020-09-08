#include <iostream>

#include "Automaton.h"
#include "TestAutomaton.h"

using namespace std;

int main()
{
    TestAutomaton myAuto;
    string input = "";
    
    cout << "Welcome to the testing site!" << endl;
    while (input.compare("exit") != 0) {
        cout << "Enter a string!" << endl;
        cin >> input;
        if (myAuto.Read(input) == 0) {
            cout << "That doesn't match the auto!" << endl;
        }
        else {
            cout << "Good job! You've figured it out!" << endl;
        }
    }
    
}