#include <iostream>
#include <string>
#include <iomanip>

#include "Source.h"

using namespace std;

int main(){
	string message = "hello";

	ElGamal source;
	source.encrypt();
	source.decrypt();

	system("pause");
	return 0;
}