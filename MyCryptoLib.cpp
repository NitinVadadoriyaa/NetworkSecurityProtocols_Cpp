#include "MyCryptoLib.h"

//LAB-ASSIGNMENT-2
GF256::Element calculate_mac(vector<GF256::Element>&block, GF256::Element key,int M)
{
	//gf2256 intialization
	GF256 gf256(0x11B); //100011011 , you can also give input in HEXA form like : 283
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

//LAB-ASSIGNMENT-3
void find_mac(const char* filePath, vector<GF256::Element> &key) {
	int key_len = key.size();
	int M;
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
    
    std::ofstream writeFile("Output1.bin", std::ios::binary);
    if (!writeFile.is_open()) {
        std::perror("Error opening output file");
        return;
    }
	int cnt = 0;
	  while (readFile.get(byte))  {
	 	if (m == M) { // making dynemic :=> create vector<int>row(M) :=> vector to mat.push_back(row).
	 		m = 0;
	 		for (int k = 0; k < key_len; k++) {
				GF256::Element result = calculate_mac(row,key[k],M);
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
    	for (m; m < M; m++) {
    		row[m] = 0x0A; // padding..
    	}
    	for (int k = 0; k < key_len; k++) {
				GF256::Element result = calculate_mac(row,key[k],M);
				writeFile.write(reinterpret_cast<const char*>(&result), sizeof(GF256::Element));
				
				cout << hex << setw(2) << setfill('0') << static_cast<int>(result);
				if (key_len - k != 1) cout << "::";
			}
    }
    cout << endl;
    readFile.close();
    writeFile.close();
    return;
}

//LAB-ASSIGNMENT-4
void calculate_matrix_multiplication(vector<vector<GF256::Element>> &a, vector<vector<GF256::Element>> &c, const char* filePath,int r,const char* fileName) { // fileName -> output file
	int p,q;
	p = a.size();
	q = a[0].size();
	
	// Open the file in binary mode
    std::ifstream readFile(filePath, std::ios::binary);
    if (!readFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }
    vector<vector<GF256::Element>>b(q,vector<GF256::Element>(r,0x0A)); // q * r
    for (int i = 0; i < q; i++) {
		char ele = 0b00000000;
		bool check = false;
		for (int j = 0; j < r; j++) {
		
				if (readFile.get(ele)) {  // read from file...
					b[i][j] = static_cast<GF256::Element>(ele);
					
				} else {
					check = true;
					break;
				}
				//bitset<8>bit(b[i][j]);
				//cout << bit << " ";
		}
		if (check) break;
		//cout << endl;
	}
    GF256 gf256(0x11B); //100011011 , you can also give input in HEXA form like : 283
    std::ofstream writeFile(fileName, std::ios::binary);
    if (!writeFile.is_open()) {
        std::perror("Error opening output file");
        return;
    }
    
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j) {
            for (int k = 0; k < q; ++k) {
                GF256::Element mul = gf256.Multiply(a[i][k],b[k][j]);
                c[i][j] = gf256.Add(mul,c[i][j]);
            }
            writeFile.write(reinterpret_cast<const char*>(&c[i][j]), sizeof(GF256::Element)); // write on file
            cout << hex << setw(2) << setfill('0') << static_cast<int>(c[i][j]);
			if (r - j != 1) cout << "::";
		}
		cout << endl;
    }
    
	return;
}
