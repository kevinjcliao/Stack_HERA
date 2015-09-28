#include <HERA.h>
#include <HERA-print.h>

void HERA_main()
{
  // Put any #defines or, strings, or other data declarations here, or get them with #includes, e.g.
  // The following include is needed to use the hera 'print' function
#include <Tiger-stdlib-reg-data.hera>

#include "Stack-tests-data.hera"


	// Set the carry block before doing any other operations:
    SETCB()

// Put the main body of your HERA program after the initialization and testing of Stack

	//Initialize top_of_stack by giving it the bottom value (make it empty)

	  // first, run the test suite, or #include a file that does:
#include "Stack-tests.hera"

	  HALT()	// end of main HERA program
	
	// Put any HERA function definitions here, or #include a file containing them

	  HALT()  // just cautious programming to make sure the program doesn't run straight into the library functions
//The following include is needed to use the hera 'print' function
#include <Tiger-stdlib-reg.hera>
}
