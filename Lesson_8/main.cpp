#include "FAM.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

int main()
{
	//Чтение текста T и образца P
	int length;
	char * buffer;
	std::ifstream ifs;
	ifs.open("Text.txt", std::ios::binary);

	ifs.seekg(0, std::ios::end);
	length = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	buffer = new char[length + 1];
	buffer[length] = '\0';

	ifs.read(buffer, length);
	ifs.close();
	
	std::string T = buffer;
	delete[] buffer;

	ifs.open("Pattern.txt", std::ios::binary);
	ifs.seekg(0, std::ios::end);
	length = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	buffer = new char[length + 1];
	buffer[length] = '\0';

	ifs.read(buffer, length);
	ifs.close();

	std::string P = buffer;

	delete[] buffer;

	//Поиск подстроки
	time_t start = clock();

	std::vector<int> pos = finiteAutomatonMatcher(P, T, true); //   <-----------
	for (int i = 0; i < pos.size(); ++i)
		std::cout << "position of pattern: " << pos[i] << '\n';
	std::cout << "time " << double(clock() - start) / CLOCKS_PER_SEC << " sec.\n";

	return 0;
}