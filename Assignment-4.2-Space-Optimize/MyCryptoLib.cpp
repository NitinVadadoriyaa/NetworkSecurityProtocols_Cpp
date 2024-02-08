#include "MyCryptoLib.h"

//LAB-ASSIGNMENT-2
GF256::Element calculate_mac(vector<GF256::Element>&block, GF256::Element key,int M)
{
	//gf2256 intialization
	GF256 gf256(0x11B); //100011011 , you can also give input in HEXA form like : 283
	GF256::Element byte = key;
	//std::cout << byte << std::endl;
	GF256::Element mac = 0x00;
	
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

    // Open the file in binary mode
    std::ifstream readFile(filePath, std::ios::binary);
    
    if (!readFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }
    
    // Move the file pointer to the end of the file
    readFile.seekg(0, std::ios::end);
    
    // Get the current position of the file pointer, which represents the total number of bytes
    streampos fileSize = readFile.tellg();
  
  	if (fileSize == -1) {
        std::cerr << "Error getting file size." << std::endl;
    }
    
    
    std::ofstream writeFile("Output1.bin", std::ios::binary);
    if (!writeFile.is_open()) {
        std::perror("Error opening output file");
        return;
    }
    
    //gf2256 intialization
	GF256 gf256(0x11B); //100011011 , you can also give input in HEXA form like : 283
    
	int row = 0;
    while (true) { // i dont know number of rows
	    bool isEndFile = false; // handle end of file.......
    	for (int k = 0; k < key_len; k++) {
	    	int m = 0;
			GF256::Element singleMac = 0x00;
			GF256::Element alpha = key[k];
			
    		while (m < M) {
    			char ele = 0b00000000;
            	std::streampos index = (row * M) + m; // 2D --> 1D indexing...
				if (index < fileSize) { // padding handler...
					readFile.seekg(index); // move file-pointer....
					readFile.read(&ele, 1);	
				} else {
					isEndFile = true;
				}
				
				GF256::Element byte = static_cast<GF256::Element>(ele);
				GF256::Element mul = gf256.Multiply(alpha,byte); // byte * alfa
				singleMac = gf256.Add(mul,singleMac); // a xor mac
				alpha = gf256.Multiply(alpha,key[k]);
				
				m++;
    		}
    		
    		writeFile.write(reinterpret_cast<const char*>(&singleMac), sizeof(GF256::Element));
    		cout << hex << setw(2) << setfill('0') << static_cast<int>(singleMac);
				if (key_len - k != 1) cout << "::";
    	}
    	
    	cout << endl;
    	row++;
    	if (isEndFile || ((row * M) == fileSize) ) {
    		break;
    	}
    }
    readFile.close();
    writeFile.close();
    return;
}

//LAB-ASSIGNMENT-4
void calculate_matrix_multiplication(vector<vector<GF256::Element>> &a, const char* filePath,int r,const char* fileName) { // fileName -> output file
	int p,q;
	p = a.size();
	q = a[0].size();
	
	// Open the file in binary mode
    std::ifstream readFile(filePath, std::ios::binary);
    if (!readFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    GF256 gf256(0x11B); //100011011 , you can also give input in HEXA form like : 283
    std::ofstream writeFile(fileName, std::ios::binary);
    if (!writeFile.is_open()) {
        std::perror("Error opening output file");
        return;
    }
    
    // Move the file pointer to the end of the file
    readFile.seekg(0, std::ios::end);
    
    // Get the current position of the file pointer, which represents the total number of bytes
    streampos fileSize = readFile.tellg();
  
  	if (fileSize == -1) {
        std::cerr << "Error getting file size." << std::endl;
    }
    
    
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j) {
        	GF256::Element sum = 0x00;
            for (int k = 0; k < q; ++k) {
            
            	char ele = 0b00000000;
            	std::streampos index = (k * r) + j; // 2D --> 1D indexing...
				if (index < fileSize) {
					readFile.seekg(index); // move file-pointer....
					readFile.read(&ele, 1);
				}
           
                GF256::Element mul = gf256.Multiply(a[i][k], static_cast<GF256::Element>(ele) );
                sum = gf256.Add(mul,sum);
            }
            writeFile.write(reinterpret_cast<const char*>(&sum), sizeof(GF256::Element)); // write on file
            cout << hex << setw(2) << setfill('0') << static_cast<int>(sum);
			if (r - j != 1) cout << "::";
		}
		cout << endl;
    }
    
	return;
}
