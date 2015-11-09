#include "Source.h"


ElGamal::ElGamal()
{
	p = choose_p();
	alpha = choose_alpha();
	a = choose_a();
	beta = generate_beta(alpha,a,p);
}


ElGamal::~ElGamal()
{
}

int ElGamal::find_inverse(int a, int m){
		a %= m;
		for (int x = 1; x < m; x++) {
			if ((a*x) % m == 1) return x;
		}

}
int ElGamal::text_to_num(string text){
	//char alpha[] = "abcdefghijklmnopqrstuvwxyz";
	//std::vector<char> alphabet(alpha, alpha + sizeof(alpha) - 1);
	//vector<int> chars;
	//vector<char> characters;
	//stringstream ss;
	//string value;
	//int summ = 0;
	//for (int i = 0; i < text.length(); i++){
	//	char cMyCharacter = text[i];
	//	int iMyAsciiValue = static_cast<int>(cMyCharacter);
	//	chars.push_back(iMyAsciiValue);
	//}
	//for (int i = 0; i < chars.size(); i++){
	//	summ += (int)chars[i];
	//}
	//cout << summ << endl;
	//return summ;
	int num = 0;
	for (int i = 0; i < text.length(); i++){
		num *= 100;
		num += (int)text[i];
	}
	return num;
	//char message = text;
}

string ElGamal::num_to_text(int num){
	char message = static_cast<char>(num);
	stringstream ss;
	string something;
	char charac;
	while (num > 0){
		charac = (num % 100);
		something = charac + something;
		num = (num - (int)charac) / 100;
	}
	return something;
}

int ElGamal::reduce_mod(int value, int n)
{
	if (value == n){
		return 0;
	}
	int reduced_value;
	if (value > n){
		while (value > n){
				value = value - n;
		}
	}
	else if (value < 0){
		while (value < 0){
			value = value + n;
		}
	}
	reduced_value = value;
	if (reduced_value == n){
		return 0;
	}

	return reduced_value;
}

int ElGamal::get_bit(unsigned number, int index)
{
	unsigned mask = 0x01 << index;
	int bit = number & mask;
	return bit;

}

int ElGamal::modular_exp(int base, int power, int mod)
{
	//find binary expansion of base
	// multiply the decimal position of binary expansion, reduce mod
	vector<int> values;
	int multi = 1;
	int square_pow = 2;
	while (square_pow <= power){
		values.push_back(base);
		base = pow(base, 2);
		base = reduce_mod(base, mod);
		square_pow *= 2;
	}
	values.push_back(base);
	values.push_back(1);

	int return_value = 0;
	for (int i = 0; i <= values.size(); i++){
		return_value = get_bit(power, i);
		if (return_value != 0){
			multi *= values[i];
			multi = reduce_mod(multi, mod);
		}
	}
	return multi;
}

void ElGamal::encrypt()
{
	//choose a secret random integer k, and compute r congruent alpha^k mod p
	//compute t congruent beta^k*m mod p where m is your message enumerated.
	//return the pair (r, t)
	int k;
	string text;
	int m;
	cout << "Choose K: ";
	cin >> k;
	cout << "What is your message? ";
	cin >> text;
	m = text_to_num(text);
	r = modular_exp(alpha, k, p);
	t = modular_exp(beta, k, p)*m;
	cout << "( " << r << ", " << t << " )" << endl;

}

void ElGamal::decrypt()
{
	//compute t*r^-a congruent to m mod p
	//this works because t*r^-a = beta^k*m(a^k)^-a = (alpha^a)^k*m*alpha^(-a*k) = m mod p
	int inverse = find_inverse(a, p);
	int answer = t*modular_exp(r, inverse, p);
	cout << num_to_text(answer) << endl;
}

int ElGamal::choose_alpha()
{
	bool isPrimRoot = false;
	while (isPrimRoot != true){
		cout << "Enter Alpha: ";
		cin >> alpha;
		for (int i = 1; i < p; i++){
			if (modular_exp(alpha, i, p) == 1 & reduce_mod(i, p - 1) == 0){
				isPrimRoot = true;
			}
			else{
				}
		}
	}


	return alpha;
	//return 1;
	//Alpha is a primitive root mod p, so we need to do a primitive root check on alpha when we've generated it
}

int ElGamal::choose_a()
{
	cout << "Enter A: ";
	cin >> a;
	return a;
	//a is simply a secret random integer
}

int ElGamal::choose_p()
{
	int p;
	bool isPrime = false;
	while (isPrime != true){
		cout << "Enter P value: ";
		cin >> p;
		//this uses fermat's little theorem to check if the given value is prime.
		if (modular_exp(2, p - 1, p) == 1){
			isPrime = true;
		}
		else{
			cout << "Not Prime!" << endl;
		}
	}


	return p;
	//return 1;
	//we need to choose a large prime p, or at least, a normal sized prime. So here we will choose that prime
}

int ElGamal::generate_beta(int alpha, int a, int p)
{
	//beta is alpha^a mod p.
	int beta = 1;
	beta = modular_exp(alpha, a, p);
	return beta;
}