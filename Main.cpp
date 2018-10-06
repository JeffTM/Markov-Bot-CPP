#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "MarkovText.h"
#include "Tokenizer.h"
using namespace std;

template<class T>
void printSMatrix(const SMatrix<T> & x)
{
	for (size_t i = 0; i < x.side(); ++i)
	{
		for (size_t j = 0; j < x.side(); ++j)
			cout << x.get(i, j) << ' ';
		cout << endl;
	}
}

int main()
{
	/*
	//SMatrix test
	SMatrix<short> a(16, 0);
	for (size_t i = 0; i < a.side(); ++i)
	a.set(i, i, 1);
	printSMatrix(a);
	a.resize(4);
	printSMatrix(a);
	a.resize(8);
	printSMatrix(a);
	a.resize(13, 7);
	printSMatrix(a);
	SMatrix<short> b(a);
	printSMatrix(b);
	SMatrix<short> c;
	c = b;
	printSMatrix(c);
	cout << endl;
	*/
	
	string file("jerry2.txt");
	vector<string> tokens;
	Tokenizer tokenizer;
	unsigned int seed = unsigned int(std::chrono::system_clock::now().time_since_epoch().count());
	//mt19937 gen(0);
	mt19937 gen(seed);
	MarkovText bot;

	tokenizer(file, tokens);
	cout << "Tokens:" << endl;
	for (const string & s : tokens)
		cout << s << ';' << endl;
	cout << endl;
	bot.build(tokens);
	cout << "Seed: " << seed << endl;
	cout << endl;
	cout << "Result:" << endl;
	cout << endl << bot.generate(gen, 4) << endl << "by Computer" << endl << endl;
	for (int i = 0; i < 16; ++i)
		cout << bot.generateUntil(gen, '.', 20) << endl;
	cout << endl;

	cout << "Press any key to continue . . . ";
	cin.get();
	return 0;
}
