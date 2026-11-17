#include "ProperFraction.h"

ProperFraction::ProperFraction(int numerator, int denominator) {
	if (denominator == 0) {
		throw std::invalid_argument("Знаменатель не может быть равен нулю");
	}
	m_numerator = numerator;
	m_denominator = denominator;
	simplify();
}

ProperFraction::ProperFraction(const ProperFraction& proper_fraction) {
	m_numerator = proper_fraction.m_numerator;
	m_denominator = proper_fraction.m_denominator;
	simplify();
}

void ProperFraction::addition(const ProperFraction& proper_fraction) {
	int a1 = m_numerator;
	int b1 = m_denominator;
	int a2 = proper_fraction.m_numerator;
	int b2 = proper_fraction.m_denominator;
	m_numerator = a1 * b2 + a2 * b1;
	m_denominator = b1 * b2;
	simplify();
}

void ProperFraction::multiplication(const ProperFraction& proper_fraction) {
	int a1 = m_numerator;
	int b1 = m_denominator;
	int a2 = proper_fraction.m_numerator;
	int b2 = proper_fraction.m_denominator;
	m_numerator = a1 * a2;
	m_denominator = b1 * b2;
	simplify();
}

void ProperFraction::division(const ProperFraction& proper_fraction) {
	int a1 = m_numerator;
	int b1 = m_denominator;
	int a2 = proper_fraction.m_numerator;
	int b2 = proper_fraction.m_denominator;
	if (a2 == 0) {
		std::cout << "Операция деления не была выполнена, так как делитель равен нулю" << std::endl;
		return;
	}
	m_numerator = a1 * b2;
	m_denominator = a2 * b1;
	simplify();
}

void ProperFraction::print() {
	std::cout << to_string() << std::endl;
}

int ProperFraction::get_numerator() const {
	return m_numerator;
}

int ProperFraction::get_denominator() const {
	return m_denominator;
}

void ProperFraction::simplify() {
	int znak = (abs(m_numerator) / ((m_numerator == 0) ? 1 : m_numerator)) *
		(abs(m_denominator) / m_denominator);
	int gcd = std::gcd(m_numerator, m_denominator);
	m_numerator = abs(m_numerator) / gcd * znak;
	m_denominator = abs(m_denominator) / gcd;
}

std::string ProperFraction::to_string() {
	std::stringstream out;
	if (m_numerator == 0) {
		out << 0;
	}
	else if (m_denominator == 1) {
		out << m_numerator;
	}
	else {
		out << m_numerator << " / " << m_denominator;
	}
	return out.str();
}