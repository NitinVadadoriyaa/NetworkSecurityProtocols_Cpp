#include <bits/stdc++.h>
#include <time.h>
using namespace std;

#define BIT 32 // total bits for represent poly.
#define MSB 8 // degree(prime poly.)

bitset<BIT> r1("100011011"); // irreducable prime polynomial
bitset<BIT> r2("001");

void getMsb(bitset<BIT> &r1, bitset<BIT> &r2, short int &r1Msb, short int &r2Msb) {
    for (int i = 0; i < BIT; i++) {
        //in built indexing calculate from right to left, ... 3,2,1,0
        if (r1.test(i)) r1Msb = i;
        if (r2.test(i)) r2Msb = i;
    }
}

void binaryDivision(bitset<BIT> &r1, bitset<BIT> &r2, bitset<BIT> &q,bitset<BIT> &r) {
    short int r1Msb, r2Msb;
    r = r1; // resultant reminder
    
    getMsb(r,r2,r1Msb,r2Msb);
    while  ((r.any()) && (r1Msb >= r2Msb)) { // stop, {r == 0 or r1Msb < r2Msb}
    	q.set(r1Msb - r2Msb);
    	bitset<BIT> tempR2 = r2; 
    	tempR2 = tempR2 << (r1Msb - r2Msb);
    	r = tempR2 ^ r; // final reminder 
    	getMsb(r,r2,r1Msb,r2Msb);
    }
}

void binaryMultiplication(bitset<BIT> &q, bitset<BIT> &t2, bitset<BIT> &result) {
    short int MsbQ, msbIndexOfPrime;
    getMsb(q, t2, MsbQ,msbIndexOfPrime);
    vector<bitset<BIT>>table(MsbQ + 1);
    table[0] = t2;
    for (int i = 1; i <= MsbQ; i++) {
        table[i] = table[i - 1] << 1;
        if (table[i].test(MSB)) {
            table[i] = table[i] ^ r1;
        }
    }
   
    for (int i = 0; i < BIT; i++) {
        if (q.test(i)) {
            result = (result xor table[i]);
        }
    }
}

void Extended_euclidean(bitset<BIT> r1, bitset<BIT> r2) {
	bitset<BIT>t1(0); // intialy 0 value
	bitset<BIT>t2(1); // intialy 1 value
	while (r2.any()) {
        bitset<BIT> q(0);
        bitset<BIT> r(0);
        bitset<BIT> t(0);
		binaryDivision(r1,r2,q,r);
        
		bitset<BIT>result(0);
		binaryMultiplication(q,t2,result);
		t = t1 xor result;
    
		r1 = r2;
		t1 = t2;
		r2 = r;
		t2 = t;
	}
	if (r1.test(0)) {
        cout << "Multiplicative inverse : " << t1 << endl;
    } else {
        cout << "Multiplicative inverse not exit!" << endl;
    }
}

int main() {
	string input;
	
	cin >> input;
	bitset <32> r2(input);
	
	clock_t t = clock(); // start time
	Extended_euclidean(r1,r2);
	t = clock() - t; // t = end time - start time
	cout << "Execution Time : " << (((double)t / CLOCKS_PER_SEC) * 1e6) << " micro-sec." << endl;
}
