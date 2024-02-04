#include "MyCryptoLib.h"
int M;

GF256::Element calculate_mac(vector<GF256::Element>&block, GF256::Element key)
{
	//gf2256 intialization
	GF256 gf256(283); //100011011 , you can also give input in HEXA form like : 0x11B
	GF256::Element byte = key;
	//std::cout << byte << std::endl;
	GF256::Element mac = 0;
	
    	for (int i = 0; i < M; i++) {
	        //std::cout << "Read byte: " << static_cast<unsigned int>(static_cast<unsigned char>(byte)) << std::endl;
	GF256::Element a;
	               
	        a = gf256.Multiply(block[i],byte); // byte * alfa
	        mac = gf256.Add(a,mac); // a xor mac
	        byte = gf256.Multiply(byte,key);
    }
    return mac;
}

void find_mac(const char* filePath, vector<GF256::Element> &key) {
	int key_len = key.size();
	cout << "Enter block size (in segment) : ";
	cin >> M;
	vector<GF256::Element>row(M,0);
	char byte = 0b00000000;
	int m = 0;

    // Open the file in binary mode
    std::ifstream readFile(filePath, std::ios::binary);

    if (!readFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }
    
    std::ofstream writeFile("Output.bin", std::ios::binary);
    if (!writeFile.is_open()) {
        std::perror("Error opening output file");
        return;
    }

	  while (readFile.get(byte))  {
	 	if (m == M) { // making dynemic :=> create vector<int>row(M) :=> vector to mat.push_back(row).
	 		m = 0;
	 		
	 		for (int k = 0; k < key_len; k++) {
				GF256::Element result = calculate_mac(row,key[k]);
				writeFile.write(reinterpret_cast<const char*>(&result), sizeof(GF256::Element));
				
				cout << hex << setw(2) << setfill('0') << static_cast<int>(result);
				if (key_len - k != 1) cout << "::";
			}
			cout <<  endl;
			row.resize(M,0);
	 	}
	 	row[m] = static_cast<GF256::Element>(byte);
	 	m++;
    }
    if (m != 0) {
    	for (int k = 0; k < key_len; k++) {
				GF256::Element result = calculate_mac(row,key[k]);
				writeFile.write(reinterpret_cast<const char*>(&result), sizeof(GF256::Element));
				
				cout << hex << setw(2) << setfill('0') << static_cast<int>(result);
				if (key_len - k != 1) cout << "::";
			}
    }
    cout << endl;
    readFile.close();
    writeFile.close();
}
