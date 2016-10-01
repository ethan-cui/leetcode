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


#endif


