#include <iostream>
#include <fstream>
#include <sstream>
#include <cryptopp/gf256.h>
#include <time.h>
#include <bitset>

using namespace std;
using namespace CryptoPP;

int main() {    
	clock_t t = clock(); // start time
    const char* filePath = "example.txt";

    // Open the file in binary mode
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }
	
	//gf2256 intialization
	GF256 gf256(283); //100011011 , you can also give input in HEXA form like : 0x8B
	GF256::Element a; 
	GF256::Element key = 15;  // secreate key
	GF256::Element b = key;
	GF256::Element mac = 0;
	
    // Read the file byte-wise
    char byte;
    while (file.get(byte)) {
    	
	        //std::cout << "Read byte: " << static_cast<unsigned int>(static_cast<unsigned char>(byte)) << std::endl;
	        int num = byte - 0;
	        if (num == 10) continue; // 10 -- end of line
	        cout << num << endl;
	        a = num;
	        a = gf256.Multiply(a,b); // b * alfa
	        mac = gf256.Add(a,mac); // a xor mac
	        b = gf256.Multiply(b,key);
    }
    bitset<8> bit_mac (mac);
    cout << "file mac is : " << bit_mac << endl;

    file.close();

	t = clock() - t; // t = end time - start time
	cout << "Execution Time : " << (((double)t / CLOCKS_PER_SEC)) << " sec." << endl;
	
    return 0;
}

