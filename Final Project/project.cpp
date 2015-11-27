//Use only the following three libraries:
#include "parserClasses.h"
#include <iostream>
#include <fstream>

using namespace std;

//Example Test code for interacting with your Token, TokenList, and Tokenizer classes
//Add your own code to further test the operation of your Token, TokenList, and Tokenizer classes
int xmain() {
	ifstream sourceFile;
	TokenList tokens;

  //Lists for types of tokens
  TokenList operatorTokens;
  TokenList identifierTokens;
  TokenList literalTokens;
  TokenList commentBodyTokens;
  TokenList otherTokens;

	Tokenizer tokenizer;

	//Read in a file line-by-line and tokenize each line
	sourceFile.open("andgate.vhd");
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

	/*Test your tokenization of the file by traversing the tokens list and printing out the tokens*/
	tokenDetails detailtoken;

	Token *t = tokens.getFirst();
	while(t)
	{
	    tokens.findAndSetTokenDetails(t); ///test findAndSetTokenDetails
        if(t->getTokenType() == 1 || t->getTokenType() == 2)
        {
           detailtoken = *(t->getTokenDetails());
           //cout << t->getStringRep() << " Token Type: " << t->getTokenType() <<" Token Detail: " << detailtoken.type << " Token Width: " << detailtoken.width <<endl;
            t = t->getNext();
        }
        else
        {
            //cout << t->getStringRep() << " Token Type: " << t->getTokenType() <<endl;
		t = t->getNext();
        }

	}

  /* For your testing purposes only */
    ///test remove token type
    ///removeTokensOfType(tokens, T_Operator);
  /* Ensure that tokens have all type information set*/
    t = tokens.getFirst();
    while(t)
	{
        if(t->getTokenType() == 1 || t->getTokenType() == 2)
        {
           detailtoken = *(t->getTokenDetails());
           cout << t->getStringRep() << " Token Type: " << t->getTokenType() <<" Token Detail: " << detailtoken.type << " Token Width: " << detailtoken.width <<endl;
            t = t->getNext();
        }
        else
        {
            cout << t->getStringRep() << " Token Type: " << t->getTokenType() <<endl;
		t = t->getNext();
        }

	}
  /* Create operator,identifier,literal, etc. tokenLists from the master list of tokens */


	return 0;
}
