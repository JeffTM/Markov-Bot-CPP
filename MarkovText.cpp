#include "MarkovText.h"

//public:

MarkovText::MarkovText()
	:vertices(), adjmat(0), rowsums()
{}

MarkovText::MarkovText(const std::vector<std::string> & tokens)
	:vertices(), adjmat(0), rowsums()
{
	build(tokens);
}

void MarkovText::build(const std::vector<std::string> & tokens)
{
	buildVertices(tokens);
	//DEBUG
	std::cout << "Vertices:" << std::endl;
	for (const std::string & s : vertices) 
		std::cout << s << ';' << std::endl;
	std::cout << vertices.size() << " vertices generated" << std::endl;
	buildAdjmat(tokens);
	//DEBUG
	/*
	std::cout << "adjmat: " << std::endl;
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		for (size_t j = 0; j < vertices.size(); ++j)
			std::cout << adjmat.get(i, j) << ' ';
		std::cout << "\tsum: " << rowsums[i] << std::endl;
	}
	*/
}

//private:

//Builds the adjacency matrix from vertices and tokens. buildVertices must be called first!
void MarkovText::buildAdjmat(const std::vector<std::string> & tokens)
{
	adjmat.resize(vertices.size(), 0);
	rowsums = std::vector<unsigned int>(vertices.size(), 0);
	for (size_t i = 0; i < tokens.size() - 1; ++i)
	{
		size_t first = getIndex(tokens[i]);
		size_t second = getIndex(tokens[i + 1]);
		++adjmat(first, second);
		++rowsums[first];
	}
}

//Builds the vertices list from tokens
void MarkovText::buildVertices(const std::vector<std::string> & tokens)
{
	vertices = tokens;
	std::sort(vertices.begin(), vertices.end());
	auto newEnd = std::unique(vertices.begin(), vertices.end());
	vertices.resize(std::distance(vertices.begin(), newEnd));
}

//Returns the index of s in the vertices list
size_t MarkovText::getIndex(const std::string & s) const
{
	return binarySearch(vertices, s);
}
