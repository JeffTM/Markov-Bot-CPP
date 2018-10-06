#pragma once
#include <string>

//Returns true if c is contained in "!,.:;?"
//In it's own file becuase this function is needed by Tokenizer and MarkovText
inline bool isPunctuation(char c)
{
	return std::string("!,.:;?").find(c) != std::string::npos;
}
