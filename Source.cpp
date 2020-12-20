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
	showTitle("������� ������");
	cout << "������������������� �������� ������� ����� � ���� ������� ���������. �������� ���������, ������� ������� ��� ������� �� ����� � � ������� ��������� �������������� ������ ������������� ����������������� �������.\n";
	cout << "������� ��� ����� � ���������:" << endl;
	string name;
	cin >> name;
	FiniteAutomata automata(name);
	//FiniteAutomata automata("automata.txt");
	//FiniteAutomata automata("automata2.txt");
	//FiniteAutomata automata("automata3.txt");
	//FiniteAutomata automata("automata4.txt");
	showTitle("������� ���������");
	automata.printTransitionFunction();
	showTitle("����� ��������������:");
	//cout << "������� �����, �������������� �������� ���� ���������. \n������� eps ��� �������� ������� �����. ��� ���������� ������� -1:" << endl;
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
				cout << "����� ����������� ����� L.\n";
			}
			else {
				cout << "����� �� ����������� ����� L.\n";
			}
			continue;
		}
		if (str.find_first_not_of("01") != std::string::npos) {
			cout << "�� ����� ������������ �����.\n";
			continue;
		}

		if (automata.recognize(str)) {
			cout << "����� ����������� ����� L.\n";
		}
		else {
			cout << "����� �� ����������� ����� L.\n";
		}
	}*/
	system("pause");
}