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
		assertEqual(p.getSize(), 1u, "Error: default constructor (get size method)");
	}

	{
		Polynomial p(5);
		assertEqual(p.getDegree(), 5u, "Polynomial degree");
		for (unsigned int i = 0; i < p.getSize(); i++) {
			assertEqual(p.getCoefficientAt(i), 0, "Error: constructor with one parameter");
		}
	}

	{
		const int size = 5;
		const int values[size] = { 1, 2, 3, 4 };
		Polynomial p(size, values);
		for (auto value : values) {
			static unsigned int i = 0;
			assertEqual(p.getCoefficientAt(i++), value, "Error: constructor with two parameters");
		}
	}

	{
		auto values = { 1, 2, 3, 4 };
		Polynomial p(values);
		for (auto value : values) {
			static unsigned int i = 0;
			assertEqual(p.getCoefficientAt(i++), value, "Error: constructor with initializer list");
		}
	}

	{
		auto values = { 1, 2, 3, 4 };
		Polynomial p1(values);
		Polynomial p2(p1);
		for (unsigned int i = 0; i < p2.getSize(); i++) {
			assertEqual(p2.getCoefficientAt(i), p1.getCoefficientAt(i), "Error: copy constructor" + std::to_string(i));
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
			p.setCoefficientAt(i, values[i]);

		for (unsigned int i = 0; i < p.getSize(); i++)
			assertEqual(p.getCoefficientAt(i), values[i], "Error: coefficient insertion at index" + std::to_string(i));
	}

	{
		try {
			Polynomial p;
			p.setCoefficientAt(10, 5);
 		} catch (const std::runtime_error& ex) {
			assertEqual(strcmp(ex.what(), "Error: index exceed coefficients array size"), 0, "Accessing value with index out of range");
		}
	}
	std::cout << "Test Coefficients OK" << std::endl;
}

void testSum() {
	{
		Polynomial p1({5, 6, 3, 2, 6});
		Polynomial p2({3, 1, 3, 6});

		auto sum = { 8, 7, 6, 8, 6 };
		
		Polynomial result1(addition(p1, p2));
		Polynomial result2 = p1 + p2;

		unsigned int i = 0;
		for (auto value : sum) {
			assertEqual(result1.getCoefficientAt(i), value, "Error: sum operation usign external function");
			assertEqual(result2.getCoefficientAt(i++), value, "Error: sum operation usign external function");
		}
	}
	std::cout << "Test Addition OK" << std::endl;
}

void testSub() {
	{
		Polynomial p1({2, 6, 3, 7, 5});
		Polynomial p2({1, 2, 3, 4});

		auto sub = { 1, 4, 0, 3, 5 };

		Polynomial result = p1 - p2;

		for (auto value : sub) {
			static unsigned int i = 0;
			assertEqual(result.getCoefficientAt(i++), value, "Error: sub operation using class method");
		}
	}

	{
		Polynomial p1({2, 6, 3, 7, 5});
		Polynomial p2({1, 2, 3, 4});

		auto sub = { 1, 4, 0, 3, 5 };

		Polynomial result1(substraction(p1, p2));
		Polynomial result2(p1 - p2);

		for (auto value : sub) {
			static unsigned int i = 0;
			assertEqual(result1.getCoefficientAt(i), value, "Error: sub operation using friend function");
			assertEqual(result2.getCoefficientAt(i++), value, "Error: sub operation using overloaded external function");
		}
	}

	std::cout << "Test Substraction OK" << std::endl;
}

void testMultiply() {
	{
		Polynomial p1({1, 2, -1});
		Polynomial p2({2, -3, 6});

		auto mult = { 2, 1, -2, 15, -6 };

		Polynomial result = p1 * p2;

		for (auto value : mult) {
			static unsigned int i = 0;
			assertEqual(result.getCoefficientAt(i++), value, "Error: mult operation");
		}
	}

	{
		const int degree = 3;
		const int values[] = {1, 2, 3, 4};
		int multiplyedValues[] = {5, 10, 15, 20};
		Polynomial p(degree, values);
		Polynomial res1(p * 5);
		Polynomial res2(5 * p);
		for (unsigned int i = 0; i < p.getSize(); i++) {
			assertEqual(res1.getCoefficientAt(i), multiplyedValues[i], "Error: multiplication by a value (postfix)");
			assertEqual(res2.getCoefficientAt(i), multiplyedValues[i], "Error: multiplication by a value (prefix)");
		}
	}
	
	std::cout << "Test multiplication OK" << std::endl;
}

void testCalculate() {
	{
		Polynomial p({1, 2, -1, 1});
		assertEqual(p(2), 9, "Error: calculate method");
	}

	{
		Polynomial p({2, -2, 3});
		assertEqual(p(2), 10, "Error: calculate method");
	}

	{
		Polynomial p({-1, 3, 0, 2, -1, 1});
		assertEqual(p(2), 37, "Error: calculate method");
	}

	{
		Polynomial p1({2, -2, 3});
		Polynomial p2({1, 2, -1, 1});
		assertEqual((p1 * p2)(2), 90, "Error: calculate method (p1 * p2)(2)");
	}
	std::cout << "Test Calculate OK" << std::endl;
}

void testPrint() {
	{
		Polynomial p1({1, 4, 0, 3, 5});
		std::string expression = "5x^4 + 3x^3 + 4x^1 + 1x^0";
		std::ostringstream os;
		os << p1;
		assertEqual(expression == os.str(), 1, "Error: writing to stream");
	}
	std::cout << "Test Print OK" << std::endl;
}

void testAll() {
	std::vector<std::function<void()>> tests = {
		testConstructors,
		testCoefficients,
		testSum,
		testSub,
		testMultiply,
		testCalculate,
		testPrint
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
	std::cout << "***\n" << "\tDONE " << counter << "/" << tests.size() << " GROUPED TESTS SUCCESSFULLY" << "\n***" << std::endl;
}
