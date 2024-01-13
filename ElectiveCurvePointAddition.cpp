#include <iostream>
#include <cryptopp/integer.h>
#include <cryptopp/ecp.h>
#include <cryptopp/eccrypto.h>

using namespace CryptoPP;
using namespace std;

int main() {

   Integer prime(13);
   ECP::FieldElement a(1), b(1);
   ECP ecp(prime, a, b);
   
   
   ECP::Point P(4, 2);
   if (ecp.VerifyPoint(P) == false) {
   		cout << "P - Point is not valid" << endl;
   		return 0;
   }
   
   ECP::Point Q(10,6);
   if (ecp.VerifyPoint(Q) == false) {
   		cout << "Q - Point is not valid" << endl;
   		return 0;
   }
   
   
   ECP::Point R;
   R = ecp.Add(P,Q);
   
   
   /* int d;
   cin >> d;
   ECP::Point res = P;
   for (int i = 1; i <= d; i++ ) {
   		res = ecp.Add(res,P);
   }
   
  cout << "(" << res.x <<" " << res.y << ")" << endl;
  
   ECP::Point mul;
   mul = ecp.ScalarMultiply(P,d);
   cout << "(" << res.x <<" " << res.y << ")" << endl;  */
   
   cout << "(" << R.x <<" " << R.y << ")" << endl;
   return 0;
}
