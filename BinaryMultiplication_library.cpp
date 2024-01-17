#include <iostream>
#include <cryptopp/gf2n.h>
#include <time.h>
#include <bitset>

using namespace CryptoPP;
using namespace std;

int main() {
	clock_t t = clock(); // start time
	size_t  bitLength = 8;
	bitset<8>b1;
	bitset<8>b2;
	cout << "Enter first binary string: ";
	cin >> b1;
	cout << "Enter second binary string: ";
	cin >> b2;
	word w1((int)b1.to_ulong()); // binary string -> int, int -> word
	word w2((int)b2.to_ulong());
	PolynomialMod2 num1 =  PolynomialMod2(w1,bitLength); 	
	cout << num1 << endl;
	
	PolynomialMod2 num2 = PolynomialMod2(w2,bitLength);
	cout << num2 << endl;
	
	PolynomialMod2 num3 = num1.Times(num2);
	cout <<  num3.Modulo(283) << endl;
	
	t = clock() - t; // t = end time - start time
	cout << "Execution Time : " << (((double)t / CLOCKS_PER_SEC)) << " sec." << endl;
	
    return 0;
}

