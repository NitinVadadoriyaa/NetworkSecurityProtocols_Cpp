#include <iostream>
#include <bitset>
#include <cryptopp/gf256.h>
#include <time.h>

using namespace CryptoPP;
using namespace std;

int main()
{
	clock_t t = clock(); // start time
    GF256 gf256(283); //100011011 , you can also give input in HEXA form like : 0x8B
	
	bitset<8>b1;
    cout << "Enter binary string: ";
	cin >> b1;
	GF256::Element a = b1.to_ulong();
    GF256::Element inverse = gf256.MultiplicativeInverse(a);
    
    std::bitset<8 * sizeof(CryptoPP::GF256::Element)> bit_Inverse(inverse);
    std::cout << "inverse in binary: " << bit_Inverse << std::endl;
    
    t = clock() - t; // t = end time - start time
	cout << "Execution Time : " << (((double)t / CLOCKS_PER_SEC)) << " sec." << endl;
	
	return 0;
}
