#include <iostream>
#include <fstream>
#include <string>
#include <clocale>

void print_file(std::string file_name) {
	std::ifstream in(file_name);
	if (!in.is_open()) {
		std::cout << "Не удалось открыть файл\n";
		return;
	}
	std::string str;
	bool is_empty = true;
	while (std::getline(in, str)) {
		is_empty = false;
		std::cout << str << '\n';
	}
	if (is_empty)
		std::cout << "Файл пуст\n";
}

bool is_comment(std::string str) {
	int ind = 0;
	while (ind < str.size() && str[ind] == ' ')
		ind++;
	if (ind + 1 < str.size() && str[ind] == '/' && str[ind + 1] == '/')
		return true;
	return false;
}

int main() {
	std::setlocale(LC_ALL, "Russian");

	std::string input_file_name, output_file_name;

	std::cout << "Введите название входного файла:\n";
	std::getline(std::cin, input_file_name);
	std::ifstream in(input_file_name);
	while (!in.is_open()) {
		std::cout << "Такого файла не существует. Введите название входного файла заново:\n";
		std::getline(std::cin, input_file_name);
		in.open(input_file_name);
	}

	std::cout << "Введите название выходного файла:\n";
	std::getline(std::cin, output_file_name);
	std::ofstream out(output_file_name);

	std::string str, prev_str = "";
	int index_line = 0, index_start_group = 0, count_repeats = 0;
	bool is_header_printed = false;

	// в условии сказано вывести текст повторяющейся строки, поэтому за группу я считал 2 и более одинаковых комментария подряд
	// если нужно учитывать и одиночные комментарии, достаточно поменять условие count_repeats >= 2 на count_repeats >= 1
	while (std::getline(in, str)) {
		index_line++;

		if (count_repeats > 0 && str == prev_str) { // если строки равны, то str тоже комментарий, так как в prev_str записываются только комментарии
			count_repeats++;
		}
		else {
			if (count_repeats >= 2) {
				if (!is_header_printed) {
					out << "Номер строки начала:\tКоличество повторений:\tТекст строки:\n";
					is_header_printed = true; // печатаем шапку только при наличии групп, иначе по условию файл должен остаться пустым
				}
				out << index_start_group << '\t' << count_repeats << '\t' << prev_str << '\n';
			}

			if (is_comment(str)) {
				prev_str = str;
				index_start_group = index_line;
				count_repeats = 1;
			}
			else {
				count_repeats = 0;
			}
		}
	}

	if (count_repeats >= 2) {
		if (!is_header_printed)
			out << "Номер строки начала:\tКоличество повторений:\tТекст строки:\n";
		out << index_start_group << '\t' << count_repeats << '\t' << prev_str << '\n';
	}

	in.close();
	out.close();

	int fl = 0;
	std::cout << "\nВывести содержимое входного файла? (1 - да, 0 - нет):\n";
	std::cin >> fl;
	if (fl == 1) {
		std::cout << "\nСодержимое входного файла:\n";
		print_file(input_file_name);
	}

	std::cout << "\nВывести содержимое выходного файла? (1 - да, 0 - нет):\n";
	std::cin >> fl;
	if (fl == 1) {
		std::cout << "\nСодержимое выходного файла:\n";
		print_file(output_file_name);
	}

	return 0;
}