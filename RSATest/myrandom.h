#pragma once
#include <random>
#include <algorithm>

class RandomINT {
private:
	std::random_device rd;
	std::mt19937 gen;
public:
	RandomINT() : gen(rd()) {};
	template<class T = long long>
	T GetRandomInteger(T a, T b) {///return random integer in [a,b]
		if (a>b)
			std::swap(a, b);
		std::uniform_int_distribution<T> dis(a, b);
		return dis(gen);
	}
};