#include <iostream>
#include <fstream>
#include <sstream>
#include <cryptopp/gf256.h>
#include <time.h>
#include <bitset>

using namespace std;
using namespace CryptoPP;
#define M 5
#define N 2

int calculate_mac(vector<int>&block, int key)
{
	//gf2256 intialization
	GF256 gf256(283); //100011011 , you can also give input in HEXA form like : 0x8B
	GF256::Element a; 
	GF256::Element b = key;
	GF256::Element mac = 0;
	
    	for (int i = 0; i < M; i++) {
	        //std::cout << "Read byte: " << static_cast<unsigned int>(static_cast<unsigned char>(byte)) << std::endl;
	        int num = block[i];
	        if (num == 10) continue; // 10 -- end of line

	        a = num;
	        a = gf256.Multiply(a,b); // b * alfa
	        mac = gf256.Add(a,mac); // a xor mac
	        b = gf256.Multiply(b,key);
    }
    return mac;
}
int main() {    
	vector<vector<int>>mat(N,vector<int>(M));
	char byte;
	int m = 0;
	int n = 0;
	vector<int>key = {5,1,3};
	
	 const char* filePath = "example_1.txt";

    // Open the file in binary mode
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }
    
	 while (file.get(byte)) {
	 if (byte == '\n') break;
	 	if (m == M) {
		 	n++;
	 		m = 0;
	 	}
	 	mat[n][m] = byte - 0;
	 	m++;
    }
    
    
    for (int b = 0; b < N; b++) {
    	int i = 0;
    	for (int k = 0; k < key.size(); k++) {
    		int result = calculate_mac(mat[b],key[k]);
    		bitset<8> bit_mac (result);
    		cout << bit_mac << " ";
    	}
    	cout <<  endl;
    }
    
    return 0;
}

