#include <vector>
#include <string>
#include "../utils.hpp"


using namespace std;


class Solution{

public:
	vector<vector<int>> subsets(const vector<int> & nums){
		vector<vector<int>> res;
		subsetsHelper(0, nums, &res);
		for (auto x: res)
			cout << x << endl;
		return res;


	}

	void subsetsHelper(int i, const vector<int> &nums, vector<vector<int>> * res){
		int n = nums.size();
		if (i == n) {
			vector<int> a;
			res->push_back(a);
			return;
		}

		subsetsHelper(i+1, nums, res);
		uint32_t N = res->size();
		for (uint32_t j=0; j<N; j++){
			vector<int> temp = (*res)[j];
			temp.push_back(nums[i]);
			res->push_back(temp);
		}
	}
	

};
int main(){

	cout << "hello world" << endl;
	Solution s;

	auto tree = constructBinaryTree("[5,4,7,3,null,2,null,-1,null,9]");
	cout << tree << endl;
	
	

	

	////// for subsets
	//vector<int> nums=range(10);
	//s.subsets(nums);


	

	return 0;
}

