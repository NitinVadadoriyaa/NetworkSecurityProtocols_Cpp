#include "MyCryptoLib.h"

int main() {
	clock_t t = clock();
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
	
	t = clock() - t; // t = end time - start time
    cout << "Execution Time : " << (((double)t / CLOCKS_PER_SEC)) << " sec." << endl;
	return 0;
}
