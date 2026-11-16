#include "utils.h"

#include <iostream>
#include <fstream>

std::string readFile(const std::string &source)
{
	std::string content;
	std::string line;

	std::ifstream file;
	file.open(source.c_str(), std::ios_base::in);
	if (file.is_open())
	{
		//parse file line by line into one string
		while (!file.eof())
		{
			getline(file, line);
			line += "\n";
			content += line;
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file: " << source << std::endl;
	}

	return content;
}