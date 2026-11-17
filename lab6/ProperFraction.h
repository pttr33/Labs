#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>
#include <numeric>

class ProperFraction {
public:
	ProperFraction() = delete;
	ProperFraction(int numerator, int denominator);
	ProperFraction(const ProperFraction& proper_fraction);

	void addition(const ProperFraction& proper_fraction);
	void multiplication(const ProperFraction& proper_fraction);
	void division(const ProperFraction& proper_fraction);

	void print();

	int get_numerator() const;
	int get_denominator() const;
private:
	int m_numerator;
	int m_denominator;
	void simplify();
	std::string to_string();
};