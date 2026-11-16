#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string readFile(const std::string &source);

template <typename T>
T lerp(const T& start,const T& end, float t)
{
	T result;

	result = (1.0f - t) * start + t * end;
	return result;
}

#endif //UTILS_H