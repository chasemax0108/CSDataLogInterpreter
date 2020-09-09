#include <iostream>
#include <string>

#include "Automaton.h"
#include "TestAutomaton.h"
#include "TokenType.h"
#include "Token.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int main()
{
    TestAutomaton myAuto;
    TokenType type = COMMA;
    string value = "";
    int line = 0;
    Token myToken(COMMA, "", 0);
    
    cout << "Welcome to the testing site!" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Enter a value" << endl;
        getline(cin, value);
        myToken.setType(type);
        myToken.setValue(value);
        myToken.setLine(line);
        line++;
        cout << "Here's your token: " << myToken.stringedToken() << endl;
        /*
        if (myAuto.Read(input) == 0) {
            cout << "That doesn't match the auto!" << endl;
        }
        else {
            cout << "Good job! You've figured it out!" << endl;
        }
        */
    }
    
}