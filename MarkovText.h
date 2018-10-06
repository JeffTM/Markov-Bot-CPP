#pragma once
#include <algorithm>
#include <limits>
#include <random>
#include <string>
#include <vector>
#include "BinarySearch.h"
#include "IsPunctuation.h"
#include "SMatrix.h"
#include <iostream> //DEBUG

class MarkovText
{
private:
	std::vector<std::string> vertices;
	SMatrix<unsigned int> adjmat;
	std::vector<unsigned int> rowsums;
public:
	//Constructor
	MarkovText();
	MarkovText(const std::vector<std::string> & tokens);
	
	void build(const std::vector<std::string> & tokens);
	template<class RNG> std::string generate(RNG & gen, int count);
	template<class RNG> std::string generateUntil(RNG & gen, char stop, int limit);
	template<class RNG> std::string generateUntil(RNG & gen, const std::string & stop, int limit);
private:
	void buildAdjmat(const std::vector<std::string> & tokens);
	void buildVertices(const std::vector<std::string> & tokens);
	static char capital(char c);
	size_t getIndex(const std::string & s) const;
	template<class RNG> size_t nextVertex(RNG & gen, size_t current) const;
	template<class RNG> size_t randVertex(RNG & gen) const;
};

//public:

//Generates a random markov walk over count vertices
//May terminate early if a vertex is reached that has no outgoing edges
//Returns a formatted string representing the walk
template<class RNG>
inline std::string MarkovText::generate(RNG & gen, int count)
{
	return generateUntil(gen, std::string(), count);
}

template<class RNG>
inline std::string MarkovText::generateUntil(RNG & gen, char stop, int limit) //Is this necessary?
{
	return generateUntil(gen, std::string(1, stop), limit);
}

template<class RNG>
std::string MarkovText::generateUntil(RNG & gen, const std::string & stop, int limit)
{
	if (vertices.empty())
		return "ERROR: EMPTY";

	size_t current = randVertex(gen); //ToDo: make sure a puctuation string isn't returned
	//Initialize result to the capitalized first token
	std::string result(capital(vertices[current][0]) + vertices[current].substr(1));
	--limit;
	for (int i = 0; i < limit && vertices[current] != stop; ++i)
	{
		current = nextVertex(gen, current);
		if (current == std::numeric_limits<size_t>::max()) //Is std::numeric_limits<size_t>::max() evaluated at compile time? If not save it as a variable
			break;
		if (!isPunctuation(vertices[current][0]))
			result += ' ';
		if (vertices[current] == "i")
			result += 'I';
		else
			result += vertices[current];
	}

	return result;
}

//private:

inline char MarkovText::capital(char c)
{
	if ('a' <= c && c <= 'z')
		c -= 32;
	return c;
}

//Randomly selects the next vertex with a weighted selection.
//A vertices probability of getting selected is the edge weight from current to the vertex divded by the sum of all edge weights from current
//Returns the index of the next vertex or std::numeric_limits<size_t>::max() if the sum of all edge weights from current is 0 (there are no outgoing edges)
template<class RNG>
size_t MarkovText::nextVertex(RNG & gen, size_t current) const
{
	if (rowsums[current] == 0)
		return std::numeric_limits<size_t>::max();

	std::uniform_int_distribution<size_t> dist(0, rowsums[current] - 1);
	size_t r = dist(gen);
	size_t i;
	for (i = 0; r > adjmat.get(current, i) || adjmat.get(current, i) == 0; ++i)
		r -= adjmat.get(current, i);
	return i;
}

//Randomly selects a vertex in vertices and returns it's index
template<class RNG>
inline size_t MarkovText::randVertex(RNG & gen) const
{
	std::uniform_int_distribution<size_t> dist(0, vertices.size() - 1);
	return dist(gen);
}
