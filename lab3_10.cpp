#include <iostream>
#include <clocale>
#include <climits>
#include <algorithm>

int32_t* element(int32_t* matrix, int32_t i, int32_t j, int32_t n) {
	if (j >= n - i) {
		i = n - i - 1;
		j = n - j - 1;
		std::swap(i, j); // по условию i = n - j - 1, j = n - i - 1, поэтому я добавил свап
	}
	// n - кол-во элементов в первой строке, n - (i - 1) - кол-во элементов в (i-1)-й строке (в каждой следующей строке на один элемент меньше чем в предыдущей)
	// i-1 - потому что нас интересует кол-во элементов в строках до i-й
	// * (i) - потому что кол-во строк до нынешней равно i, с учетом нулевой индексации
	// случай i = 0 проходит, случаи когда i больше 0 - тоже
	int	count_elements_in_previous_lines = (n + (n - (i - 1))) * (i) / 2;
	return matrix + (count_elements_in_previous_lines + j);
}


void print_matrix(int32_t* matrix, int32_t n) {
	for (int32_t i = 0; i < n; i++) {
		for (int32_t j = 0; j < n; j++)
			std::cout << *element(matrix, i, j, n) << ' ';
		std::cout << '\n';
	}
}


int32_t main() {
	std::setlocale(LC_ALL, "Russian");

	//Ввод числа и проверка (я сделал ввод одного числа, тк матрица по условию 10-й задачи квадратная)
	int32_t n;
	std::cout << "Введите натуральное число, которое будет соответствовать размерности матрицы (количество строк и столбцов).\n" <<
		"В случае ввода действительного числа, число округлятся по правилам с++, а в случае ввода символа - консоль зависнет:\n";
	std::cin >> n;
	while (n <= 0 || n > 10) {
		std::cout << "Введите натуральные число не больше 10:\n";
		std::cin >> n;
	}

	int32_t* matrix = new int32_t[n * (n + 1) / 2];

	//Ввод матрицы
	std::cout << "Введите матрицу из натуральных чисел размером " << n << " на " << n << ":\n";

	for (int32_t i = 0; i < n; i++) {
		std::cout << "Введите первые " << n - i << " элементов " << i + 1 << "-й строки:\n";
		for (int32_t j = 0; j < n - i; j++)
			std::cin >> *element(matrix, i, j, n);
	}
	std::cout << "\nВведенная вами матрица выглядит так:\n";
	print_matrix(matrix, n);

	std::cout << "Произведение элементов в строках, не содержащих отрицательные элементы:\n" <<
		"Строка:\tЗначение:\n";
	for (int32_t i = 0; i < n; i++) {
		bool is_negative_exist = false;
		int64_t product = 1;

		for (int32_t j = 0; j < n; j++) {
			int32_t elem = *element(matrix, i, j, n);
			if (elem < 0) {
				is_negative_exist = true;
				std::cout << i + 1 << "-я:\t" << "Строка содержит отрицательные элементы\n";
				break;
			}
			product *= elem;
		}
		if (!is_negative_exist)
			std::cout << i + 1 << "-я:\t" << product << '\n';

	}

	if (n == 1) {
		std::cout << "Матрица 1x1 не имеет диагоналей, кроме главной.\n";
	}
	else {
		std::cout << "\nМинимум среди сумм всех диагоналей, параллельных главной диагонали, но не включая ее:\n";
		int32_t min = INT_MAX;

		//диагонали, начинающиеся с i = 0, кроме главной
		for (int32_t j = 1; j < n; j++) { // j = 0 - начало главной
			int32_t i = 0;
			int32_t sum = 0;
			for (int32_t k = 0; j + k < n && i + k < n; k++) { //добавляем к индексу i, j, чтобы идти диагонально по матрице и паралельно главной диагонали
				sum += *element(matrix, i + k, j + k, n);
			}
			min = std::min(min, sum);
		}

		//диагонали, начинающиеся с j = 0, кроме главной
		for (int32_t i = 1; i < n; i++) { // i = 0 - начало главной
			int32_t j = 0;
			int32_t sum = 0;
			for (int32_t k = 0; j + k < n && i + k < n; k++) {
				sum += *element(matrix, i + k, j + k, n);
			}
			min = std::min(min, sum);
		}

		std::cout << min << '\n';
	}
	delete[] matrix;
}