#include <iostream>
#include <bitset>
#include <cryptopp/gf256.h>
#include <time.h>

using namespace CryptoPP;
using namespace std;

int main() {
    clock_t t = clock(); // start time
    GF256 gf256(283); //100011011 , you can also give input in HEXA form like : 0x8B
	
    bitset<8>b1;
	bitset<8>b2;
    cout << "Enter first binary string: ";
	cin >> b1;
	cout << "Enter second binary string: ";
	cin >> b2;
        
    GF256::Element a = b1.to_ulong();
   
    GF256::Element b = b2.to_ulong();
    
    // Addition
    GF256::Element result = gf256.Multiply(a, b);

    // Print in binary
    bitset<8 * sizeof(GF256::Element)> bit_result (result);
    cout << "Multiplication is : " << bit_result << endl;
    
	t = clock() - t; // t = end time - start time
	cout << "Execution Time : " << (((double)t / CLOCKS_PER_SEC)) << " sec." << endl;
	
    return 0;
}

