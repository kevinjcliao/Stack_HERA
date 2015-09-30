#include <HERA.h>
#include <HERA-print.h>





void HERA_main()
{
  // Put any #defines or, strings, or other data declarations here, or get them with #includes, e.g.
  // The following include is needed to use the hera 'print' function
#include <Tiger-stdlib-reg-data.hera>

#include "Stack-tests-data.hera"
	// Memory locations for add subtract space and period:
	// 900: Space (ASCII 32)
//	SET(R9, 32)
//	STORE(R9, 900, R0)
	// 901: . (ASCII 46)
//	SET(R9, 46)
//	STORE(R9, 901, R0)
	// 902: + (ASCII 43)
//	SET(R9, 43)
//	STORE(R9, 902, R0)
	// 903: - (ASCII 45)
//	SET(R9, 45)
//	STORE(R9, 903, R0)


	// REGISTRY USAGE:
	// R1: String operations
	// R2: Current Character Index
	// R3: The string character index (string_memory_location + R2)
	// R4: Integer to be added or popped.
	// R5: TOP: Latest registry in which memory is stored.
	// R6 & R7: Operations.
	// R8: String size


	DLABEL(the_string)
	  TIGER_STRING("4 3 4 4 - .")

	// Set the carry block before doing any other operations:
    SETCB()

	//Initialize top_of_stack by giving it the bottom value (make it empty)
	// cout << "I get here! ";

	// Put the main body of your HERA program after the initialization and testing of Stack
	SET(R3, the_string)

	// Set R8 to the size of the string
	SET(R1, the_string)
	CALL(R12, SIZE)
	MOVE(R8, R1)
	INC(R8, 1)
	cout<< "Size of string:";
	print_reg(R8)

	// Set R2 to the initial increment of 1
	SET(R2, 1)



	SET(R5, 0)
//	print_reg(R4)
//    CALL(R12, STACK_PUSH)
//
//
//	SET(R4, 120)	  SET(R2,1)
//	CALL(R12, STACK_PUSH)
//	SET(R4, 10)
//
//	CALL(R12, STACK_PUSH)
//	CALL(R12, STACK_ADD)
//
//
//	SET(R4, 250)
//	CALL(R12, STACK_PUSH)
//
//	CALL(R12, STACK_SUBTRACT)
//
//	CALL(R12, STACK_POP)
//	CALL(R12, STACK_POP)


	CALL(R12, OPERATION)
	LABEL(BREAK)
	cout<<"broke";

	//SET(R4, 0)
	//LABEL(input_1000_ints)

	  // first, run the test suite, or #include a file that does:
// #include "Stack-tests.hera"

	  HALT()	// end of main HERA program

	// Put any HERA function definitions here, or #include a file containing them

	/*
	 * MAIN STACK FUNCTIONS:
	 * PUSH, POP and TOP supported
	 */
	  LABEL(STACK_PUSH)
	  std::cout<<"Pushing: ";
	  print_reg(R4)
	  INC(R5, 1)
	  std::cout<<"Storing it into: ";
	  print_reg(R5)
	  STORE(R4, 1000, R5)
	  std::cout<<endl;
	  RETURN(R12, Rt)


	  LABEL(STACK_POP)
	  LOAD(R4, 1000, R5)
	  std::cout<<"Popping: ";
	  print_reg(R4)
	  DEC(R5, 1)
	  std::cout<<"Top address is now: ";
	  print_reg(R5)
	  std::cout<<endl;
	  RETURN(R12, Rt)


	  LABEL(STACK_TOP)
	  LOAD(R4, 1000, R5)
	  RETURN(R12, Rt)

	  /*
	   * STACK ARITHMETIC.
	   * supports ADD and SUBTRACT
	   */
	  LABEL(STACK_ADD)
	  CALL(R12, STACK_POP)
	  MOVE(R6,R4)
	  CALL(R12, STACK_POP)
	  MOVE(R7,R4)
	  ADD(R4,R6,R7)
	  std::cout<< "Added: ";
	  print_reg(R6)
	  std::cout<< " and: ";
	  print_reg(R7)
	  std::cout<< "result: ";
	  print_reg(R4)
	  CALL(R12, STACK_PUSH)
	  std::cout<<endl;
	  RETURN(R12, Rt)
	  RETURN(R12, Rt)


	  LABEL(STACK_SUBTRACT)
	  CALL(R12, STACK_POP)
	  MOVE(R6,R4)
	  CALL(R12, STACK_POP)
	  MOVE(R7,R4)
	  SUB(R4,R6,R7)
	  std::cout<< "SUBTRACTED: ";
	  print_reg(R6)
	  std::cout << " and: ";
	  print_reg(R7)
	  std::cout<< "result: ";
	  print_reg(R4)
	  CALL(R12, STACK_PUSH)
	  std::cout<<endl;
	  RETURN(R12, Rt)

	  /*
	   * MAIN INTERFACE FUNCTION
	   */
	  LABEL(OPERATION)
	  //BASE CASE: If String Length == 0: BREAK
	  CALL(R12, SIZE)
	  SET(R3, the_string)
	  ADD(R3, R2, R3)
	  CMP(R8,R2)
	  BZ(BREAK)
	  //ELSE:
	  LOAD(R1, 0, R3) // Get first character
	  // Check if it's a space Space (ASCII 32)
	  SET(R9, 32)
	  CMP(R1, R9)
	  BZ(SUBSTRING_AND_RECURSE)
	  // Check if it's a "."
	  SET(R9, 46)
	  CMP(R1, R9)
	  BZ(DOT_BEHAVIOR)
	  // Check if it's a "+"
	  SET(R9, 43)
	  CMP(R1, R9)
	  BZ(ADD_BEHAVIOR)
	  // Check if it's a "-"
	  SET(R9, 45)
	  CMP(R1, R9)
	  BZ(SUB_BEHAVIOR)
	  // Else: Assert it's an integer
	  // Push it.
	  BR(PUSH_BEHAVIOR)
	  //END OPERATION

	  // Simply converts integers from ASCII to
	  // standard decimal numbers
	  LABEL(STR_TO_INT)
	  DEC(R4, 32)
	  DEC(R4, 16)
	  RETURN(R12, Rt)

	  /* CALL BEHAVIORS: What to do when the first char is
	   * an int, a space, etc.
	   */
	  LABEL(ADD_BEHAVIOR)
	  CALL(R12, STACK_ADD)
	  BR(SUBSTRING_AND_RECURSE)

	  LABEL(SUB_BEHAVIOR)
	  CALL(R12, STACK_SUBTRACT)
	  BR(SUBSTRING_AND_RECURSE)

	  LABEL(DOT_BEHAVIOR)
	  CALL(R12, STACK_POP)
	  MOVE(R2, R4)
	  HALT()

	  LABEL(PUSH_BEHAVIOR)
	  MOVE(R4,R1) // Move it to push register
	  CALL(R12, STR_TO_INT) // push op
	  CALL(R12, STACK_PUSH) // push op
	  BR(SUBSTRING_AND_RECURSE)

	  LABEL(SUBSTRING_AND_RECURSE)
	  INC(R2, 1)
	  BR(OPERATION)



//		LABEL(STACK_MULTIPLY)
//		BR(STACK_POP)
//		MOVE(R6,R4)
//		BR(STACK_POP)
//		MOVE(R7,R4)
//		MULT(R4,R7,R6)
//		BR(STACK_PUSH)


	  HALT()  // just cautious programming to make sure the program doesn't run straight into the library functions
//The following include is needed to use the hera 'print' function
#include <Tiger-stdlib-reg.hera>


}
