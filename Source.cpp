#include<iostream>
#include <string>
#include <vector>
#include "FiniteAutomata.h"
#include <ctime>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

void showTitle(string message) {
	cout << "\n========================= " << message << " =========================\n" << endl;
}


int main() {
	setlocale(LC_ALL, "RUS");
	showTitle("Условия задачи");
	cout << "Недетерминированный конечный автомат задан в виде таблицы переходов. Напишите программу, которая считает эту таблицу из файла и с помощью алгоритма детерминизации строит эквивалентный детерминированный автомат.\n";
	cout << "Введите имя файла с автоматом:" << endl;
	string name;
	cin >> name;
	FiniteAutomata automata(name);
	//FiniteAutomata automata("automata.txt");
	//FiniteAutomata automata("automata2.txt");
	//FiniteAutomata automata("automata3.txt");
	//FiniteAutomata automata("automata4.txt");
	showTitle("Функция переходов");
	automata.printTransitionFunction();
	showTitle("После детерминизации:");
	//cout << "Введите слово, принадлежность которого надо проверить. \nВведите eps для проверки пустого слова. Для завершения введите -1:" << endl;
	//std::string str;

	automata.determine();

	automata.printTransitionFunction();

	/*while (true)
	{
		cout << "\n> ";
		cin >> str;
		if (str == "-1") {
			break;
		}
		if (str == "eps") {
			if (automata.recognize("")) {
				cout << "Слово принадлежит языку L.\n";
			}
			else {
				cout << "Слово не принадлежит языку L.\n";
			}
			continue;
		}
		if (str.find_first_not_of("01") != std::string::npos) {
			cout << "Вы ввели недопустимое слово.\n";
			continue;
		}

		if (automata.recognize(str)) {
			cout << "Слово принадлежит языку L.\n";
		}
		else {
			cout << "Слово не принадлежит языку L.\n";
		}
	}*/
	system("pause");
}