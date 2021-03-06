#include <vector>
#include <sstream>
#include <array>
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

// 155. Min Stack
class MinStack {
public:
/** initialize your data structure here. */
	MinStack() {}

	void push(int x) {
		if (sk.empty()) {
			sk.push(x);
			sk_min.push(x);
		} else {
			int cur_min = sk_min.top();
			sk.push(x);
			if (cur_min > x) sk_min.push(x);
			else sk_min.push(cur_min);
		}
	}

	void pop() {
		sk.pop();
		sk_min.pop();
	}

	int top() {
		return sk.top();
	}

	int getMin() {
		return sk_min.top();
	}

	stack<int> sk;
	stack<int> sk_min;

};

// 225. Implement Stack using Queues
class Stack{
public:
	queue<int> q1, q2;

	void push(int x){
		if (q1.empty() && q2.empty())
			q1.push(x);
		else if (q1.empty())
			q2.push(x);
		else q1.push(x);
	}

	void pop(){
		if (q1.empty()){
			int sz = q2.size();
			for (int i=0; i<sz-1;i++){
				q1.push(q2.front());
				q2.pop();
			}
			q2.pop();
		} else {
			int sz = q1.size();
			for (int i=0; i<sz-1; i++){
				q2.push(q1.front());
				q1.pop();
			}
			q1.pop();
		}
	}

	int top(){
		int res=0;
		if (q1.empty()){
			int sz = q2.size();
			for (int i=0; i<sz-1;i++){
				q1.push(q2.front());
				q2.pop();
			}
			res = q2.front();
			q1.push(q2.front());
			q2.pop();
		} else {
			int sz = q1.size();
			for (int i=0; i<sz-1; i++){
				q2.push(q1.front());
				q1.pop();
			}
			res = q1.front();
			q2.push(q1.front());
			q1.pop();
		}
		return res;
	}

	bool empty(){
		return q1.empty() && q2.empty();
	}

};

// 232. Implement Queue using Stacks
class Queue{
public:
	stack<int> sk1, sk2;
	void push(int x){
		if (sk2.empty()) {
			sk2.push(x);
		} else {
			while(!sk2.empty()){
				sk1.push(sk2.top());
				sk2.pop();
			}
			sk2.push(x);
			while(!sk1.empty()){
				sk2.push(sk1.top());
				sk1.pop();
			}
		}
	}

	void pop(){
		if (!sk2.empty()) sk2.pop();
	}

	int peek(){
		return sk2.top();
	}

	bool empty(){
		return sk2.empty();
	}


};

// 173. Binary Search Tree Iterator
class BSTIterator{
public:
	stack<shared_ptr<TreeNode>> sk;
	bool processed;

	BSTIterator(){}

	BSTIterator(shared_ptr<TreeNode> root){
		processed = false;
		if (root){
			sk.push(root);
			shared_ptr<TreeNode> temp = sk.top();
			while (temp->left) {
				sk.push(temp->left);
				temp = temp->left;
			}
			processed = true;
		}
	}

	bool hasNext(){
		return !sk.empty();
	}

	int next(){
		if (!hasNext()) return 0;
		shared_ptr<TreeNode> temp = sk.top();
		while (temp->left && !processed) {
			sk.push(temp->left);
			temp = temp->left;
		}
		processed = true;
		int res = temp->val;
		sk.pop();
		if (temp->right){
			sk.push(temp->right);
			processed = false;
		}
		return res;
	}
};



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

	// 145. Binary Tree Postorder Traversal
	vector<int> postorderTraversal(shared_ptr<TreeNode> root){
		vector<int> res;
		if (!root) return res;
		stack<shared_ptr<TreeNode>> sk;
		sk.push(root);
		shared_ptr<TreeNode> temp;


		while(!sk.empty()){
			temp = sk.top();
			sk.pop();
			
			if (temp){
			sk.push(temp->left);
			sk.push(temp->right);
			res.push_back(temp->val);
			}
		}
		return vector<int>(res.rbegin(), res.rend());
	}

	// 150. Evaluate Reverse Polish Notation
	int evalRPN(vector<string>& tokens){
		if (tokens.size() == 0) return 0;

		stack<int> sk;
		string a = string("+");
		string b = string("-");
		string c = string("*");
		string d = string("/");

		for (unsigned i=0; i<tokens.size(); i++){
			string token = tokens[i];
			if (token!=a && token!=b && token!=c && token!=d){
				sk.push(stoi(token));
			} else {
				int second = sk.top();
				sk.pop();
				int first = sk.top();
				sk.pop();
				if (token == a) sk.push(first + second);
				else if (token == b) sk.push(first - second);
				else if (token == c) sk.push(first * second);
				else  sk.push(first / second);
			}
		}

		return sk.top();
	}

	// 224. Basic Calculator
	int calculate_old(string s){
		if (s.length() == 0) return 0;

		stack<int> sk;
		int tempsum=0;
		int sign = 1;
		for (unsigned i=0; i<s.length(); i++){
			
			if(s[i] == ' ') continue;
			if (s[i] == '(' ) {
				if (i>0) sign = s[i-1] == '+' ? 1 : -1;
				sk.push(tempsum);
				sk.push(sign);
				tempsum = 0;
			} else if (s[i] >= '0' && s[i] <= '9') {
			       tempsum += (static_cast<int> (s[i]) - 48) * sign;
			} else if (s[i] == '-') {
				sign = -1;
			} else if (s[i] == '+') {
				sign = 1;
			} else {
				sign = sk.top();
				sk.pop();
				tempsum = sign * tempsum + sk.top();
				sk.pop();
			}
			cout << tempsum << endl;
		}
		return tempsum;
	}

	int calculate(string s){
		if (s.length() == 0) return 0;

		stack<int> sk;
		int tempsum=0, num = 0;
		int sign = 1;
		for (unsigned i=0; i<s.length(); i++){
			if (s[i] == ' ') continue;
			if (s[i] == '(') {
				sk.push(tempsum);
				sk.push(sign);
				sign = 1;
				tempsum = 0;
				
			} else if (s[i] == ')') {
				tempsum += num * sign;
				num = 0;
				sign = sk.top();
				sk.pop();
				tempsum = sk.top() + tempsum * sign;
				sk.pop();

			} else if (s[i] == '+' || s[i] == '-'){
				tempsum += num * sign;
				num = 0;
				sign = s[i] == '+' ? 1 : -1;
			} else {
				num = num * 10 + static_cast<int> (s[i]) - 48;
			}
		}
		tempsum += num * sign;
		return tempsum;
	}

	// 316. Remove Duplicate Letters
	string removeDuplicateLetters_old(string s){
		// sturcture of solution
		// 1. for element that cnt > 1(means they still have something later, they must in increasing order.
		// 2. for 

		string res;
		if (s.length() == 0) return res;

		vector<char> v;
		unordered_map<char, int> mp;

		for (unsigned i=0; i<s.length(); i++){
			if (mp.find(s[i]) == mp.end()) {
				mp[s[i]] = 1;
			} else {
				mp[s[i]] += 1;
			}
		}

		for (unsigned i=0; i<s.length(); i++){
			mp[s[i]] -=1;
			if (find(v.begin(), v.end(), s[i]) != v.end()) {
				continue;
			}
			if (v.size() == 0 ) {
				v.push_back(s[i]);
				continue;
			}
			if (v.back() < s[i]){
				v.push_back(s[i]);
				continue;
			}
			while (v.back() > s[i] && mp[v.back()] >0){
				v.pop_back();
			}
			v.push_back(s[i]);
		}

		// need to document
		return string(v.begin(), v.end());

	}

	string removeDuplicateLetters(string s){
		string res;
		if (s.length() == 0) return res;
		vector<int> cnt(26, 0), exist(26, 0);

		for (char x:s) cnt[x-'a']++;

		for (char x:s){
			cnt[x-'a']--;
			if (res.length() == 0){
				res.push_back(x);
				exist[x-'a'] = 1;
				continue;
			} else if (exist[x-'a']) continue;
			if (res.back() < x){
				res.push_back(x);
				exist[x-'a'] = 1;
				continue;
			}
			while(res.back() > x && cnt[res.back()-'a'] > 0) {
				exist[res.back()-'a'] = 0;
				res.pop_back();
			}
			res.push_back(x);
			exist[x-'a'] = 1;
		}
		return res;
	}

	// 331. Verify Preorder Serialization of a Binary Tree
	bool isValidSerialization(string preorder){
		if (preorder.length() == 0) return true;
		stringstream ss(preorder);
		string item;
		stack<string> sk;
		string first, second, third;
		string h("#");

		while (getline(ss, item, ',')){
			cout << item << " ";
			if (sk.size() < 3){
				sk.push(item);
				continue;
			}

			third = sk.top();
			sk.pop();
			second = sk.top();
			sk.pop();
			first = sk.top();
			sk.push(second);
			sk.push(third);

			while (sk.size() > 2 && first != h && second == h && third == h) {
				sk.pop();
				sk.pop();
				sk.pop();
				sk.push(h);

				if (sk.size() > 2){
					third = sk.top();
					sk.pop();
					second = sk.top();
					sk.pop();
					first = sk.top();
					sk.push(second);
					sk.push(third);
				}
			}
			sk.push(item);
		}
		if (sk.size() > 2){

			third = sk.top();
			sk.pop();
			second = sk.top();
			sk.pop();
			first = sk.top();
			sk.push(second);
			sk.push(third);

			while (sk.size() > 2 && first != h && second == h && third == h) {
				sk.pop();
				sk.pop();
				sk.pop();
				sk.push(h);

				if (sk.size() > 2){
					third = sk.top();
					sk.pop();
					second = sk.top();
					sk.pop();
					first = sk.top();
					sk.push(second);
					sk.push(third);
				}
			}
		}
		
		 cout << endl;
		 cout << sk << endl; 
		return sk.size() ==1 && sk.top() == h;

	}
	bool test(string preorder){

	    if (preorder.empty()) return false;
	        preorder+=',';
		    int sz=preorder.size(),idx=0;
		        int capacity=1;
			    for (idx=0;idx<sz;idx++){
				            if (preorder[idx]!=',') continue;
					            capacity--;
						            if (capacity<0) return false;
							            if (preorder[idx-1]!='#') capacity+=2;
								        }
			        return capacity==0;
	}


		

};

int main(){

	Solution s;
	// 331. Verify Preorder Serialization of a Binary Tree
	string str("9,#,#,#,#,#,#,#,3,4,1,2,6");
	//string str("9,3,4,#,#,1,#,#,2,#,6,#,#");
	cout << s.isValidSerialization(str) << endl;
	cout << s.test(str) << endl;

	//// 173. Binary Search Tree Iterator
	//auto treeRoot = constructBinaryTree("[3,9,20,null,null,15,7]");
	//BSTIterator bsti (treeRoot);
	//while (bsti.hasNext()) cout << bsti.next()<< endl;


	//// 155. Min Stack
	//MinStack ms = MinStack();
	//ms.push(-2);
	//ms.push(0);
	//ms.push(-1);
	//cout << ms.getMin() << endl;

	//// 316. Remove Duplicate Letters
	//string str("cbacfdcbeaf");
	//cout << s.removeDuplicateLetters(str) << endl;


	//// 224. Basic Calculator
	////string str("1+((4+5+2)-3)+(16+8)");
	////string str("2147483647");
	//string str("1-(5)");
	//cout << s.calculate(str) << endl;


	//// 150. Evaluate Reverse Polish Notation
	
	////vector<string> v{"2", "1", "+", "3", "*"};
	//vector<string> v{"4", "13", "5", "/", "+"};
	//cout << s.evalRPN(v) << endl;


	//// 145. Binary Tree Postorder Traversal
	//auto treeRoot = constructBinaryTree("[3,9,20,null,null,15,7]");
	//cout << s.postorderTraversal(treeRoot) << endl;
	

	//// 144. Binary Tree Preorder Traversal
	//auto treeRoot = constructBinaryTree("[3,9,20,null,null,15,7]");
	//cout << s.preorderTraversal(treeRoot) << endl;
	


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
