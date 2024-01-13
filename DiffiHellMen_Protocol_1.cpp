#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/nbtheory.h>

#define PORT 8000
using namespace std;
using namespace CryptoPP;

Integer p(-1);
Integer g(2);
Integer RecieverPublicKey(-1);
Integer SenderPrivateKey(-1);
Integer SenderPublicKey;

Integer GeneratePrime(int size)
{
	AutoSeededRandomPool rng;
	Integer prime;

	// Generate a random 1024-bit number and make sure it's odd
	do
	{
		prime.Randomize(rng, size);
		prime.SetBit(0); // Set the least significant bit to 1
	} while (!RabinMillerTest(rng,prime,(unsigned int)10)); // Perform 5 rounds of Miller-Rabin test

	return prime;
}


string IntgerToString(Integer p) {
	string str = "";
	while (p != 0) {
		int r = p % 10;
		p = p / 10;
		str = to_string(r) + str;
	}

	return str;
}


void Start_Server() {
	int server_fd, addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024];

	if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	while (1) {
		memset(buffer,0,sizeof(buffer));
		ssize_t recv_len = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen);
		if (recv_len == -1) {
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		Integer temp(buffer);
		if (p == -1) {
			p = temp;
			cout <<"Prime Modulo is recieved : " << temp << endl;  
 
		} else {
			RecieverPublicKey = temp;
			cout<<"Reciever public key is recieved : " << temp << endl;  
			break;
		}
	}

	close(server_fd);
}

void Send_msg(const char *server_ip) {
	int client_fd;
	struct sockaddr_in serv_addr;
	if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		return;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
		perror("inet_pton");
		return;
	}


	// Generate 1024-bit prime numbers for the public parameters
	AutoSeededRandomPool rng;
	int size;
	cout << endl << "Enter size of prime number (bits) : ";
	cin >> size;
	
	if(p == -1) {
		p = GeneratePrime(size);
		//cout << "Enter prime modulo : " ;
	//		cin >> p;

		std::string prime_string = IntgerToString(p);

		sendto(client_fd, prime_string.c_str(), prime_string.length(), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		cout <<"Prime-number sent.. " << p << endl;

	}

	while (SenderPrivateKey <= 0 || SenderPrivateKey >= p) {
		SenderPrivateKey.Randomize(rng, size);
	}
	
	SenderPublicKey = a_exp_b_mod_c(g, SenderPrivateKey, p);
	
	//cout << endl << "Enter Your Private Key : ";
	//	cin >> SenderPrivateKey;
	//SenderPublicKey = a_exp_b_mod_c(g, SenderPrivateKey, p);
	cout <<"My private Key : " << SenderPrivateKey << endl;
	
	
	std::string str = IntgerToString(SenderPublicKey);
	sendto(client_fd, str.c_str(), str.length(), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	cout <<"My public Key sent.. " << SenderPublicKey << endl;

	close(client_fd);
}

int main() {
	std::thread serverThread(Start_Server);

	std::string IP;
	std::cout << "server IP : ";
	std::cin >> IP;
	cout << endl;

	Send_msg(IP.c_str());

	while (RecieverPublicKey == -1) {} // WAITING FOR RECIVER PUBLIC KEY

	serverThread.join();

	cout << endl << "Shared Private key : " << a_exp_b_mod_c(RecieverPublicKey,SenderPrivateKey,p) << endl;

	return 0;
}
