#ifndef UTILS_HPP
#define UTILS_HPP


#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <stdexcept>
struct TreeNode{
	int val;
	std::shared_ptr<TreeNode> left;
	std::shared_ptr<TreeNode> right;

	TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
	TreeNode(): val(0), left(nullptr), right(nullptr) {}
};

template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& vec){
	for (auto& el :vec){
		os << el << ' ';
	}
	return os;
}

std::ostream& operator << (std::ostream& os, const std::shared_ptr<TreeNode>& sp){
	std::queue<std::shared_ptr<TreeNode>> q;
	q.push(sp);
	while (!q.empty()){
		auto el = q.front();
		if (el){
			os << el->val << " ";
			q.pop();
			q.push(el->left);
			q.push(el->right);
		} else { 
			q.pop();
			os << "nullptr ";}
	}
	return os;
}

std::ostream& operator << (std::ostream& os, const TreeNode & tr){
	os << tr.val;
	return os;
}

std::vector<std::string> split(const std::string& s, char delim){

	std::stringstream ss(s);
	std::vector<std::string> res;
	std::string item;

	while( std::getline(ss, item, delim)){
		res.push_back(item);
	}

	return res;
}

std::shared_ptr<TreeNode> constructBinaryTree(const std::string& s){
	// this function construct binary from a leetcode string, like [5,4,7,3,null,2,null,-1,null,9]

	if (s.length() == 0) return nullptr;
	auto n = s.length();
	if (!(s[0] == '[' && s[n-1] == ']') ) throw std::runtime_error("wrong format");

	std::vector<std::string> tokens = split(s.substr(1,n-2), ',');

	std::vector<std::shared_ptr<TreeNode>> tree;
	std::string nullstr("null");
	unsigned m = tokens.size();
	for (auto& x:tokens){
		if ( x == nullstr) tree.emplace_back(nullptr);
		else tree.emplace_back(new TreeNode(stoi(x)));
	}

	for (unsigned i=0, j=1; i<m;i++){
		if (!tree[i]) continue;
		if (j<m) tree[i]->left = tree[j++];
		if (j<m) tree[i]->right = tree[j++];

	}
	return tree[0];
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


