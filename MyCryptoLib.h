// MyCryptoLib.h
#ifndef MYCRYPTOLIB_H
#define MYCRYPTOLIB_H

#include <iostream>
#include <bits/stdc++.h>
#include <cryptopp/gf256.h>
	
using namespace std;
using namespace CryptoPP;

// Function declaration for MAC calculation

GF256::Element calculate_mac(vector<GF256::Element>&block, GF256::Element key,int M);

void find_mac(const char* filePath, vector<GF256::Element> &key);

void calculate_matrix_multiplication(vector<vector<GF256::Element>> &a, vector<vector<GF256::Element>> &c, const char* fileName1,int r,const char* fileName2);

#endif

