/***********************************************************************
* Header:
*    Lesson 02, Infix
*    Brother Helfrich, CS 235
* Summary:
*    This header file contains all the necessary code to convert infix
*    equations to postfix notation. An attempt was made to complete the
*    code to convert to assembly as well, but remains incomplete.
* Author
*    Justin Stucki <8 Hrs>
************************************************************************/

#ifndef INFIX_H
#define INFIX_H

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include "stack.h"     // for STACK
using namespace std;   // <- I deleted this but got a bunch
                       // of compile errors in return

int    determineOrder          (char input);
bool   isOperator              (char input);
string variableName            (string &input);
string convertInfixToPostfix   (string &infix);
void   handleOperator          (char op, string &infix, string &postfix,
                                Stack<char> &theStack);
void   testInfixToPostfix      ();
string convertPostfixToAssembly(string postfix);
string determineOperator       (char input);
void   testInfixToAssembly     ();

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 * Code provided by Bro.Helfrich
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix:  " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/*****************************************************
 * DETERMINE ORDER
 * Returns an int based on the rank of an operator in
 * the order of operations
 *****************************************************/
int determineOrder(char input)
{
   switch (input)
   {
      case '(':           //Highest rank: "()"
         return 4;
         break;
      case ')':           //Special case of ")"
         return 3;        //used in stack logic
         break;
      case '^':           //Exponents
         return 2;
         break;
      case '*':           //Multiplication
      case '/':           //Division
      case '%':           //Modulus
         return 1;
      break;
      case '+':           //Addition
      case '-':           //Subtraction
         return 0;
      break;
      default:            //Error check
         return 5;        //Unrecognized operator
   }
}

/*****************************************************
 * IS OPERATOR
 * Returns true if the input matches an acceptable
 * operator, returns false otherwise
 *****************************************************/
bool isOperator(char input)
{
   switch (input)
   {
      case '(':    //Accepted operators
      case ')':
      case '^':
      case '*':
      case '/':
      case '%':
      case '+':
      case '-':
         return true;

      default:    //Everything else
         return false;
   }
}

/*****************************************************
 * VARIABLE NAME
 * Parses a string char by char to obtain a whole
 * variable name or decimal number
 *****************************************************/
string variableName(string &input)
{
   string variable;
   while (input[0] != ' '   && input[0] != ')'
          && !input.empty() && !isOperator(input[0]))
   {
      variable += input[0];  //Append the next char to the output string
      input.erase(0,1);      //Erase it off the input
   }
   return variable;          //Return complete variable/decimal
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(string & infix)
{
   string postfix;
   Stack<char> theStack;

   while(infix.size() && infix != "quit")
   {
      if (infix[0] == ' ')     //Get rid of any pesky spaces
         infix.erase(0,1);

      //If a char is identified as an operator
      else if(isOperator(infix[0]))
      {
         handleOperator(infix[0], infix, postfix, theStack);
         //Remove operator from input (and space if necessary)
         infix.erase(0,1);
      }

      //Test if input is more than a single char
      else if (infix[1] != ' ' && infix[1] != ')' && infix.size() != 1)
      {
         //Space output appropriately and obtain string from input
         postfix += " ";
         postfix += variableName(infix);
      }

      //single char input
      else
      {
         //Space output, append char, remove char from input
         postfix += " ";
         postfix += infix[0];
         infix[1] == ' ' ? infix.erase(0,2) : infix.erase(0,1);
      }
   }

   //Empty the stack when input is empty
   while (infix.empty() && theStack.size())
   {
      if (theStack.top() == '(')     //If '(' is the only thing in the stack
         theStack.pop();
      else
      {
         postfix += " ";
         postfix += theStack.top();  //Retrieve and append to output
         theStack.pop();             //Remove from stack
      }
   }

   if (postfix[0] == ' ')     //Final output spacing adjustment
      postfix.erase(0,1);

   return postfix;            //Return generated postfix string
}

/*****************************************************
 * HANDLE OPERATOR
 * Performs the logic of order of operations,
 * tops, pops, and pushes accordingly while appending
 * output string
 *****************************************************/
void handleOperator(char op, string &infix, string &postfix,
                    Stack<char> &theStack)
{
   //Find out which rank the operator has
   switch (determineOrder(op))
   {
      //Error check for unrecognized operators
      case 5: //Unrecognized
         postfix = "Unrecognized operator: " + op;
         break;

         //Always push '(' onto the stack
      case 4: // (
         theStack.push(op);
         break;

         //Retrieves and appends everything between parentheses
      case 3: // )
         while (theStack.top() != '(')
         {
            postfix += " ";
            postfix += theStack.top();
            theStack.pop();
         }
         theStack.pop();
         break;

         //Always push eponents to the stack
      case 2: // ^
         theStack.push(op);
         break;

         //Compare if operator should go to stack or output
      case 1: // *, /, and %
      case 0: // + and -
         if (theStack.empty() || theStack.top() == '(' ||
             determineOrder(op) > determineOrder(theStack.top())) //Look into
         {
            theStack.push(op);
            break;
         }
         //If operator forces the stack to empty
         else
         {
            //While rank of current operator doesn't preceed stack.top
            while (!theStack.empty() &&
                   determineOrder(op) <= determineOrder(theStack.top()))
            {
               postfix += " ";
               postfix += theStack.top();
               theStack.pop();
            }
            //Now output the current operator and remove it from input
            theStack.push(op);
         }
   }
}


/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(string postfix)
{
   string assembly;
/*   cout << postfix << endl;
   //Until postfix string is transferred to assembly
   int  variables = 1;
//   while (postfix.size())
   {  //Search for opeartors by rank
      for (int i1 = 4; i1 >= 0 ; i1--)
      {
         cout << assembly << endl;
         //Transverse the string looking for operators
         for (int i2 = 0; i2 < postfix.length(); i2++)
         {  //Act when operator is found
            if (isOperator(postfix[i2]) && determineOrder(postfix[i2]) == i1)
            {  //Backtrack to left side operand
               int skips = 0;
               for (int i3 = i2; i3 >= 0 && skips < 4; i3--)
               {
                  //Do nothing while moving over characters
                  if (postfix[i3] != ' ' && i3 >= 0);
                  //Convert postfix to assembly beginning with LOAD left side
                  else if (skips == 3)
                  {
                     //Keep track of spaces between operands
                     int spaces = 0;
                     //Assembly always starts with "LOAD "
                     assembly += "LOAD ";

                     //Make conversion to assembly
                     for (int i4 = (i3 + 1); i4 <= i2; i4++)
                     {
                        //Add charcters to assembly
                        if (postfix[i4] != ' ')
                           assembly += postfix[i4];
                        //Add operator command
                        else if (spaces == 1)
                           assembly += determineOperator(postfix[i2]);
                        //End with STORE command 
                        else if (spaces == 2)
                        {
                           assembly += "STORE ";
                           i4++;
                           spaces = 0;
                        }
                        else if (postfix[i4] == ' ')
                           spaces++;
                        string tmp = "VALUE" + variables;
                        postfix.replace(i3 + 2, i2, tmp);
                     }
                  }
                  //Keep track of spaces while backtracking
                  else if (postfix[i3] == ' ')
                     skips++;
               }
            }
         }     
      }
      }*/
   return assembly;
}

/**********************************************
 * DETERMINE OPERATOR
 * Returns the operator command applicable to 
 * char passed in
 **********************************************/
/*string determineOperator(char input)
{
   string oper;
   switch (input)
   {
      case '^':
         oper = "EXPONENT ";
         break;
      case '*':
         oper = "MULTIPLY ";
         break;
      case '/':
         oper = "DIVIDE ";
         break;
      case '%':
         oper = "MODULUS ";
         break;
      case '+':
         oper = "ADD ";
         break;
      case '-':
         oper = "SUBTRACT ";
         break;
   }
   return oper;
   }*/

/**********************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 * Some code provided by Bro.Helfrich
 **********************************************/
void testInfixToAssembly()
{
   string input;
   string postfix;
   string assembly;
 
   // handle errors
   if (cin.fail())
   {
      cin.clear();
      cin.ignore(256, '\n');
   }
   
   // prompt for infix
   cout << "Enter an infix equation.  Type \"quit\" when done.\n"
        <<"infix > ";
   getline(cin, input);
   postfix = convertInfixToPostfix(input);
//   cout << postfix << endl;
   assembly = convertPostfixToAssembly(postfix);
//   cout << assembly << endl;
/*   int skips = 0;
   for(int i = 0; i < assembly.length(); i++)
   {
      if(assembly[i] != ' ')     //Display assembly command
      {
         cout << assembly[i];
      }
      else if (skips == 2)
      {
         skips = 0;
         cout << endl;
//         continue;
      }
      else if(assembly[i] == ' ')
      {
         skips++;
//         continue;
      }
      }*/
}

#endif // INFIX_H
