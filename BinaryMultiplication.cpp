#include<bits/stdc++.h>
using namespace std;
#define BIT 9

bitset<BIT> r1("100011011"); // prime
int MSB = 8;

void getMsb(bitset<BIT> &r, bitset<BIT> &r2, short int &r1Msb, short int &r2Msb) {
    for (int i = 0; i < BIT; i++) {
        //in built indexing calculate from right to left, ... 3,2,1,0
        if (r.test(i)) r1Msb = i;
        if (r2.test(i)) r2Msb = i;
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

int main() {
	bitset<BIT> q("1001010");
	bitset<BIT> p("1001010");
	bitset<BIT> result;
   
    binaryMultiplication(q, p,result) ;
    cout << "Multiplication : " << result;
    return 0;
}
