#ifndef UTILS_HPP
#define UTILS_HPP


#include <iostream>
#include <vector>
#include <string>

template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& vec){
	for (auto& el :vec){
		os << el << ' ';
	}
	return os;
}

std::vector<int> range(int n){
	std::vector<int> res(n,0);
	for (int i=0; i<n; i++)
		res[i]=i;
	return res;
}

std::vector<int> range(int start, int end, int step=1){
	int n = (int) (end - start) / step;
	std::vector<int> res(n,start);
	for (int i=0; i<n; i++)
		res[i]+= i*step;
	return res;
}


#endif


