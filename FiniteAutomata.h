#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <initializer_list>
#include <set>

class FiniteAutomata {
	std::map<std::string, std::map<char, std::set<std::string>>> transitionFunction;
	std::vector<std::string> finiteStates;
	int stateCount;
	std::string startingState;
	std::vector<char> alphabet;

public:
	FiniteAutomata() {
		stateCount = 0;
		startingState = "";
	}

	FiniteAutomata(std::string pathToFile) : FiniteAutomata() {
		readFromFile(pathToFile);
	}

	// Create automata from file
	void readFromFile(std::string pathToFile) {
		std::ifstream in(pathToFile, std::ios_base::in);
		std::string line;
		if (!in) {
			std::cout << "Error while opening the file." << std::endl;
			return;
		}
		std::getline(in, line);
		for (auto s : split(line)) {
			if (s.size() > 1) {
				throw std::exception("File parsing exception: Alphabet must cosist of single chars.");
			}
			alphabet.push_back(s[0]);
		}
		while (std::getline(in, line))
		{
			if (line.size() == 0) {
				return;
			}
			auto splitted = split(line);
			if (!(splitted[0] == "+" || splitted[0] == "-")) {
				throw std::exception("File parsing exception: Transition function lines must start with '+' or '-'.");
			}
			if (splitted[0] == "+") {
				finiteStates.push_back(splitted[1]);
			}

			auto state = splitted[1];
			stateCount++;
			if (startingState == "") {
				startingState = state;
			}
			transitionFunction[state] = {};
			for (size_t i = 2; i < splitted.size(); i++)
			{
				auto pair = split(splitted[i], ':');
				if (pair.size() != 2 || pair[0].size() != 1) {
					throw std::exception("File parsing exception: Error while parsing state.");
				}
				transitionFunction[state][pair[0][0]].insert(pair[1]);
			}
		}
	}

	void printTransitionFunction() {
		std::string head = "            ";
		std::string body = "           |";
		std::string down = "-----------|";
		for (auto s : alphabet) {
			head += "__________________";
			body += "        " + std::string(1, s) + "        |";
			down += "-----------------|";
		}
		head.replace(--head.end(), head.end(), "");
		std::cout << head << std::endl << body << std::endl << down << std::endl;

		for (auto st : transitionFunction) {
			std::cout << "   ";
			centerText(st.first.c_str(),5);
			std::cout << "   |   ";
			for (auto s : alphabet) {
				std::string wholestate = "";
				if (st.second[s].size() > 0) {
					for (auto state : st.second[s]) {
						wholestate += state + " ";
					}

					wholestate.replace(--wholestate.end(), wholestate.end(), "");
				}
				else
				{
					wholestate = " ";
				}
				
				centerText(wholestate.c_str(),11);
				std::cout << "   |   ";
			}
			std::cout << "\n";
			std::cout << down << std::endl;
		}
		std::cout << std::endl;
	}

	bool recognize(const std::string& input) {
		return recognize_work(input, startingState);
	}

private:

	bool recognize_work(const std::string& input, std::string state) {
		for (auto p = input.begin(); p < input.end(); p++) {
			auto stateSet = transitionFunction[state][*p];
			if (stateSet.size() == 1) {
				state = *stateSet.begin();
			}
			else {
				for (auto q = stateSet.begin(); q != stateSet.end(); ++q) {
					if (recognize_work(std::string(p + 1, input.end()), *q)) {
						return true;
					}
				}
				return false;
			}
		}
		return std::find(finiteStates.begin(), finiteStates.end(), state) != finiteStates.end();
	}

	std::vector<std::string> split(const std::string& text, char sep = ' ') {
		std::vector<std::string> tokens;
		std::size_t start = 0, end = 0;
		while ((end = text.find(sep, start)) != std::string::npos) {
			tokens.push_back(text.substr(start, end - start));
			start = end + 1;
		}
		tokens.push_back(text.substr(start));
		return tokens;
	}

	void centerText(const char* text, int fieldWidth) {
		int padlen = (fieldWidth - strlen(text)) / 2;
		printf("%*s%s%*s", padlen, "", text, padlen, "");
	}


};