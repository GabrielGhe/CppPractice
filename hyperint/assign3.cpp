#include <iostream>
#include <string>
#include <cassert>
#include "hyperint.h"

using namespace std;

/**
* COMP 345 - Assignment #3
* To compile: g++ assign3.cpp hyperint.cpp -o assign3
* Authors: 	Natacha Gabbamonte 6892574
*			Gabriel Gheorghian 5726115
*/

int main(){
	cout << endl << "HYPERINT TEST CLASS" << endl << endl;
	
	// Test #1 - hyperint(long)	
	cout << endl << "TEST: hyperint(long) constructor" << endl;
	hyperint h1(1000);	
	hyperint h2(0);
	
	// Test #2 - cout << hyperint 
	cout << endl << "TEST: hyperint extractor (<<)" << endl;
	cout << h1 << endl;
	
	// Test #3 - bool operator	
	cout << endl << "TEST: bool operator" << endl;
	bool b1 = h1;
	bool b2 = h2;
	assert(b1 && !b2);
	cout << h1 << "=" << b1 << endl << h2 << "=" << b2 << endl;
	
	// Test #4 - equality test
	cout << endl << "TEST: ==, <=, <, >, >=, !=" << endl;
	hyperint h3(122332132);
	hyperint h4(122332133);
	hyperint h5(120332131);
	b1 = (h3 == h3);
	assert(b1);
	b1 = (h3 < h4);
	assert(b1);
	b1 = (h3 <= h4);
	assert(b1);
	b1 = (h3 >= h4);
	assert(!b1);
	b1 = (h3 > h4);
	assert(!b1);
	b1 = (h5 < h4);
	assert(b1);
	b1 = (h3 != h5);
	assert(b1);
	cout << "successful test" << endl;
	
	// Test #5 - Testing +=
	cout << endl << "TEST: +=" << endl;
	hyperint realSum(242664263);
	cout << h3 << " += " << h5 << "  ->";
	h3 += h5;
	assert(h3 == realSum);
	cout << h3 << endl;
	cout << "successful test" << endl;
	
	// Test #6 - Pre increment ++(hyperint)
	hyperint test6(999);
	cout << endl << "TEST: Pre increment ++(hyperint)" << endl;
	cout << ++test6 << " should be = 1000" << endl;

	// Test #7 - Post increment (hyperint)++
	cout << endl << "TEST: Post increment (hyperint)++" << endl;
	cout << test6++ << " should be = 1000" << endl;
	cout << test6 << " should be = 1001" << endl;
	
//	// Test #8 - Testing -=
//	cout << endl << "TEST: -=" << endl;
//	hyperint test8(0);
//	test8 += h4;
//	test8 -= h3;
//	cout << test8 << " should be = 0" << endl;
//	test8 += h3;
//	test8 -= h4;
//	cout << test8 << endl;
//	cout << "successful test" << endl;
//
//	// Test #9 - Testing /=
//	cout << endl << "TEST: /=" << endl;
//	hyperint test9(0);
//	test9 += h4;
//	test9 -= h3;
//	cout << test9 << " should be = 0" << endl;
//	test9 += h3;
//	test9 -= h4;
//	cout << test9 << endl;
//	cout << "successful test" << endl;

	// Test #10 - Testing *=
	cout << endl << "TEST: *=" << endl;
	hyperint test10(0);
	hyperint twenty(20);
	test10 *= h3;
	cout << test10 << " should be = 0" << endl;
	test10 += twenty; //test10 = 0
	test10 += twenty; //test10 = 20
	test10 *= twenty;
	cout << test10 << " should be = 800" <<  endl;
	cout << "successful test" << endl;

	// Test #11 - Testing ^
	cout << endl << "TEST: ^" << endl;
	hyperint test11(0);
	hyperint lastTest(313);
	cout << (test11 ^ twenty) << " should be 0" << endl;
	cout << (twenty ^ test11) << " should be 1"<< endl;
	cout << (lastTest ^ lastTest) << endl;

	// Exit textS
	cout <<  endl << "Exiting..." << endl;
	return 0;
}
