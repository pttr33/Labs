#include <iostream>
#include <clocale>

void task_a();

void task_b();

// так как в задаче А не была указана длина строки, я решил реализовать функцию ввода строки неопределенного значение
// по запросу как вводится string из stl, мне описал идею гемини, он указал что string вводится так же, но эту информацию не перепроверял
// асимпототика должна быть O(n), n - длина итоговой строки
char* read_input() {
    int size = 10;
    int ind = 0;
    char* str = new char[size];
    char c;

    while (std::cin.get(c) && c != '\n') {
        if (ind == size - 1) {
            size *= 2;
            char* new_str = new char[size];
            for (int i = 0;i <= ind;i++)
                new_str[i] = str[i];
            delete[] str;
            str = new_str;
        }
        str[ind] = c;
        ind++;
    }
    str[ind] = '\0';
    return str;
}

int my_strspn(const char* string, const char* strCharSet) {
    int count = 0;

    while (*string != '\0') {
        const char* ptr = strCharSet;

        bool fl = false;
        while (*ptr != '\0' && !fl) {
            fl = (*ptr == *string); // выйдет из цикла как только будет true
            ptr++;
        }

        if (!fl)
            return count;
        count++;
        string++;
    }
    return count;
}



int main()
{
    std::setlocale(LC_ALL, "Russian");

    task_a();

    task_b();

    return 0;
}

void task_a() {
    std::cout << "Задача A\n\n";

    std::cout << "Введите строку:\n";
    char* str = read_input();
    std::cout << "Введите множество символов:\n";
    char* str_char_set = read_input();

    std::cout << "Ответ: " << my_strspn(str, str_char_set) << "\n\n";
    delete[] str;
    delete[] str_char_set;
}

void task_b() {
    char str[301];
    std::cout << "Задача B\n\n";
    std::cout << "Введите строку, содержащую не более 300 символов:\n";
    // ввод
    std::cin.getline(str, 301);

    const char* ptr = str;
    int max_count_zero = -1;
    const char* ptr_max_count_zero_last = nullptr;
    const char* ptr_max_count_zero_prelast = nullptr;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            const char* ptr_start = ptr;
            bool is_all_symnbols_numbers = true;
            int count_zero_in_word = 0;
            while (*ptr != '\0' && *ptr != ' ') {
                if (*ptr == '0')
                    count_zero_in_word++;
                is_all_symnbols_numbers = ('0' <= *ptr && *ptr <= '9') && is_all_symnbols_numbers; // пока флаг правдив и условие правдиво - true, один раз условие неверно - значние && будет false
                ptr++;
            }
            if (!is_all_symnbols_numbers)
                continue;
            if (max_count_zero == count_zero_in_word) {
                // если он равен, то значит мы уже присваивали (изначально max_count_zero = -1) в
                // ptr_max_count_zero_last адресс => мы уверены, что там не нулевой указатель
                ptr_max_count_zero_prelast = ptr_max_count_zero_last;
                ptr_max_count_zero_last = ptr_start;
            }
            else if (max_count_zero < count_zero_in_word) {
                max_count_zero = count_zero_in_word;
                ptr_max_count_zero_prelast = nullptr; // новый максимум, значит предпоследний нулевой
                ptr_max_count_zero_last = ptr_start;
            }
        }
        else {
            ptr++;
        }
    }
    if (ptr_max_count_zero_prelast != nullptr) {
        while (*ptr_max_count_zero_prelast != '\0' && *ptr_max_count_zero_prelast != ' ') {
            std::cout << *ptr_max_count_zero_prelast;
            ptr_max_count_zero_prelast++;
        }
    }
    else if (ptr_max_count_zero_last != nullptr) {
        while (*ptr_max_count_zero_last != '\0' && *ptr_max_count_zero_last != ' ') {
            std::cout << *ptr_max_count_zero_last;
            ptr_max_count_zero_last++;
        }
    }
    else {
        std::cout << "В строке нету слов, подходящих под условия задачи B";
    }
    std::cout << "\n\n";
}


