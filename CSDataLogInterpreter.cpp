#include <iostream>
#include <string>

#include "Automaton.h"
#include "AutoList.h"
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
    CommaAutomaton myAuto;
    string value = "";
    int line = 0;
    Token myToken;
    
    cout << "Welcome to the testing site!" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Enter a value" << endl;
        getline(cin, value);
        cout << "Automaton.Read = " << myAuto.Read(value) << endl;
        myToken = myAuto.CreateToken(value, line);
        cout << "Token created: " << myToken.stringedToken() << endl;
        line++;
    }
    
}