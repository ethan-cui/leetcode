#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <string>
#include <iostream>
#include <map>
#include <typeinfo>
#include <ctype.h>
#include "../utils.hpp"


using namespace std;


class Solution{

public:
	int largestRectangleArea(vector<int>& heights){
		heights.push_back(0);
		int max = 0;
		stack<int> s;

		if (heights.size() == 0) return 0;
		if (heights.size() == 1) return heights[0];

		for (unsigned i=0; i<heights.size(); i++){
			if(s.empty() || heights[i] > heights[s.top()]){
				s.push(i);
			} else {
				while (!s.empty() && heights[s.top()] >= heights[i]){
					int temp = s.top();
					s.pop();
					int area;
					if (s.empty())
						area = i * heights[temp];
					else
						area = (i - s.top() - 1) * heights[temp];
					//cout <<i << temp <<  max << area << endl;
					if (max <= area){
						max = area;
					}
				}
				s.push(i);
			}
		}

		return max;
	}


	int reverse(int x){
		if (x == -2147483647 -1) return 0;
		int sign = x>=0?1:-1;
		x = x>=0?x:-1*x;
		int res = 0;
		if (x<10) return sign*x;
		while (x){
			//if (res>(~(1<<31))/10 || (res==(~(1<<31))/10 && x%10> (~(1<<31))%10)) return 0;
			if (res>(~(1<<31))/10 ) return 0;
			res = 10*res + x%10;
			x /=10;
		}
		return res*sign;
	}

	// 20 valid parenthesis
	bool isValid(string s){
		if (s.size() == 0) return true;
		if (s.size() % 2 == 1) return false;

		stack<char> st;

		for (unsigned i=0; i<s.size(); i++){
			char temp = s[i];
			if (temp == '(' || temp == '{' || temp == '[') st.push(temp);
			else if (st.empty()) return false;
			else if ((st.top() == '(' && temp == ')') ||( st.top() == '{' && temp == '}') || (st.top() == '[' && temp == ']')) st.pop();
			else return false;
		}
		if (st.empty()) return true;
		else return false;
	}

	// 71 Simplify path
	string simplifyPath(string path){
		stack<string> st;
		string s1(".");
		string s2("..");
		string s3("/");
		for (unsigned i=0; i<path.size()-1; ){
			unsigned j = 1;
			while (path[i+j] != '/' && i+j < path.size()) j++;
			string temp = path.substr(i+1, j-1);
			// the case !temp corresponds to "//" case the next char is '/'
			if ((temp.size() == 0)  || (!st.empty() && temp == s1)) {
				i += j;
				continue;
			}
			if (!st.empty() && temp == s2) {
				st.pop();
				i += j;
				continue;
			}
			if (st.empty() && (temp == s2 || temp == s1)){
				i += j;
				continue;
			}
			i += j;
			st.push(temp);
		}
		string res("");
		if (st.empty()) return s3;
		while (!st.empty()) {
			res = s3 + st.top() + res;
			st.pop();
		}
		return res;
	}

	// 42 traping rain water
	int trapHelper(vector<int>& height){
		int trap = 0, tempsum = 0;
		vector<unsigned> l;
		for (unsigned i=0; i<height.size(); i++){
			if (l.size() == 0) {
				l.push_back(i);
				continue;
			}
			if (height[i] < height[l.back()]){
				tempsum += height[i];
				continue;
			} else {
				trap += height[l.back()] * (i - l.back() - 1) - tempsum;
				tempsum = 0;
				l.push_back(i);
			}
		}
		return trap;
	}

	int trap(vector<int>& height){
		if (height.size() == 0) return 0;
		int v = *max_element(height.begin(), height.end());
		vector<int>::iterator it = find(height.begin(), height.end(), v);
		int trap = 0;
		vector<int> temp(height.begin(), ++it);
		trap += trapHelper(temp);
		vector<int> temp1(--it, height.end());
		std::reverse(temp1.begin(), temp1.end());
		trap += trapHelper(temp1);
		return trap;
	}

	int maximalRectangle(vector<vector<char>>& matrix){
		unsigned m = matrix.size();
		if (m == 0) return 0;
		unsigned n = matrix[0].size();
		if (n == 0) return 0;

		int res=0;
		vector<int> height(n, 0);
		for (unsigned i=0; i<m; i++){
			for (unsigned j=0; j<n; j++){
				if (matrix[i][j] == '0')
					height[j] = 0;
				else 
					height[j] += 1;
			}
			int cand = largestRectangleArea(height);
			if (cand >= res) res = cand;
		}
		return res;
	}

	void inorderTraversalHelper(vector<int>* res, shared_ptr<TreeNode> root){
		if (!root) return;
		inorderTraversalHelper(res, root->left);
		res->push_back(root->val);
		inorderTraversalHelper(res, root->right);
	}
	vector<int> inorderTraversal_recursive(shared_ptr<TreeNode> root){
		vector<int> res;
		if (!root) return res;
		inorderTraversalHelper(&res, root);
		return res;
	}
	
	vector<int> inorderTraversal(shared_ptr<TreeNode> root){
		vector<int> res;
		if (!root) return res;
		stack<shared_ptr<TreeNode>> sk;
		sk.push(root);

		shared_ptr<TreeNode> temp;
		bool processed = false; // the processed flag is a flag indicate wheather the left subtree has been pushed.
		while(!sk.empty()){
			temp = sk.top();
			while(temp->left && !processed) {
				sk.push(temp->left);
				temp = temp->left;
			}
			temp = sk.top();
			sk.pop();
			processed = true;
			res.push_back(temp->val);
			if (temp->right) {
				sk.push(temp->right);
				processed = false;
			}
				
		}
		return res;
	}


	// 103. Binary Tree Zigzag Level Order Traversal
	vector<vector<int> > zigzagLevelOrder(shared_ptr<TreeNode> root){
		vector<vector<int> > res;
		if (!root) return res;
		stack<shared_ptr<TreeNode>> sk1, sk2; // sk1 to start

		sk1.push(root);
		bool sk1_tag=true;
		shared_ptr<TreeNode> temp;

		while(!sk1.empty() || !sk2.empty()){
			vector<int> temp_res;
			if (sk1_tag) {
				while(!sk1.empty()){
					temp = sk1.top();
					if (temp) {
						temp_res.push_back(temp->val);
						sk2.push(temp->left);
						sk2.push(temp->right);
					}
					sk1.pop();
				}
				if (temp_res.size()) res.push_back(temp_res);
				sk1_tag = false;
			} else {
				while(!sk2.empty()){
					temp = sk2.top();
					if (temp){
						temp_res.push_back(temp->val);
						sk1.push(temp->right);
						sk1.push(temp->left);
					}
					sk2.pop();
				}
				if (temp_res.size()) res.push_back(temp_res);
				sk1_tag = true;
			}
		}
		return res;
	}

	vector<int> preorderTraversal1(shared_ptr<TreeNode> root){
		vector<int> res;
		if (!root) return res;
		stack<shared_ptr<TreeNode>> sk;
		sk.push(root);

		shared_ptr<TreeNode> temp;
		bool processed = false;
		res.push_back(root->val);
		while(!sk.empty()){
			temp = sk.top();
			while (temp->left && !processed){
				res.push_back(temp->left->val);
				sk.push(temp->left);
				temp = temp->left;
			}
			processed = true;
			temp = sk.top();
			sk.pop(); // pop out the nullptr
			if (temp->right){
				sk.push(temp->right);
				res.push_back(temp->right->val);// need to push in right now, next time when it popped out, will process its left
				processed = false;
			}
		}

		return res;
	}

	vector<int> preorderTraversal(shared_ptr<TreeNode> root){
		vector<int> res;
		if (!root) return res;
		stack<shared_ptr<TreeNode>> sk;
		sk.push(root);

		shared_ptr<TreeNode> temp;
		while(!sk.empty()){
			temp = sk.top();
			sk.pop();
			if (temp){
				res.push_back(temp->val);
				sk.push(temp->right);
				sk.push(temp->left);
			}
		}
		return res;
	}


};

int main(){

	Solution s;
	// 144. Binary Tree Preorder Traversal
	auto treeRoot = constructBinaryTree("[3,9,20,null,null,15,7]");
	cout << s.preorderTraversal(treeRoot) << endl;
	


	//// 103. Binary Tree Zigzag Level Order Traversal
	//auto treeRoot = constructBinaryTree("[3,9,20,null,null,15,7]");
	//cout << s.zigzagLevelOrder(treeRoot) << endl;


	//// 94. Binary Tree Inorder Traversal
	//auto treeRoot = constructBinaryTree("[1,null,2,3]");
	//cout << s.inorderTraversal(treeRoot) << endl;


	//// 85 Maximal Rectangle
	//vector<vector<char> > matrix = {{'0','1'},{'1','0'}};
	////vector<vector<char> > matrix = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
	////vector<vector<char> > matrix = {{1,0,1,0,0}, {1,0,1,1,1}, {1,1,1,1,1}, {1,0,0,1,0}};
	////cout << matrix << endl;
	////cout << matrix[0] << endl;
	//cout << s.maximalRectangle(matrix) << endl;

	//// 42 trapping rain water
	//vector<int> temp {0,1,0,2,1,0,1,3, 2,3,1,2,1};
	//cout << s.trap(temp) << endl;

	//// 71 Simplify Path
	////string path("/abc");
	//string path("/./bGWC/tUnSS/../lAqL/QkbTK/./nP");
	//cout << s.simplifyPath(path) << endl;


	//// 20 valid parenthesis
	//string temp("[()]{}");
	//cout << s.isValid(temp) << endl;




	//// 7. reversed integer
	//// 2147483647
	//int res = s.reverse(-2147483647-1);

	//// 84. Largest Rectangle in Histogram
	//vector<int> temp = {4,2,0,3,2,5};
	//int res = s.largestRectangleArea(temp);
	//cout << res << endl;

	return 0;

}
