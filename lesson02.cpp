/***********************************************************************
* Program:
*    Lesson 02, Stack
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary:
*    This is a driver program to exercise the Stack class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>    // for CIN and COUT
#include <string>      //
#include "stack.h"     // your Stack class should be in stack.h
#include "infix.h"     // for testInfixToPostfix() and testInfixToAssembly()
using namespace std;


// prototypes for our four test functions
void testSimple();
void testPush();
void testPop();
void testErrors();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testPush()
#define TEST3   // for testPop()
#define TEST4   // for testErrors()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // test comment 1
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a Stack.\n";
   cout << "\t2. The above plus push items onto the Stack.\n";
   cout << "\t3. The above plus pop items off the stack.\n";
   cout << "\t4. The above plus exercise the error handling.\n";
   cout << "\ta. Infix to Postfix.\n";
   cout << "\tb. Extra credit: Infix to Assembly.\n";

   // select
   char choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 'a':
         cin.ignore();
         testInfixToPostfix();
         break;
      case 'b':
         cin.ignore();
         testInfixToAssembly();
         break;
      case '1':
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case '2':
         testPush();
         cout << "Test 2 complete\n";
         break;
      case '3':
         testPop();
         cout << "Test 3 complete\n";
         break;
      case '4':
         testErrors();
         cout << "Test 4 complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }

   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a Stack: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   // Test1: a bool Stack with default constructor
   cout << "Create a bool Stack using the default constructor\n";
   Stack <bool> s1;
   cout << "\tSize:  " << s1.size() << endl;
   cout << "\tEmpty? " << (s1.empty() ? "Yes" : "No") << endl;

   // Test2: double Stack with non-default constructor
   cout << "Create a double Stack using the non-default constructor\n";
   Stack <double> s2(10 /*capacity*/);
   cout << "\tSize:  " << s2.size() << endl;
   cout << "\tEmpty? " << (s2.empty() ? "Yes" : "No") << endl;

   {
      // Test3: copy the bool Stack
      cout << "Copy the double Stack using the copy-constructor\n";
      Stack <double> s3(s2);
      cout << "\tSize:  " << s1.size() << endl;
      cout << "\tEmpty? " << (s1.empty() ? "Yes" : "No") << endl;
   }
   cout << "\tDestroying the third Stack\n";
#endif //TEST1
}

/*******************************************
 * TEST PUSH
 * Add a whole bunch of items to the stack.  This will
 * test the stack growing algorithm
 *****************************************/
void testPush()
{
#ifdef TEST2
   // create
   //cout << "you got in";
   cout << "Create an integer Stack with the default constructor\n";
   Stack <int> s;

   cout << "\tEnter numbers, type 0 when done\n";
   int number;
   do
   {
      cout << "\t> ";
      cin  >> number;
      if (number)
         s.push(number);
   }
   while (number);

   // display how big it is
   cout << "\tSize:  " << s.size() << endl;
   cout << "\tEmpty? " << (s.empty() ? "Yes" : "No") << endl;
#endif // TEST2
}

/*******************************************
 * TEST POP
 * We will test both Stack::pop() and Stack::top()
 * to make sure the stack looks the way we expect
 * it to look.
 ******************************************/
void testPop()
{
#ifdef TEST3
   // create
   cout << "Create a string Stack with the default constructor\n";
   Stack <string> s;

   // instructions
   cout << "\tTo add the word \"dog\", type +dog\n";
   cout << "\tTo pop the word off the stack, type -\n";
   cout << "\tTo see the top word, type *\n";
   cout << "\tTo quit, type !\n";

   // interact
   char instruction;
   string word;
   try
   {
      do
      {
         cout << "\t> ";
         cin  >> instruction;
         switch (instruction)
         {
            case '+':
               cin >> word;
               s.push(word);
               break;
            case '-':
               s.pop();
               break;
            case '*':
               cout << s.top() << endl;
               break;
            case '!':
               cout << "\tSize:  " << s.size() << endl;
               cout << "\tEmpty? " << (s.empty() ? "Yes" : "No") << endl;
               break;
            default:
               cout << "\tInvalid command\n";
         }
      }
      while (instruction != '!');
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST3
}

/*******************************************
 * TEST ERRORS
 * Numerous error conditions will be tested
 * here, including bogus popping and the such
 *******************************************/
void testErrors()
{
#ifdef TEST4
   // create
   cout << "Create a char Stack with the default constructor\n";
   Stack <char> s;

   // test using Top with an empty stack
   try
   {
      s.top();
      cout << "BUG! We should not be able to top() with an empty stack!\n";
   }
   catch (const char * error)
   {
      cout << "\tStack::top() error message correctly caught.\n"
           << "\t\"" << error << "\"\n";
   }

   // test using Pop with an empty stack
   try
   {
      s.pop();
      cout << "BUG! We should not be able to pop() with an empty stack!\n";
   }
   catch (const char * error)
   {
      cout << "\tStack::pop() error message correctly caught.\n"
           << "\t\"" << error << "\"\n";
   }
#endif // TEST4
}
