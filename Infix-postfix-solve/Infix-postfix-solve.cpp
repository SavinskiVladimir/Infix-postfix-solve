#include <iostream>
#include <string>
#include <vector>

using namespace std;

int get_priority(char c) {
    if (c == '(' || c == ')') return 1;
    if (c == '+' || c == '-') return 2;
    return 3;
}

string get_postfix(string s) {
    string stek = "";
    string result = "";
    int i, j;
    for (i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) result += s[i]; // добавление в конец результирующей строки встреченной цифры
        else if (s[i] == '(') stek += s[i]; // вталкивание в стек открытой скобки
        else if (s[i] == ')') {
            j = stek.size() - 1;
            while (stek[j] != '(') {
                result += stek[j]; // добавление в конец результирующей строки оператора из стека
                stek = stek.substr(0, j); // удаление добавленного в строку оператора из стека
                j--;
            }
            stek = stek.substr(0, j); // удаление открытой скобки из стека
        }
        else {
            if (stek.empty() || stek.size() > 0 && get_priority(stek[stek.size() - 1]) < get_priority(s[i])) stek += s[i];
            else {
                j = stek.size() - 1;
                while (j >= 0 && get_priority(stek[j]) >= get_priority(s[i])) {
                    result += stek[j];
                    stek = stek.substr(0, j);
                    j--;
                }
                stek += s[i]; // вталкивание в стек встреченного оператора
            }
        }
    }
    if (!stek.empty()) for (i = stek.size() - 1; i >= 0; i--) result += stek[i]; // добавление в результирующую
    // строку операторов, оставшихся в стеке 
    return result;
}

int solve_postfix(string s) {
    vector <int> stek;
    int i, a, b;
    for (i = 0; i < s.size(); i++) {
        if (isdigit(s[i])) stek.push_back((int)s[i] - 48); // вталкивание в стек встреченной цифры
        else {
            a = stek[stek.size() - 2]; // выталкивание из стека 2 крайних операндов
            b = stek[stek.size() - 1]; // и вычисление значения выражения
            stek.erase(stek.begin() + stek.size() - 2, stek.end());
            if (s[i] == '+') stek.push_back(a + b);
            else if (s[i] == '-') stek.push_back(a - b);
            else if (s[i] == '*') stek.push_back(a * b);
            else stek.push_back(a / b); // вталкивание в стек вычисленного результата
        }
    }
    return stek[0]; // возврат оставшегося в стеке результата вычисления выражения
}

int main()
{
    setlocale(LC_ALL, "");
    cout << "Введите выражение без пробелов: ";
    string s;
    cin >> s;
    string s_post = get_postfix(s);
    cout << "Введённое выражение в постфиксной форме: " << s_post<<endl;
    int result = solve_postfix(s_post);
    cout << "Решение введённого выражения: " << result;
    return 0;
}

