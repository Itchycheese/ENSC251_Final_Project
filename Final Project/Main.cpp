#include "parserClasses.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int programMain() {
	ifstream sourceFile;
	TokenList tokens;

  //Lists for types of tokens
  TokenList operatorTokens;
  TokenList identifierTokens;
  TokenList literalTokens;
  TokenList commentBodyTokens;
  TokenList otherTokens;

	Tokenizer tokenizer;


	bool verboseModeFlag = false;
	string userInput;
	char parsedUserInput;


	//Read in a file line-by-line and tokenize each line

	cout << "Enter the name of the file to open: ";
	cin >> userInput;

	sourceFile.open(userInput);
	if (!sourceFile.is_open()) {
		cout << "Failed to open file" << endl;
		return 1;
	}

	while(!sourceFile.eof()) {
		string line;
		getline(sourceFile, line);

		tokenizer.setString(&line);
		while(!tokenizer.isComplete()) {
			tokens.append(tokenizer.getNextToken());
		}
	}
    ///removeComments(tokens); ///test remove comment

	cout << "Enter Verbose Mode? Type \"1\" for Yes, Other inputs will be a No. : ";
	cin >> userInput;

    parsedUserInput = userInput[0];

	if (parsedUserInput == '1')
    {
        verboseModeFlag = true;
    }

  /* For your testing purposes only */
    ///test remove token type
    ///removeTokensOfType(tokens, T_Operator);
  /* Ensure that tokens have all type information set*/

  /* Create operator,identifier,literal, etc. tokenLists from the master list of tokens */


	return 0;
}
