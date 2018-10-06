#include "Tokenizer.h"

//Breaks the string src into substrings that represent words in the markov chain
void Tokenizer::operator()(const std::string & fileName, std::vector<std::string> & dest) const
{
	using namespace std;

	string src(slurp(fileName));

	size_t i = 0;
	while (true)
	{
		//Advance past any white space characters
		while (isWhiteSpace(src[i]) && i < src.size())
			++i;
		if (i == src.size())
			return;

		//If src[i] is an opening character add the substring contained
		//between i and its closing tag
		if (isOpeningTag(src[i]))
		{
			size_t closeIndex = findClosingTag(src, src[i], i + 1);
			if (closeIndex == string::npos)
			{
				dest.push_back(lowercase(src.substr(i)));
				return;
			}
			dest.push_back(lowercase(src.substr(i, closeIndex - i + 1))); //Remove the lowercase?
			i = closeIndex + 1;
		}
		//else if scr[i] is a punctuation character add it and any following equal characters
		else if (isPunctuation(src[i]))
		{
			size_t count = groupCount(src, i);
			dest.push_back(src.substr(i, count));
			i += count;
		}
		//else add the token is the substring from i up to but not including
		//the next stop character
		else
		{
			size_t nextStopper = findStopper(src, i + 1);
			if (nextStopper == string::npos)
			{
				dest.push_back(lowercase(src.substr(i)));
				return;
			}
			dest.push_back(lowercase(src.substr(i, nextStopper - i)));
			i = nextStopper;
		}
	}
}

//private:

//Returns the closing character of c
//e.g. closer('[') returns ']'
char Tokenizer::closer(char c)
{
	switch (c)
	{
	case '(':
		return ')';
	case '[':
		return ']';
	case '<':
		return '>';
	case '{':
		return '}';
	default:
		return '\0';
	}
}

//Returns the number of characters that compare equal to scr[start] continuously starting at start
//e.g. if scr is "aaaba", start is 0 the function will return 3
std::size_t Tokenizer::groupCount(const std::string & src, size_t start)
{
	char key = src[start];
	std::size_t count = 1;
	for (++start; src[start] == key && start < src.size(); ++start)
		++count;
	return count;
}

//Returns the index of the closing character of c in src starting at start
//if not found returns string::npos
std::size_t Tokenizer::findClosingTag(const std::string & src, char c, size_t start)
{
	c = closer(c);
	return src.find(c, start);
}

//Returns the index of the first character in src for which isStopper returns true
std::size_t Tokenizer::findStopper(const std::string & src, size_t start)
{
	while (start < src.size())
	{
		if (isStopper(src[start]))
			return start;
		++start;
	}
	return std::string::npos;
}

//returns true if c is contained in the string "c[<{"
bool Tokenizer::isOpeningTag(char c)
{
	return std::string("([<{").find(c) != std::string::npos;
}

//returns true if c is a stopping character character
//C is a stopping character if isPunctuation(c) or isWhiteSpace(c) returns true
bool Tokenizer::isStopper(char c)
{
	return isWhiteSpace(c) || isPunctuation(c);
}

//Returns true if c is contained in " \n\t\r\f\v"
bool Tokenizer::isWhiteSpace(char c)
{
	return std::string(" \n\t\r\f\v").find(c) != std::string::npos;
}

//Returns s with all uppercase letters replaced with their lowercase version
std::string Tokenizer::lowercase(std::string s) //Upgrade this with move semantics? I think it is already used automatically
{
	for (std::size_t i = 0; i < s.size(); ++i)
	{
		if ('A' <= s[i] && s[i] <= 'Z')
			s[i] += 32;
	}
	return s;
}

//Returns the entire file at fileName as a string
//Modified from: https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c
std::string Tokenizer::slurp(const std::string & fileName)
{
	std::ifstream file(fileName);
	std::stringstream sstr;
	sstr << file.rdbuf();
	file.close();
	return sstr.str();
}
