#include <iostream>
#include <string>
#include <fstream>

#include "Automaton.h"
#include "AutoList.h"
#include "TokenType.h"
#include "Token.h"

using namespace std;

int main()
{
    ifstream inFile("input.txt");
    LineCommentAutomaton myAuto;
    string value = "";
    int line = 0;
    Token myToken;
    
    cout << "Welcome to the testing site!" << endl;
    /*while (inFile) {
        getline(inFile, value);
        cout << "Automaton.Read = " << myAuto.Read(value) << endl;
        if (myAuto.Read(value) != 0) {
            myToken = myAuto.CreateToken(value, line);
            cout << "Token created: " << myToken.stringedToken() << endl;
        }
        line++;
    }*/
    
    while (inFile) {
        if (!inFile.eof()) {
            string temp;
            getline(inFile, temp);
            value += temp + '\n'; // Add newline char because getline takes it off
        }
        else break;
    }
    cout << "Automaton.Read = " << myAuto.Read(value) << endl;
    if (myAuto.Read(value) != 0) {
        myToken = myAuto.CreateToken(value, line);
        cout << "Token created: " << myToken.stringedToken() << endl;
    }

    return 0;
    
}