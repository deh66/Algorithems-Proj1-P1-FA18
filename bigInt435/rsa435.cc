//	Daniel Hollo
//	deh66@zips.uakron.edu
//	UAID: 2980428

// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 

#include <thread>
#include <fstream>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

// NOTES TO DAN //
//Part I : RSA key generation.
//	Implement Fermat test; X
//	Use Fermat’s test to generate two large prime numbers(p, q), each should have a size >= 512 bits;
//	Save p and q in a file named p_q.txt, one integer per line and making sure no white space saved;
//	Use extended Euclidean algorithm to generate two pairs of keys : (e, n), (d, n), where n = p * q;
//	Save the two pairs of keys in two separate files : e_n.txt and d_n.txt, one integer per line and no white space;
//              //

bool fermatTest(BigUnsigned&);
BigUnsigned generateBigPrime(BigUnsigned const &);

bool block = true;

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	/*try {
		      
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
	}*/

	/// My Code ///
	// Generate 2 Big numbers ( 512 Bits or greater )
	BigUnsigned p;
	BigUnsigned q;
	BigUnsigned temp;

	/// FERMAT TEST CODE ///
	// 2, 3, 5, 7, 11, 13, 17, 19, 23 and 29.
	/*fermatTest(3);
	fermatTest(5);
	fermatTest(7);
	fermatTest(11);
	fermatTest(13);
	fermatTest(17);
	fermatTest(19);
	fermatTest(23);
	fermatTest(29);*/
	/// //////////////// ///

	//while (temp.bitLength() < 512)
	//	temp = temp * 10 + rand();	// Initalize temp;

	//// Test for Primality
	//while (!fermatTest(temp))
	//{
	//	std::cout << "regenerating temp\n";
	//	// Not a prime number 
	//	// Generate new number
	//	temp = 0;
	//	while (temp.bitLength() < 512)//512
	//		temp = temp * 10 + rand();
	//}

	//// Assign new large prime number to p
	//p = temp;
	//std::cout << "p complete\n";
	////std::cout << "p= " << p << std::endl;

	//// Generate second large prime number
	//temp = 0;
	//while (temp.bitLength() < 512)
	//	temp = temp * 10 + rand();	// Initalize temp

	//// Test for Primality
	//while (!fermatTest(temp))
	//{
	//	// Not a prime number 
	//	// Generate new number
	//	temp = 0;
	//	while (temp.bitLength() < 512)//512
	//		temp = temp * 10 + rand();
	//}

	//// Assign second new large prime number to q
	//q = temp;

	
	// Threading Code
	std::thread genOne(generateBigPrime, std::ref(p));
	std::thread genTwo(generateBigPrime, std::ref(q));
	
	genOne.join();
	genTwo.join();

	std::cout << "P: " << p << "\n";
	std::cout << "Q: " << q << "\n";


	// Write p and q to file
	std::fstream pqFile;
	pqFile.open("p_q.txt", std::ios::out);
	pqFile << p << "\n" << q;
	pqFile.close();

	// Generate Key Pairs 
	BigUnsigned n = p * q;
	BigUnsigned nPhi = (p - 1) * (q - 1);

	// Generate (select) e, integer that is co-prime with nPhi
	BigUnsigned e = rand();
	while (e >= nPhi)
		e = rand();

	std::cout << "e generated: " << e << "\n";

	// Test if nPhi and e are relatively prime
	while (gcd(nPhi, e) != 1)
	{
		e = rand();
		while (e >= nPhi)
			e = rand();
	}
	// Generate d (multiplicative inverse of e)
	BigUnsigned d;
	try 
	{
		d = modinv(e, nPhi);
	}
	catch(char const* err)
	{
		std::cout << "ERROR COMPUTING MULTIPLICATIVE INVERSE OF d, FACTORS EXIST BETWEEN d AND nPhi.\n";
	}

	std::cout << "d generated: " << d << "\n";

	// Print e and d to seperate files
	std::fstream eFile;
	std::fstream dFile;

	eFile.open("e_n.txt", std::ios::out);
	dFile.open("d_n.txt", std::ios::out);

	eFile << e << "\n" << n;
	dFile << d << "\n" << n;

	eFile.close();
	dFile.close();

	std::cout << "Program Execution Complete";

	// Utility code for my IDE (keeps console from closing)
	char hold;
	std::cin >> hold;

	return 0;
}

// Function that allows BigPrime Generation to be threaded
//(std::promise <BigUnsigned> && p1)
BigUnsigned generateBigPrime(BigUnsigned const & output)
{
	BigUnsigned & temp = const_cast<BigUnsigned &>(output);
	
	while (temp.bitLength() < 512)
		temp = temp * 10 + rand();	// Initalize temp;

	// Test for Primality
	while (!fermatTest(temp))
	{
		// Not a prime number 
		// Generate new number
		temp = 0;
		while (temp.bitLength() < 512) //512
			temp = temp * 10 + rand();
	}

	std::cout << "Thread Complete\n";

	return temp;
}

// A function implementing the Fermat Primality Test
bool fermatTest(BigUnsigned& BigIn)
{
	int rep = 3;					// Number of times to run test (more iterations make false positives less likely)
	int rnd;
	BigUnsigned a;

	// Perform test multiple times
	while (rep > 0)
	{

		BigUnsigned a = 2 + rand();	// Generate random number (unbound)
		while (a >= BigIn)
		{
			a = 2 + rand();			// Ensure a < BigIn	(since % does not work well)
		}

		// Test if a^(n-1) % n == 1
		if (modexp(a, BigIn - 1, BigIn) != 1)
		{
			//std::cout << "Fermat Failure \n";
			return false;
		}

		rnd = 0;
		rep--;
	}

	std::cout << "Fermat Success: " << BigIn << " is Prime\n";
	return true;
}