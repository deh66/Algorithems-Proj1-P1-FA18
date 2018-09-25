//	Daniel Hollo
//	deh66@zips.uakron.edu
//	UAID: 2980428

// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

// NOTES TO DAN //
//Part I : RSA key generation.
//	Implement Fermat test;
//	Use Fermat’s test to generate two large prime numbers(p, q), each should have a size >= 512 bits;
//	Save p and q in a file named p_q.txt, one integer per line and making sure no white space saved;
//	Use extended Euclidean algorithm to generate two pairs of keys : (e, n), (d, n), where n = p * q;
//	Save the two pairs of keys in two separate files : e_n.txt and d_n.txt, one integer per line and no white space;
//              //

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {
		      
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned big1 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big1 = big1*10 +rand();
      }
      std::cout << "my big1 !!!\n";
      std::cout << big1;
      BigUnsigned big2 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big2 = big2*10 +rand();
      }
      std::cout << "my big2 !!!\n";
      std::cout << big2;
      std::cout << "my big3 = big1*big2 !!!\n";
      BigUnsigned big3 = big1*big2;
      std::cout <<big3;
      std::cout << "my big3/big2 !!!\n";
      std::cout <<big3/big2;
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}