#include <iostream>
#include "ProperFraction.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	int numerator1, denominator1, numerator2, denominator2;
	std::cout << "Введите числитель и знаменатель первой дроби: " << std::endl;
	std::cin >> numerator1 >> denominator1;
	std::cout << "Введите числитель и знаменатель второй дроби: " << std::endl;
	std::cin >> numerator2 >> denominator2;

	try {
		ProperFraction f1(numerator1, denominator1);
		ProperFraction f2(numerator2, denominator2);

		f1.print();
		f2.print();

		ProperFraction f1_copy(f1);
		ProperFraction f2_copy(f2);
		f1_copy.addition(f2_copy);
		f1_copy.print();

		f1_copy = ProperFraction(f1);
		f2_copy = ProperFraction(f2);
		f1_copy.multiplication(f2_copy);
		f1_copy.print();

		f1_copy = ProperFraction(f1);
		f2_copy = ProperFraction(f2);
		f1_copy.division(f2_copy);
		f1_copy.print();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl; // про обработчик ошибок сказала иишка мне, решил добавить
	}

	return 0;
}