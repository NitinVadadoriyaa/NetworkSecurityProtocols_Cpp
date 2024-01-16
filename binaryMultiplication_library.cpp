#include <iostream>
#include <cryptopp/gf2n.h>
#include <time.h>

using namespace CryptoPP;
using namespace std;

int main() {
	clock_t t = clock(); // start time
	word w1	= 23;
	size_t  bitLength = 8;
	PolynomialMod2 num1 =  PolynomialMod2(w1,bitLength); 	
	cout << num1 << endl;
	
	word16 w2 = 24;
	PolynomialMod2 num2 = PolynomialMod2(w2,bitLength);
	cout << num2 << endl;
	
	PolynomialMod2 num3 = num1.Times(num2);
	cout <<  num3.Modulo(283) << endl;
	t = clock() - t; // t = end time - start time
	cout << "Execution Time : " << (((double)t / CLOCKS_PER_SEC) * 1e6) << " micro-sec." << endl;
	
    return 0;
}

