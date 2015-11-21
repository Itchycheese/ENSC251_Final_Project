/*
Name : Isaac Cheng Hui Tan (301247997), Tran Xuan Nhan Le [Ray] (301243743)
ENSC 251 Final Pro
*/


#include "parserClasses.h"
#include <string>
#include <clocale>
#include <cctype>
#include <stdlib.h>
#include <stdio.h>
/// debug code
//#include <iostream>







//****TokenList class function definitions******
//           function implementations for append have been provided and do not need to be modified


//Creates a new token for the string input, str
//Appends this new token to the TokenList
//On return from the function, it will be the last token in the list
void TokenList::append(const string &str) {
	Token *token = new Token(str);
	append(token);
}

//Appends the token to the TokenList if not null
//On return from the function, it will be the last token in the list
void TokenList::append(Token *token) {

	findAndSetTokenDetails(token);
	if (!head) {
		head = token;
		tail = token;
	}
	else {
		tail->setNext(token);
		token->setPrev(tail);
		tail = token;
	}
}


//Complete the implementation of the following member functions:
//****Tokenizer class function definitions******

//Computes a new tokenLength for the next token
//Modifies: size_t tokenLength, and bool complete
//(Optionally): may modify offset
//Does NOT modify any other member variable of Tokenizer
void Tokenizer::prepareNextToken()
{/*Fill in implementation */

    ///this is testing

    string thestring;
    string firstchar;
    string secondchar;

    ///debug code
    //cout << "the string is: "<<*str << endl;


    thestring = *str;

    size_t delimiter_test = string::npos;
    size_t quote_delim_test = string::npos;
    size_t next_delimiter;
    size_t temp_offset;
    size_t non_quote_delimiter = string::npos;

    //check if we are at the end of the line
    if(offset >= thestring.length()) //check if it the end of string, if yes stop prepare the next token
    {
        complete = true;
        return;
    }

    //first step is to get the first token.
    //start of a new string
    /*
    if (offset ==0)
    {
        firstchar = thestring.substr(offset,1);
        delimiter_test = firstchar.find_first_of(" ,.;[]{}()_?`~!@#$%^&|_+",0);
        tokenLength = 1;
        return;
    }
    */
    //normal cases
    firstchar = thestring.substr(offset,1);
    delimiter_test = firstchar.find_first_of(",.;[]{}()?`~!@#$%^&|+",0);
    if (delimiter_test != 0) // checking if the first char, if first char is not one of the single delimiter, then token length is not 1
    {

        /// checks for single quotes - if yes the entire quote will be 1 token
        quote_delim_test = firstchar.find_first_of("'",0);
        if(quote_delim_test == 0)
        {
            next_delimiter = thestring.find_first_of("'", offset+1);
            non_quote_delimiter = thestring.find_first_of(",.;[]{}()?`~!@#$%^&|+\<=:/*>- \t\r\n",offset+1);
            if (non_quote_delimiter < next_delimiter)
            {
                tokenLength = 1;
                return;
            }
            if (next_delimiter == string::npos)
            {
                tokenLength = 1;
                return;
            }
            tokenLength = next_delimiter-offset+1;
            return;
        }

        ///checks for double quotes - if yes, the entire double quote will be 1 token
        quote_delim_test = firstchar.find_first_of("\"",0);
        if(quote_delim_test == 0)
        {
            next_delimiter = thestring.find_first_of("\"", offset+1);
            tokenLength = next_delimiter-offset+1;
            return;
        }

        ///checks for <= delimiter
        quote_delim_test = firstchar.find_first_of("<",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "=")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1; // if it not double delimiter, it will be a single delimiter token
                return;
            }
        }

        ///checks for => delimiter
        quote_delim_test = firstchar.find_first_of("=",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == ">")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1;// if it not double delimiter, it will be a single delimiter token
                return;
            }
        }

        ///checks for := double delimiter
        quote_delim_test = firstchar.find_first_of(":",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "=")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1; // it is a single delimiter in this case
                return;
            }
        }

        ///checks for /= double delimiter
        quote_delim_test = firstchar.find_first_of("//",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "=")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1; // single delimiter found
                return;
            }
        }

        ///checks for ** double delimiter
        quote_delim_test = firstchar.find_first_of("*",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "*")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1; // single delimiter * found
                return;
            }
        }

        ///checks for >= double delimiter
        quote_delim_test = firstchar.find_first_of(">",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "=")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1; // single delimiter > found
                return;
            }
        }

        ///checks for -- double delimiter, this also the begin of a comments for the removeComment function later
        quote_delim_test = firstchar.find_first_of("-",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "-")
            {
                tokenLength = 9999;
                return;
            }
            else
            {
                tokenLength =1; // single delimiter - found
                return;
            }
        }

        ///checks if it is a bit vector
        quote_delim_test = firstchar.find_first_of("bBOoxX",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "\"")
            {
                next_delimiter = thestring.find_first_of("\"", offset+2);
                tokenLength = next_delimiter-offset+1;
                return; /// if the bit vector condition is not right, this mean the token is the begin of a work entities
            }
        }

        /// checks for word entities - no delimiter or bit vector, it just a normal words - numbers entities token
        {
            quote_delim_test = firstchar.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIGJLMNOPQRSTUVWXYZ0123456789",0); //case sensitive and number as a token
            if(quote_delim_test == 0) // all other case hase been cover -> thus, it must be a word-number entity token.
            {
                next_delimiter = thestring.find_first_of(",.;:<>[]{}()?/`~!@#$%^&*|-=+  \t\r'\"-", offset+1); // find the next single-double delimiter/ space/tab as the END of this words-numbers entity token
                tokenLength = next_delimiter - offset;
                return;
            }

        }

        /// checks for whitespace. if it is a white space/tab, we will skip this -> it 's not a token
        {
            quote_delim_test = firstchar.find_first_of(" \t\r",0);
            if(quote_delim_test == 0)
            {
                offset = offset +1;
                prepareNextToken();
                return;
            }
        }

        /// checks for newlines -> skip new line, it is not a token
        {
            quote_delim_test = firstchar.find_first_of("\n",0);
            if(quote_delim_test == 0)
            {
                complete = true;
                return;
            }
        }
    }
    else
    {
        tokenLength = 1;
        return;
    }
}

//Sets the current string to be tokenized
//Resets all Tokenizer state variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
void Tokenizer::setString(string *str)
{
    complete = false;
    offset = 0;
    tokenLength =0;
    this->str = str;
    prepareNextToken();
    return;
}

//Returns the next token. Hint: consider the substr function
//Updates the tokenizer state
//Updates offset, resets tokenLength, updates processingABC member variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
string Tokenizer::getNextToken()
{/*Fill in implementation */

    string the_string;
    string the_token;
    the_string = *str;

    if(tokenLength == 9999) //9999 is the code for comment indications. Realistically no token should be this long
    {
        the_token = the_string.substr(offset,2);
        offset = offset+2;
        tokenLength = 14370;
        ///debug
        //cout << "the token is: \"" <<the_token << "\"\n";

        return the_token;
    }
    else if(tokenLength == 14370) //14370 is the code for comment token, treat everything until the end of string as one token
    {
        the_token = the_string.substr(offset,string::npos);
        complete = true;
        ///debug
        //cout << "the token is: \"" <<the_token << "\"\n";

        return the_token;
    }
    else
    {
        the_token = the_string.substr(offset,tokenLength);
        offset = offset+tokenLength;
        prepareNextToken();
        ///debug
        //cout << "the token is: \"" <<the_token << "\"\n";

        return the_token;
    }

}


void Token::setTokenDetails(const string &type, int width)
{
    details = new tokenDetails;
    details->type = type;
    details->width = width;
}



TokenList* findAllConditionalExpressions(const TokenList &inList)
{
    Token *current = inList.getFirst();;
    bool insideConditional = false;
    TokenList *returnedList = new TokenList();

    while(current->getNext() != nullptr)
    {
        if(current->getStringRep() == "else" || current->getStringRep() == "then")
        {
            returnedList->append("\\n");
            insideConditional = false;
        }

        if(insideConditional)
        {
            Token* copyOfToken = new Token(*current); // for some reason copy constructor to Token(Token*) cannot call.
            /*tokenDetails* theDetails;

            copyOfToken->setStringRep(current->getStringRep());
            copyOfToken->setNext(current->getNext());
            copyOfToken->setPrev(current->setPrev()); //Cant call this idk why. setNext() is fine though.

            theDetails = current->getTokenDetails();
            copyOfToken->setTokenDetails(theDetails->type, theDetails->width);
            if(current->isKeyword())
            {
                copyOfToken->setKeyword();
            }
            copyOfToken->setTokenType(current->getTokenType()); */


            returnedList->append(copyOfToken);
        }
        else if(current->getStringRep() == "if" || current->getStringRep() == "elsif" || current->getStringRep() == "when")
        {
            insideConditional = true;
        }

        current = current->getNext();
    }
    return returnedList;
}

//****Challenge Task Functions******

//Removes the token from the linked list if it is not null
//Deletes the token
//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
void TokenList::deleteToken(Token *token)
{
    Token *temp= nullptr;
    Token *temp2= nullptr;
    if (token != nullptr)
    {
        if(token->prev == nullptr && token->next == nullptr) /// case only one token inside the list, we just delete the token
        {
            delete token;
        }
        else if (token->prev == nullptr) /// case token is the first node, delete token and change the head pointer, also ajust next and previous
        {
            head = token->next;
            head ->prev= nullptr;
            delete token;
        }
        else if (token->next == nullptr) /// case token is the last node, delete token, adjust the tail pointer, prev and next pointer
        {
            tail = token->prev;
            tail-> next = nullptr;
            delete token;
        }
        else                            /// case token is the middle node, delete the token, adjust next and prev pointer. temp is a pointer point to the previous node of the token, temp2 is point to the next node of the token
        {
            temp = token->prev;
            temp->next = token->next;
            temp2 = token->next;
            temp2->prev = temp;
            delete token;
        }
    }
}

//Removes all comments from the tokenList including the --  marker
//Returns the number of comments removed
int removeComments(TokenList &tokenList)
{
    Token *temp = nullptr; // temp is the pointer point to the node that we check if it a comment
    Token *temp2= nullptr; // temp2 is the node next to the node contain "--", which is the rest of the comment
    Token *temp3= nullptr; // temp3 is the node before the comment
    Token *temp4= nullptr; // temp4 is the node after the comment
    temp = tokenList.getFirst();
    temp2 = temp ->getNext();
    temp3 = temp2 ->getNext();
    temp4 = temp ->getPrev();
    while ( temp2 ->getNext() != nullptr)///delete the comment until the last two token
    {
        if ( temp->getStringRep() == "--")
        {
            tokenList.deleteToken(temp);
            tokenList.deleteToken(temp2);
            temp = temp3;
            temp2 = temp3->getNext();
            temp3 = temp2->getNext();
        }
        else
        {
            temp = temp2;
            temp2 = temp3;
            temp3 = temp3 ->getNext();
        }
    }
    if (temp ->getStringRep() == "--")
    {
        tokenList.deleteToken(temp);
        tokenList.deleteToken(temp2);
    }
    else if ( temp2->getStringRep()== "--")
    {
        tokenList.deleteToken(temp2);
    }
}



void TokenList::findAndSetTokenDetails(Token *token)
{
    string tokenIs;
    size_t strSize;
    string firstchar;
    string secondchar;
    string lastchar;
    size_t firstcharflag;
    size_t secondcharflag;
    char lowChar;
    int bitWidthMultiplier = 1;
    int bitWidth = 0;
    tokenIs = token->getStringRep();
    strSize = tokenIs.size();


    lastchar = tokenIs.substr(strSize-1,1);
    lastchar = '\0';

    if(strSize != 1)
    {
        lastchar = tokenIs.substr(strSize-1,1);
    }

    /// Coverts the string tolower.
    for (int ii=0; ii<strSize; ++ii)
    {
        tokenIs[ii] = tolower(tokenIs[ii]);
    }

    /// Checks to see if the token is a keyword.
    for(int ii=0; ii < 97; ii++)
    {
        if (tokenIs == keyWordList[ii])
        {
            token->setKeyword();
            break;
        }
    }

    /// Checks to see if the token is a literal.
    firstchar = tokenIs.substr(0,1); //check if it is a integer.
    firstcharflag = firstchar.find_first_of("0123456789",0);
    if(firstcharflag == 0)
    {
        token->setTokenType(T_Literal);
        token->setTokenDetails("integer",strSize);
    }
    firstcharflag = firstchar.find_first_of("bBOoxX",0); //checks to see if it is one of them bit vectors.
    if(firstcharflag == 0)
    {
        secondchar = tokenIs.substr(1,1);
            if(secondchar == "\"") // is second char a "?
            {
                lowChar = tolower(int(firstchar[0])); //sets the proper multiplier for the width.
                if(lowChar == 'b')
                {
                    bitWidthMultiplier = 1;
                }
                else if (lowChar == 'o')
                {
                    bitWidthMultiplier = 3;
                }
                else if (lowChar == 'x')
                {
                    bitWidthMultiplier = 4;
                }

                token->setTokenType(T_Literal);
                bitWidth = ((strSize-2)*bitWidthMultiplier);
                token->setTokenDetails("Literal", bitWidth);

            }
    }
    else if (firstchar.compare("\"") == 0) //sets the multipler for bit vectors with no b in front
    {
        if(lastchar.compare("\"") == 0)
        {
            bitWidthMultiplier = 1;
            token->setTokenType(T_Literal);
            bitWidth = ((strSize-2)*bitWidthMultiplier);
            token->setTokenDetails("Literal", bitWidth);
        }
    }
    else if (firstchar.compare("'")==0) //sets the multipler for ' vectors.
    {
        if (lastchar.compare("'") == 0)
        {
            bitWidthMultiplier = 1;
            token->setTokenType(T_Literal);
            bitWidth = ((strSize-2)*bitWidthMultiplier);
            token->setTokenDetails("Literal", bitWidth);
        }
    }


    ///check if token is a comment body
    Token *previous_token = nullptr;
    previous_token = token->getPrev();
    string previous_token_string = previous_token->getStringRep();

    if ( previous_token_string == "--") /// this token is a comment body
    {
        token->setTokenType(T_CommentBody);
        token->setTokenDetails("comment",0);
    }
    ///check to see if a token is a identifier
    firstcharflag = firstchar.find_first_of("abcdefghijklmnopqrstuwxyz",0);
    if(firstcharflag == 0)
    {
        secondchar = tokenIs.substr(1,1);
            if (strSize == 1) ///case identifier is only 1 char
            {
                token->setTokenType(T_Identifier);
                //check before and after if it a signal/variable define line ?

                //get the value of the previous and next token to find the type of identifier


                Token *next_token = nullptr;
                next_token = token->getNext();
                string next_token_string = next_token->getStringRep();

                Token *token_type = nullptr;
                token_type = next_token->getNext();
                string token_type_string = token_type->getStringRep();
                for (int ii =0; ii < 97; ii++)
                    if (previous_token_string == keyWordList[ii] && next_token_string ==":")
                    {
                        Token *bracket_check = nullptr;
                        bracket_check = token_type->getNext();
                        string bracket_check_str = token_type->getStringRep(); // to check if next token is a bracket
                        if (bracket_check_str == "(" )
                        {
                            //check if inside the bracket there is a to/downto
                            Token *first_number = bracket_check->getNext();
                            Token *vector_check = first_number ->getNext();
                            string vector_check_str = vector_check->getStringRep();
                            if (vector_check_str == "to" || vector_check_str == "downto")
                            {
                                 //this is a vector, we need to set detail of type and width of the vector

                                 string first_number_str = first_number->getStringRep();
                                 Token *second_number = vector_check->getNext();
                                 string second_number_str = second_number->getStringRep();
                                 int firstnum = 0;
                                 firstnum = stoi(second_number_str);
                                 int secondnum = stoi(first_number_str);
                                 int width_token = abs( firstnum - secondnum ) +1;
                                 token->setTokenDetails(token_type_string, width_token);
                                 ///need to consider about default value if needed
                            }
                            else //bracket but not a vector type ? set width = 0
                            {
                                token->setTokenDetails(token_type_string, 0);
                            }
                        }
                        else //if there is not a bracket the width of vector will be 0
                            {
                                token->setTokenDetails(token_type_string, 0);
                            }

                        break; // previous match one of the key word list, no more same match, break the loops
                    }

            }
            else if (secondchar != "\"" ) /// case identifier contain more than or =2 char
            {


                Token *next_token = nullptr;
                next_token = token->getNext();
                string next_token_string = next_token->getStringRep();

                Token *token_type = nullptr;
                token_type = next_token->getNext();
                string token_type_string = token_type->getStringRep();

                for(int ii=0; ii < 28; ii++)
                {
                    if (tokenIs != operatorList[ii])
                    {
                        token->setTokenType(T_Identifier);

                        for (int ii =0; ii < 97; ii++)
                        if (previous_token_string == keyWordList[ii] && next_token_string ==":")
                        {
                            Token *bracket_check = nullptr;
                            bracket_check = token_type->getNext();
                            string bracket_check_str = token_type->getStringRep(); // to check if next token is a bracket
                            if (bracket_check_str == "(" )
                            {
                                //check if inside the bracket there is a to/downto
                                Token *first_number = bracket_check->getNext();
                                Token *vector_check = first_number ->getNext();
                                string vector_check_str = vector_check->getStringRep();
                                if (vector_check_str == "to" || vector_check_str == "downto")
                                {
                                     //this is a vector, we need to set detail of type and width of the vector

                                     string first_number_str = first_number->getStringRep();
                                     Token *second_number = vector_check->getNext();
                                     string second_number_str = second_number->getStringRep();
                                     int width_token = abs( stoi(second_number_str) - stoi(first_number_str) ) +1;
                                     token->setTokenDetails(token_type_string, width_token);
                                     ///need to consider about default value if needed
                                }
                                else
                                {
                                    token->setTokenDetails(token_type_string, 0);
                                }
                            }
                            else //case there is no bracket, vector width = 0
                                {
                                    token->setTokenDetails(token_type_string, 0);
                                }


                        }
                    }
                }
            }
    }
    ///check to see if token is an operator
            for(int ii=0; ii < 28; ii++)
                {
                    if (tokenIs == operatorList[ii])
                    {
                        token->setTokenType(T_Operator);
                        token->setTokenDetails("operator",0);
                        break;
                    }
                }
    /// it will type Other if it not any other type - which is the default type in the default constructor

}

int removeTokensOfType(TokenList &tokenList, tokenType type)
{
    Token *current = nullptr;
    current = tokenList.getFirst();
    Token *next_token = nullptr;
    next_token = current ->getNext();
    int num_token_delete = 0;
    while (next_token != nullptr)
    {
        if (current->getTokenType() == type)
        {
            tokenList.deleteToken(current);
            num_token_delete ++;
            current = next_token;
            next_token=current->getNext();
        }
        current = next_token;
        next_token = current->getNext();
    }
    if (current->getTokenType() == type) /// the last node of the token list
        {
            tokenList.deleteToken(current);
            num_token_delete ++;
            current = next_token;
            next_token=current->getNext();
        }
    return num_token_delete;
}
