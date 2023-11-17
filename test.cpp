#include <iostream>
#include <sstream>
#include <functional>
#include "Polynomial.h"
#include <string.h>

template<typename A, typename B>
void assertEqual(const A& a, const B& b, const std::string& hint) {
	if(a != b) {
		std::ostringstream os;
		os << "Failed: " << a << "!=" << b << " Hint: " << hint;
		throw std::runtime_error(os.str());
	}
}

void testConstructors() {
	{
		Polynomial p;
		assertEqual(p.getDegree(), 0u, "Error: default constructor (get degree method)");
		assertEqual(p.getSize(), 0u, "Error: default constructor (get size method)");
	}

	{
		Polynomial p(5);
		assertEqual(p.getDegree(), 5u, "Polynomial degree");
		for (unsigned int i = 0; i < p.getSize(); i++) {
			assertEqual(p.coefficientAt(i), 0, "Error: constructor with one parameter");
		}
	}

	{
		const int values[] = { 1, 2, 3, 4 };
		Polynomial p(5, values);
		for (unsigned int i = 0; i < p.getSize(); i++) {
			assertEqual(p.coefficientAt(i), values[i], "Error: constructor with two parameters" + std::to_string(i));
		}
	}

	{
		const int values[] = { 1, 2, 3, 4 };
		Polynomial p1(5, values);
		Polynomial p2(p1);
		for (unsigned int i = 0; i < p2.getSize(); i++) {
			assertEqual(p2.coefficientAt(i), p1.coefficientAt(i), "Error: copy constructor" + std::to_string(i));
		}
	}
	
	std::cout << "Test Constructors OK" << std::endl;
}

void testCoefficients() {
	{
		const int degree = 10;
		const int size = degree + 1;
		Polynomial p(degree);
		int values[size];
		for (int i = 0; i < size; i++)
			values[i] = i;	

		for (int i = 0; i < size; i++)
			p.coefficientInsert(i, values[i]);

		for (unsigned int i = 0; i < p.getSize(); i++)
			assertEqual(p.coefficientAt(i), values[i], "Error: coefficient insertion at index" + std::to_string(i));
	}

	{
		try {
			Polynomial p;
			p.coefficientInsert(10, 5);
 		} catch (const std::runtime_error& ex) {
			assertEqual(strcmp(ex.what(), "Error: index exceed coefficients array size"), 0, "Accessing value with index out of range");
		}
	}
	std::cout << "Test Coefficients OK" << std::endl;
}

void testSum() {
	{
		Polynomial p1();
	}
}

void testAll() {
	std::vector<std::function<void()>> tests = {
		testConstructors,
		testCoefficients
	};
	static unsigned int counter = tests.size();
	for (auto& test : tests) {
		try {
			test();
		} catch (const std::runtime_error& ex) {
			counter--;
			std::cout << ex.what() << std::endl;
		}
	}
	std::cout << "***\n" << "\tDONE " << counter << "/" << tests.size() << " TESTS SUCCESSFULLY" << "\n***" << std::endl;
}
