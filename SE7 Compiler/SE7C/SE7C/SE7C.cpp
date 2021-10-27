// SE7C.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

#include "lexer.hpp"

int main(int argc, const char *argv[]) {
	if (!std::filesystem::exists("test.SE7")) {
		std::fstream temp("test.SE7", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

		temp <<
			"module src;\n"
			"\n"
			"import io;\n"
			"\n"
			"int(string[]) main = (args) {\n"
			"\r\tint a = 1 + 2 * 3 / 4 \\ 5 & 6 | 7 ^ 8 - 9;\n"
			"\r\t\n"
			"\r\tprintln(args[0]);\n"
			"\r\treturn 0;\n"
			"}\n"
		;

		temp.close();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
