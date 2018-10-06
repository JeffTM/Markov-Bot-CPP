#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "IsPunctuation.h"

struct Tokenizer
{
public:
	void operator()(const std::string & fileName, std::vector<std::string> & dest) const;
private:
	static char closer(char c);
	static std::size_t groupCount(const std::string & src, size_t start);
	static std::size_t findClosingTag(const std::string & src, char c, size_t start);
	static std::size_t findStopper(const std::string & src, size_t start);
	static bool isOpeningTag(char c);
	static bool isStopper(char c);
	static bool isWhiteSpace(char c);
	static std::string lowercase(std::string s);
	static std::string slurp(const std::string & fileName);
};
