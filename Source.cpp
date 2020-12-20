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
	FiniteAutomata automata("automata.txt");
	showTitle("������� ���������");
	automata.printTransitionFunction();
	showTitle("�������� �� ��������������");
	cout << "������� �����, �������������� �������� ���� ���������. \n������� eps ��� �������� ������� �����. ��� ���������� ������� -1:" << endl;
	std::string str;
	while (true)
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
	}
	system("pause");
}