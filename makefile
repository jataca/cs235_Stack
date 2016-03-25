###############################################################
# Program:
#     Lesson 02, STACK
#     Brother Helfrich, CS235
# Author:
#     Jacob Casperson & Justin Stucki
# Summary:
#     A personal implementation of the stack container and a 
#     set of test functions which convert infix notation to 
#     postfix notation
# Time:
#     About 13 Hrs between us both
#     Each of us gave 100% effort.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h lesson02.o infix.o 
	g++ -o a.out lesson02.o infix.o 
	tar -cf lesson02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson02.o     : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
lesson02.o: stack.h infix.h lesson02.cpp
	g++ -c lesson02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

