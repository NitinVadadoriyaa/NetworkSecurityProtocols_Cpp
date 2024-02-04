#include "MyCryptoLib.h"

int main ()
{
	//***********************I ASUME THAT PROVIDED FILE CONTAIN N * M FULL CHARACTOR -- NO PADDING****************************
	//step - 1
	string fileName;
	cout << "Enter fileName : ";
	cin >> fileName;
	const char* filePath = fileName.c_str();
	
	int key_len;
	cout << "Enter key length : ";
	cin >> key_len;
	vector<GF256::Element> key(key_len);
	for(int i = 0; i < key_len; i++)  {
		int k; cin >> k;
		key[i] = static_cast<GF256::Element>(k);
	}
	find_mac(filePath, key);
	
	//step - 2
	int p,q,r;
	cout << "Enter p, q, and r : ";
	cin >> p >> q >> r;
	vector<vector<GF256::Element>>a(p,vector<GF256::Element>(q,0)); // p * q
	for (int i = 0; i < p; i++) {
		char ele; // char --> int for read integer.....
		for (int j = 0; j < q; j++) {
				cin >> ele;
				a[i][j] = static_cast<GF256::Element>(ele);
				
				//bitset<8>bit(a[i][j]);
				//cout << bit << " ";
		}
		//cout << endl;
	}
	/* string inputFile;
	cout << "Enter file Name : ";
	cin >> inputFile; 
	const char* filePath = inputFile.c_str(); */
	vector<vector<GF256::Element>> c(p,vector<GF256::Element>(r,0)); // p * r
	calculate_matrix_multiplication(a,c,filePath,r,"Output2.bin");
	
	//step - 3
	cout << "Enter p, q, and r : ";
	cin >> p >> q >> r;
	a = vector<vector<GF256::Element>>(p,vector<GF256::Element>(q,0));
	for (int i = 0; i < p; i++) {
		char ele; // char --> int for read integer.....
		for (int j = 0; j < q; j++) {
				cin >> ele;
				a[i][j] = static_cast<GF256::Element>(ele);
				
				//bitset<8>bit(a[i][j]);
				//cout << bit << " ";
		}
		//cout << endl;
	}
	c = vector<vector<GF256::Element>>(p,vector<GF256::Element>(r,0));
	calculate_matrix_multiplication(a,c,"Output1.bin",r,"Output3.bin");
	
	//step - 4
	find_mac("Output2.bin", key);
	
	return 0;
}
