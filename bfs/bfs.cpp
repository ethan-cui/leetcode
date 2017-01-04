#include <vector>
#include <string>
#include <algorithm>
#include "../utils.hpp"

using namespace std;


struct TreeNode {
	int val;
	TreeNode * left;
	TreeNode * right;
	TreeNode(int x): val(x), left(nullptr), right(nullptr){}

};


class Solution{

public:
	bool isSameTree(TreeNode* p, TreeNode* q){
		if ((!p) || (!q)){
			if ((!p) && (!q))
				return true;
			else
				return false;
		}
		

		if (p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right))
			return true;
		else
			return false;
	}

	bool isSymmetric(TreeNode* root){
		if (!root) return true; // When rool is nullptr



		return true;
	}

};

int main(){

	Solution s;

	
	//vector<int> a = {1,2,2,3,3};
	

	//for(auto& x:temp)
		//cout << x << endl;


	return 0;
}
