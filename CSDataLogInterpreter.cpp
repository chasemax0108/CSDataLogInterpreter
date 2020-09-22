#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Automaton.h"
#include "AutoList.h"
#include "TokenType.h"
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[])
{   
    if (argc < 2) {
        cout << "Error: no input file specified" << endl;
    }
    else {

        // Variables
        ifstream inFile(argv[1]);
        string input = "";
        vector<Automaton*> allFSA;
        vector<Token> tokens;

        // Setup all Finite State Automata and add them to a collection of Automata
        // (define the rules of the lexer)
        SSAutomaton CommaAuto(COMMA);
        allFSA.push_back(&CommaAuto);
        SSAutomaton PeriodAuto(PERIOD);
        allFSA.push_back(&PeriodAuto);
        SSAutomaton QMarkAuto(Q_MARK);
        allFSA.push_back(&QMarkAuto);
        SSAutomaton LPAuto(LEFT_PAREN);
        allFSA.push_back(&LPAuto);
        SSAutomaton RPAuto(RIGHT_PAREN);
        allFSA.push_back(&RPAuto);
        SSAutomaton ColonAuto(COLON);
        allFSA.push_back(&ColonAuto);
        SSAutomaton MultAuto(MULTIPLY);
        allFSA.push_back(&MultAuto);
        SSAutomaton AddAuto(ADD);
        allFSA.push_back(&AddAuto);

        MSAutomaton ColonDashAuto(COLON_DASH);
        allFSA.push_back(&ColonDashAuto);
        MSAutomaton SchemesAuto(SCHEMES);
        allFSA.push_back(&SchemesAuto);
        MSAutomaton FactsAuto(FACTS);
        allFSA.push_back(&FactsAuto);
        MSAutomaton RulesAuto(RULES);
        allFSA.push_back(&RulesAuto);
        MSAutomaton QueriesAuto(QUERIES);
        allFSA.push_back(&QueriesAuto);

        BlockCommentAutomaton BCAuto;
        allFSA.push_back(&BCAuto);
        LineCommentAutomaton LCAuto;
        allFSA.push_back(&LCAuto);
        StringAutomaton StringAuto;
        allFSA.push_back(&StringAuto);
        IDAutomaton IDAuto;
        allFSA.push_back(&IDAuto);
        ErrorAutomaton EAuto;
        allFSA.push_back(&EAuto);


        //Read and process the input file
        while (inFile) {
            if (!inFile.eof()) {
                string temp;
                getline(inFile, temp);
                input += temp + '\n'; // Add newline char because getline takes it off
            }
            else break;
        }
        input = input.substr(0, input.length() - 1); // Take off the last newline char

        //Run the lexer
        Lexer myLexer(allFSA);
        tokens = myLexer.Run(input);

        // Clean out the comments
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i].getType() == COMMENT) {
                tokens.erase(tokens.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < tokens.size(); i++) {
            cout << tokens[i].stringedToken() << endl;
        }

        //Run the parser
        try {
            Parser myParser;
            myParser.Parse(tokens);
            cout << "Parsing Successful!" << endl;
        }
        catch (Token errorToken) {
            cout << "Failure!" << endl;
            cout << "  " << errorToken.stringedToken() << endl;
        }
        

        //Output
       
    }
    return 0;
}