/*
Name : Isaac Cheng Hui Tan (301247997), Tran Xuan Nhan Le [Ray] (301243743)
ENSC 251 Assignment 3
*/

//Use only the following libraries:
#include "parserClasses.h"
#include <string>
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

size_t Tokenizer::givesSmallest(size_t a, size_t b) //returns the smaller of the two numbers.
{
    if (a < b)
        return a;
    else
        return b;
}

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
  /*  while (temp ->getStringRep()== "--") ///the case the first line is a comment - go into the loops until the first line is not a comment
    {
        tokenList.deleteToken(temp);
        tokenList.deleteToken(temp2);
        temp = tokenList.getFirst(); ///increment of temp and temp2
        temp2 = temp->getNext();
    }

    while ((temp2->getNext()) != nullptr) ///check the if it the comment until the end of the list
    {
        temp3 = temp->getPrev(); //adjust temp3 and temp4 after the increment of temp and temp2 in previous loop
        temp4=temp2->getNext();
        if (temp->getStringRep() == "--") // if temp is contain "--" temp and temp2 are comments
        {
            tokenList.deleteToken(temp);
            tokenList.deleteToken(temp2);
            temp = temp4;
            temp2 = temp4->getNext(); //after delete the comments token, adjust temp and temp2 to the new position
        }
        //case we not delete anything -> increment
        temp = temp->getNext();
        temp2 = temp2->getNext();
    }
    /// the above loop reach the end when temp and temp2 is the last 2 node of the token link list
    ///we check the last 2 node if they are comments

    if (temp2->getStringRep()== "--" && temp->getStringRep() != "--") ///only the last node is a comment
    {

        temp->setNext(nullptr);
        tokenList.deleteToken(temp2);
    }
    else if ( temp->getStringRep()=="--") ///both 2 last node are comments
    {
        tokenList.deleteToken (temp);
        tokenList.deleteToken (temp2);
    }
    */
}


