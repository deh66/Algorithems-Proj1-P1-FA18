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

//Part I : RSA key generation.
//	Implement Fermat test; X
//	Use Fermat�s test to generate two large prime numbers(p, q), each should have a size >= 512 bits;
//	Save p and q in a file named p_q.txt, one integer per line and making sure no white space saved;
//	Use extended Euclidean algorithm to generate two pairs of keys : (e, n), (d, n), where n = p * q;
//	Save the two pairs of keys in two separate files : e_n.txt and d_n.txt, one integer per line and no white space;
//              //

bool fermatTest(BigUnsigned&);
//void generateBigPrime(BigUnsigned const &);

int main(){
	//tmp
	int minBitLength = 512;	// Minimum for submission: 512
	
	// Inform User
	std::cout << "Program starting" << "\n";
	
	// Set rand() function seed to current time to actually randomize key generation between program iterations
	srand(time(NULL));

	// Generate 2 Big numbers ( 512 Bits or greater )
	BigUnsigned p;
	BigUnsigned q;
	BigUnsigned temp;

	while (temp.bitLength() < minBitLength)
		temp = temp * 10 + rand();	// Initalize temp;

	// User feedback
	std::cout << "Generating p and q" << "\n";

	// Test for Primality
	while (!fermatTest(temp))
	{
		// Not a prime number 
		// Generate new number
		temp = 0;
		while (temp.bitLength() < minBitLength)//512
			temp = temp * 10 +rand();
	}
	// Assign new large prime number to p
	p = temp;

	// User feedback
	std::cout << "p generated, generating q" << "\n";

	// Generate second large prime number
	temp = 0;
	while (temp.bitLength() < minBitLength)
		temp = temp * 100 + rand();	// Initalize temp

	// Test for Primality
	while (!fermatTest(temp))
	{
		// Not a prime number 
		// Generate new number
		temp = 0;
		while (temp.bitLength() < minBitLength)//512
			temp = temp * 10 +rand();
	}
	// Assign second new large prime number to q
	q = temp;

	// User feedback
	std::cout << "q generated" << "\n";

	// Malfunctioning and abandoned threading code
	//p = rand() % 10;
	//q = rand() % 10;

	//// Generate two large prime numbers (p, q)
	//std::thread genOne(generateBigPrime, std::ref(p));
	//std::thread genTwo(generateBigPrime, std::ref(q));
	//
	//genOne.join();
	//genTwo.join();

	// Output Testing //
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
	while (e.bitLength() < 100)	// use minBitLength?
		e = e * 10 + rand();

	// Test if nPhi and e are relatively prime
	while (gcd(nPhi, e) != 1)
	{
		e = rand();
		while (e.bitLength() < 100)	// use minBitLength?
			e = e * 10 + rand();
		while (e >= nPhi)
			e = rand();
	}

	std::cout << "e Generated" << "\n";
	std::cout << "e: " << e << "\n";

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

	std::cout << "d Generated" << "\n";
	std::cout << "d: " << d << "\n";

	//std::cout << "d generated: " << d << "\n";

	// Print e and d to seperate files
	std::fstream eFile;
	std::fstream dFile;

	eFile.open("e_n.txt", std::ios::out);
	dFile.open("d_n.txt", std::ios::out);

	eFile << e << "\n" << n;
	dFile << d << "\n" << n;

	eFile.close();
	dFile.close();

	std::cout << "RSA Key Generation Complete\n";

	//// Utility code for my IDE (keeps console from closing)
	//char hold;
	//std::cout << "Enter character and press enter to complete execution (end program):\n";
	//std::cin >> hold;

	return 0;
}

//// Function that allows BigPrime Generation to be threaded
//void generateBigPrime(BigUnsigned const & output)
//{
//	BigUnsigned & temp = const_cast<BigUnsigned &>(output);
//
//	int modifier = output.toInt();
//	
//	while (temp.bitLength() < 512)
//		temp = temp * modifier + rand();	// Initalize temp;
//
//	// Test for Primality
//	while (!fermatTest(temp))
//	{
//		// Not a prime number 
//		// Generate new number
//		temp = rand();
//		while (temp.bitLength() < 512)
//			temp = temp * 10 + rand();
//	}
//
//	//std::cout << "Thread Complete\n";
//
//	return;
//}

// A function implementing the Fermat Primality Test
bool fermatTest(BigUnsigned& BigIn)
{
	int rep = 3;					// Number of times to run test (more iterations make false positives less likely)
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
			return false;
		}

		rep--;
	}

	//std::cout << "Fermat Success: " << BigIn << " is Prime\n";
	return true;
}