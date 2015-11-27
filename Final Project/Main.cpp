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

	vector<string> errorLines;
	string errorMissingEndIf = "Missing \"End If\" here: ";
	string errorMissingThen = "Missing \"Then\" here: ";
	string errorMissingIf = "Extra \"End If\" Here: ";
	string errorTypeMismatch = "Type Mismatch of types : ";
	string errorWidthMismatch = "Width Mismatch of Width: ";
	int numberOfTokens =0;
	int numberOfCondExp =0;
	int numberOfMissingEndIfs = 0;
	int numberOfMissingIfs =0;
	int numberofMissingThens =0;
	int ifEndifBalance =0; //if there is a positive number there are too many ifs, negative number too many endifs.
	int ifwhenBalance =0; //Like above except with When.


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

    //This part counts the number of tokens.
    Token *t = tokens.getFirst();
	while(t)
	{
	    numberOfTokens++;
		t = t->getNext();
	}

	//This part counts the number of conditional expressions.
	TokenList *conditionalTokenList = findAllConditionalExpressions(tokens);
	Token *condtokens = conditionalTokenList->getFirst();
    while(condtokens)
	{
	    if(condtokens->getStringRep() == "\\n")
        {
            numberOfCondExp++;
        }
		condtokens = condtokens->getNext();
	}

	//This part counts the number of ifs, end ifs.
	t = tokens.getFirst();
	Token *tError = tokens.getFirst();
	string errorCodeLine[7] = {" ", " ", " ", " ", " ", " ", " "};
	while(t)
	{
	    if(t->getStringRep() == "if")
        {
            ifEndifBalance++;
            if(ifEndifBalance>0)
            {
                { // this part gets the tokens around the error.
                errorCodeLine[3] = t->getStringRep();
                if(t->getPrev()!=nullptr)
                {
                    tError = t->getPrev();
                    errorCodeLine[2] = tError->getStringRep();
                }
                if(tError->getPrev()!=nullptr)
                {
                    tError = tError->getPrev();
                    errorCodeLine[1] = tError->getStringRep();
                }
                if(tError->getPrev()!=nullptr)
                {
                    tError = tError->getPrev();
                    errorCodeLine[0] = tError->getStringRep();
                }
                if(t->getNext()!=nullptr)
                {
                    tError = t->getNext();
                    errorCodeLine[4] = tError->getStringRep();
                }
                if(tError->getNext()!=nullptr)
                {
                    tError = tError->getNext();
                    errorCodeLine[5] = tError->getStringRep();
                }
                if(tError->getNext()!=nullptr)
                {
                    tError = tError->getNext();
                    errorCodeLine[6] = tError->getStringRep();
                }
                }
                errorLines.push_back(errorMissingEndIf+errorCodeLine[1]+" "+errorCodeLine[2]+" "+errorCodeLine[3]+" "+errorCodeLine[4]+" "+errorCodeLine[5]+" "+errorCodeLine[6]+" "+errorCodeLine[7]);
                for(int ii=0; ii <7;ii++)
                {
                    errorCodeLine[ii] = " ";
                }
            }
            else if(ifEndifBalance<=0)
            {
                errorLines.pop_back();
            }
        }
        else if (t->getStringRep() == "end")
        {
            if(t->getNext()!= nullptr)
            {
                tError = t->getNext();
                if(tError ->getStringRep() == "if")
                {
                    ifEndifBalance--;
                    if(ifEndifBalance<0)
                    {
                        { // This part gets the tokens around the error
                        errorCodeLine[3] = t->getStringRep();
                        if(t->getPrev()!=nullptr)
                        {
                            tError = t->getPrev();
                            errorCodeLine[2] = tError->getStringRep();
                        }
                        if(tError->getPrev()!=nullptr)
                        {
                            tError = tError->getPrev();
                            errorCodeLine[1] = tError->getStringRep();
                        }
                        if(tError->getPrev()!=nullptr)
                        {
                            tError = tError->getPrev();
                            errorCodeLine[0] = tError->getStringRep();
                        }
                        if(t->getNext()!=nullptr)
                        {
                            tError = t->getNext();
                            errorCodeLine[4] = tError->getStringRep();
                        }
                        if(tError->getNext()!=nullptr)
                        {
                            tError = tError->getNext();
                            errorCodeLine[5] = tError->getStringRep();
                        }
                        if(tError->getNext()!=nullptr)
                        {
                            tError = tError->getNext();
                            errorCodeLine[6] = tError->getStringRep();
                        }
                        }
                        errorLines.push_back(errorMissingIf+errorCodeLine[1]+" "+errorCodeLine[2]+" "+errorCodeLine[3]+" "+errorCodeLine[4]+" "+errorCodeLine[5]+" "+errorCodeLine[6]+" "+errorCodeLine[7]);
                        for(int ii=0; ii <7;ii++)
                        {
                            errorCodeLine[ii] = " ";
                        }
                    }
                    else if (ifEndifBalance>=0)
                    {
                        errorLines.pop_back();
                    }
                }
            }
        }
		t = t->getNext();
	}

	//this part finds the missing thens.
    t = tokens.getFirst();
    tError = tokens.getFirst();
	while(t)
	{
	    if(t->getStringRep() == "if")
        {
            ifwhenBalance++;
            if(ifwhenBalance>0)
            {
                { // this part gets the tokens around the error.
                errorCodeLine[3] = t->getStringRep();
                if(t->getPrev()!=nullptr)
                {
                    tError = t->getPrev();
                    errorCodeLine[2] = tError->getStringRep();
                }
                if(tError->getPrev()!=nullptr)
                {
                    tError = tError->getPrev();
                    errorCodeLine[1] = tError->getStringRep();
                }
                if(tError->getPrev()!=nullptr)
                {
                    tError = tError->getPrev();
                    errorCodeLine[0] = tError->getStringRep();
                }
                if(t->getNext()!=nullptr)
                {
                    tError = t->getNext();
                    errorCodeLine[4] = tError->getStringRep();
                }
                if(tError->getNext()!=nullptr)
                {
                    tError = tError->getNext();
                    errorCodeLine[5] = tError->getStringRep();
                }
                if(tError->getNext()!=nullptr)
                {
                    tError = tError->getNext();
                    errorCodeLine[6] = tError->getStringRep();
                }
                }
                errorLines.push_back(errorMissingThen+errorCodeLine[1]+" "+errorCodeLine[2]+" "+errorCodeLine[3]+" "+errorCodeLine[4]+" "+errorCodeLine[5]+" "+errorCodeLine[6]+" "+errorCodeLine[7]);
                for(int ii=0; ii <7;ii++)
                {
                    errorCodeLine[ii] = " ";
                }
            }
            else if(ifEndifBalance<=0)
            {
                errorLines.pop_back();
            }
        }
        else if (t->getStringRep() == "then")
        {
            ifwhenBalance--;
            if(ifEndifBalance<0)
            {
                { // This part gets the tokens around the error
                errorCodeLine[3] = t->getStringRep();
                if(t->getPrev()!=nullptr)
                {
                    tError = t->getPrev();
                    errorCodeLine[2] = tError->getStringRep();
                }
                if(tError->getPrev()!=nullptr)
                {
                    tError = tError->getPrev();
                    errorCodeLine[1] = tError->getStringRep();
                }
                if(tError->getPrev()!=nullptr)
                {
                    tError = tError->getPrev();
                    errorCodeLine[0] = tError->getStringRep();
                }
                if(t->getNext()!=nullptr)
                {
                    tError = t->getNext();
                    errorCodeLine[4] = tError->getStringRep();
                }
                if(tError->getNext()!=nullptr)
                {
                    tError = tError->getNext();
                    errorCodeLine[5] = tError->getStringRep();
                }
                if(tError->getNext()!=nullptr)
                {
                    tError = tError->getNext();
                    errorCodeLine[6] = tError->getStringRep();
                }
                }
                errorLines.push_back(errorMissingThen+errorCodeLine[1]+" "+errorCodeLine[2]+" "+errorCodeLine[3]+" "+errorCodeLine[4]+" "+errorCodeLine[5]+" "+errorCodeLine[6]+" "+errorCodeLine[7]);
                for(int ii=0; ii <7;ii++)
                {
                    errorCodeLine[ii] = " ";
                }
            }
            else if (ifEndifBalance>=0)
            {
                errorLines.pop_back();
            }
        }
        t = t->getNext();
	}


	if (ifEndifBalance == 0)
    {
        numberOfMissingEndIfs =0;
        numberOfMissingIfs = 0;
    }
    else if (ifEndifBalance < 0)
    {
        numberOfMissingEndIfs = abs(ifEndifBalance);
        numberOfMissingIfs = 0;
    }
    else if (ifEndifBalance >0)
    {
        numberOfMissingEndIfs =0;
        numberOfMissingIfs = abs(ifEndifBalance);
    }

    if (ifwhenBalance == 0)
    {
        numberofMissingThens =0;
    }
    else if (ifwhenBalance < 0)
    {
        numberofMissingThens = abs(ifwhenBalance);
    }
    else if (ifwhenBalance >0)
    {
        numberOfMissingIfs = numberOfMissingIfs + abs(ifwhenBalance);
        numberofMissingThens =0;
    }

    t = tokens.getFirst();
    Token *t_before = tokens.getFirst();
    Token *t_after = tokens.getFirst();
    tokenDetails *t_before_details = nullptr;
    tokenDetails *t_after_details = nullptr;


    while(t)
    {
        if(t->isOperator())
        {
            if(t->getPrev()!= nullptr && t->getNext() != nullptr)
            {
                t_before = t->getPrev();
                t_after = t->getNext();
            }
            else if(t->getPrev()== nullptr && t->getNext() == nullptr)
            {
                errorLines.push_back("Error: Cannot find Objects for \""+t->getStringRep()+"\" Operator");
            }
            else if (t->getPrev()!= nullptr && t->getNext() == nullptr)
            {
                t_before = t->getPrev();
                errorLines.push_back("Error: Cannot find next object for \""+t_before->getStringRep()+ " " +t->getStringRep()+"\" Operator");
            }
            else if (t->getPrev() == nullptr && t->getNext() != nullptr)
            {
                t_after = t->getNext();
                errorLines.push_back("Error: Cannot find previous object for \""+t->getStringRep()+ " " + t_after->getStringRep()+ "\" Operator");
            }

            t_before_details = t_before->getTokenDetails();
            t_after_details = t_after->getTokenDetails();

            if(t_before_details->type != t_after_details->type)
            {
                errorLines.push_back(errorTypeMismatch+ t_before->getStringRep()+" : "+t_before_details->type+ t->getStringRep() + t_after->getStringRep() +" : " + t_after_details->type);
            }
            else if (t_before_details->width != t_after_details->width)
            {
                errorLines.push_back(errorWidthMismatch+ t_before->getStringRep()+" : "+to_string(t_before_details->width)+ t->getStringRep() + t_after->getStringRep() +" : " + to_string(t_after_details->width));
            }


        }
    }


	cout << "Number of Tokens                  : " << numberOfTokens <<endl;
	cout << "Number of Conditional Expressions : " << numberOfCondExp <<endl;
	cout << "Number of Missing \"end if\"s     : " << numberOfMissingEndIfs << endl;
	cout << "Number of Missing \"if\"s         : " << numberOfMissingIfs << endl;
	cout << "Number of Missing \"When\"s       : " << numberofMissingThens << endl;


    if(verboseModeFlag)
    {
        cout << "Error Messages: " << endl;
        for ( vector<string>::iterator it = errorLines.begin() ; it != errorLines.end(); ++it)
        {
            cout << *it << endl;
        }
    }

  /* For your testing purposes only */
    ///test remove token type
    ///removeTokensOfType(tokens, T_Operator);
  /* Ensure that tokens have all type information set*/

  /* Create operator,identifier,literal, etc. tokenLists from the master list of tokens */


	return 0;
}
