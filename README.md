ASSIGNMENT-4 : 
	command : 
	--> g++ -c MyCryptoLib.cpp -o MyCryptoLib.o -lcryptopp
	--> g++ -c Matrix_Multiplication_gf256.cpp -o mat.o
	--> g++ mat.o MyCryptoLib.o -o mat -lcryptopp

	step-1: do assignment-3 [you get 'Output1.bin' file]
	step-2: do assignment-4/excersize-1 give input [1 * 17] and assignment_3.pdf file [you get 1 * 8000 [Output2.bin] byte hex]
	step-3: do assignment-4/excersize-2 give input [1 * 17] and Output1.bin (17 * 3 byte) [you get 1 * 3 byte hex]
	step-4: do assignment-3 input (Output2.bin)[1 * 8000] as file and [alpha1,2,3] [you get same result as step-3]
