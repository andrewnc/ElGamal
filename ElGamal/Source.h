#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h> 
#include <time.h> 
#include <tuple>
#include <sstream>

using namespace std;

class ElGamal
{
public:
	ElGamal();
	~ElGamal();
	int reduce_mod(int value, int n);
	int modular_exp(int base, int power, int mod);
	int get_bit(unsigned number, int index);
	int find_inverse(int num, int mod);
	void encrypt();
	void decrypt();
	int text_to_num(string text);
	string num_to_text(int num);
	int choose_p();
	int choose_a();
	int choose_alpha();
	int generate_beta(int alpha, int a, int p);
private:
	int p;
	int alpha;
	int beta;
	int a;

	int k;
	int r;
	int t;
};

