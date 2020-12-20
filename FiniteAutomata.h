#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <initializer_list>
#include <set>
#include <queue>
#include <algorithm>

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
			std::cout << "\nError while opening the file.\n" << std::endl;
			system("pause");
			exit(1);
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
		int length = getLongestState();
		std::string head = generateString(' ', length + 7);
		std::string body = generateString(' ',length + 6) + "|";
		std::string down = generateString('-',length + 6) + "|";
		for (auto s : alphabet) {
			head += generateString('_', length*2 + 6);
			body += generateString(' ', (length*2 + 5)/2) + std::string(1, s) + generateString(' ', (length*2 + 6) / 2) +"|";
			down += generateString('-', length*2 + 6) + "|";
		}
		head += "_";
		std::cout << head << std::endl << body << std::endl << down << std::endl;

		for (auto st : transitionFunction) {
			if (std::find(finiteStates.begin(), finiteStates.end(), st.first) != finiteStates.end()) {
				std::cout << "F";
			}
			else
			{
				std::cout << " ";
			}
			if (st.first == startingState) {
				std::cout << "->";
			}
			else
			{
				std::cout << "  ";
			}
			centerText(st.first.c_str(), length);
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

				centerText(wholestate.c_str(), length*2);
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

	void determine() {
		std::map<std::string, std::map<char, std::set<std::string>>> newTransitionFunction;
		std::queue<std::set<std::string>> queue;
		for (auto tr : transitionFunction[startingState]) {
			auto newState = transitionFunction[startingState][tr.first];
			newTransitionFunction["{" + startingState + "}"][tr.first].insert(formatSet(newState));
			queue.push(newState);
		}
		while (!queue.empty())
		{
			auto stateSet = queue.front();
			auto newStateName = formatSet(stateSet);
			if (newTransitionFunction.find(newStateName) == newTransitionFunction.end()) {
				for (auto sym: alphabet)
				{
					std::set<std::string> newState;
					for (auto it = stateSet.begin(); it != stateSet.end(); it++) {
						auto oldState = transitionFunction[*it][sym];
						newState = getUnion(oldState, newState);
						queue.push(newState);
					}
					if (newState.empty()) {
						continue;
					}
					newTransitionFunction[newStateName][sym].insert(formatSet(newState));
				}
			}
			queue.pop();
		}
		
		std::vector<std::string> newFiniteStates;
		for (auto pair : newTransitionFunction) {
			for (auto old : finiteStates) {
				if (pair.first.find(old) != std::string::npos) {
					newFiniteStates.push_back(pair.first);
					continue;
				}
			}
		}

		finiteStates = newFiniteStates;
		startingState = "{" + startingState + "}";
		stateCount = transitionFunction.size();
		transitionFunction = newTransitionFunction;

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
		if ((fieldWidth - strlen(text)) % 2 == 1) {
			printf(" ");
		}
	}

	std::string formatSet(std::set<std::string> in) {
		if (in.empty()) {
			return " ";
		}
		std::string res = "{";
		for (auto p = in.begin(); p != --in.end(); p++)
		{
			res += *p + ", ";
		}
		res += *(--in.end()) + "}";
		return res;
	}

	std::set<std::string> getUnion(const std::set<std::string>& a, const std::set<std::string>& b)
	{
		std::set<std::string> result = a;
		result.insert(b.begin(), b.end());
		return result;
	}

	int getLongestState() {
		int max = 0;
		for (auto pair : transitionFunction) {
			if (pair.first.size() > max) {
				max = pair.first.size();
			}
		}
		if (max < 2) {
			return 5;
		}
		return max;
	}

	std::string generateString(char elem, int count) {
		std::string res = "";
		for (int i = 0; i < count; i++)
		{
			res += elem;
		}
		return res;
	}

};