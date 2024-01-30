#include <iostream>
#include <bits/stdc++.h>
#include <cryptopp/gf256.h>

using namespace std;
using namespace CryptoPP;

int M;

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
	        
	        a = num;
	        a = gf256.Multiply(a,b); // b * alfa
	        mac = gf256.Add(a,mac); // a xor mac
	        b = gf256.Multiply(b,key);
    }
    return mac;
}
int main() {    
	vector<vector<int>>mat;
	int key_len;
	cout << "Enter key length : ";
	cin >> key_len;
	int key[key_len];
	for(int i = 0; i < key_len; i++)  cin >> key[i];
	cout << "Enter block size (in segment) : ";
	cin >> M;
	vector<int>row(M,0);
	char byte;
	int m = 0;
	
	 const char* filePath = "example_1.txt";
    // Open the file in binary mode
    std::ifstream file1(filePath, std::ios::binary);

    if (!file1.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }
    
	 while (file1.get(byte)) {
	 if (byte == '\n') continue;
	 	if (m == M) { // making dynemic :=> create vector<int>row(M) :=> vector to mat.push_back(row).
	 		m = 0;
	 		mat.push_back(row);
	 		row.resize(M,0);
	 	}
	 	row[m] = byte - 0;
	 	m++;
    }
    file1.close();
    mat.push_back(row); // add last row...
    int N = mat.size();
    
    // Open the file in binary mode for writing
    std::ofstream file("output_hash.txt", std::ios::binary);
    
     if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    
    for (int b = 0; b < N; b++) { // b => block
    	//cout << "0x";
    	for (int k = 0; k < key_len; k++) {
    		int result = calculate_mac(mat[b],key[k]);
    		bitset<8> bit_mac (result);
    		string data = bit_mac.to_string();
    		data.push_back(' ');
    		file.write(data.c_str(), data.size());
    		
    		cout << std::hex << result;
    		if (key_len - k != 1) cout << " ";
    	}
    	cout <<  endl;
    	string newLine = "\n";
    	file.write(newLine.c_str(), newLine.size());
    }
    file.close();
    
    return 0;
}

