#include <vector>
#include <algorithm>
#include "../utils.hpp"

using namespace std;


class Solution{

public:
	// 77. Combinations
	vector<vector<int>> combine(int k, int n){
		vector<vector<int>> res;
		if (k>n) return res;
		if (k<0 || n<0) return res;

		vector<int> l = range(1, n+1); 
		res =  combineHelper(k, l);
		return res;


	}


	vector<vector<int>>  combineHelper(int k, vector<int> l){
		if (k == 0){
			vector<vector<int>> res;
			vector<int> temp;
			res.push_back(temp);
			return  res;
		}

		int n = l.size();
		if (k == n){

			vector<vector<int>> res;
			res.push_back(l);
			return res;
		}

		int elem = l.back();
		l.pop_back();
		vector<vector<int>> res = combineHelper(k-1, l);
		//for (unsigned i=0; i<res.size();i++){
			//res[i].push_back(elem);
		//}
		for (auto &ls:res)
			ls.push_back(elem);
		vector<vector<int>> res2 = combineHelper(k, l);
		for (auto x:res2)
			res.push_back(x);
		return res;
	}


	// 39. combinationSum
	vector<vector<int>> combinationSum(vector<int>& candidate, int target){

		sort(candidate.begin(), candidate.end());


		vector<vector<int>> res;
		if (candidate.size() == 0 || target <= 0)
			return res;

		vector<int> valueList;
		combinationSumHelper(candidate, target, 0, &res, valueList);
		return res;
	}
	
	void combinationSumHelper(vector<int> & candidate, int target, int pos, vector<vector<int>> * res, vector<int> valueList){
		if (target < 0)
			return;
		if (target == 0){
			res->push_back(valueList);
			cout << "target = 0 " << valueList << endl;
			return;
		}
		for (unsigned i=pos; i<candidate.size(); i++){
			if (target < candidate[i])
				return;
			vector<int> valueList_temp(valueList);
			valueList_temp.push_back(candidate[i]);
			combinationSumHelper(candidate,target - candidate[i], i, res, valueList_temp);
		}
	}

	// 40. combinationSum2
	vector<vector<int>> combinationSum2(vector<int>& candidate, int target){

		vector<vector<int>> res;

		if (target<=0 || candidate.size() ==0)
			return res;

		sort(candidate.begin(), candidate.end());
		vector<int> valueList;

		combinationSumHelper2(candidate, target, 0, &res, valueList);
		return res;
	}

	void combinationSumHelper2(vector<int>& candidate, int target, unsigned pos, vector<vector<int>> * res, vector<int> valueList){

		if (target < 0)
			return;
		if (target == 0){
			res->push_back(valueList);
			return;
		}
		for (unsigned i = pos; i < candidate.size(); i++){
			if (target < candidate[i])
				return;
			// i> pos is key to remove the redundency and should continue instead of return.
			if (i > pos && candidate[i-1] == candidate[i]) continue;
			vector<int> valueList_temp(valueList);
			valueList_temp.push_back(candidate[i]);
			combinationSumHelper2(candidate, target-candidate[i], i+1, res, valueList_temp);
		}
	}

};

int main(){

	Solution s;

	//// combine
	//vector<vector<int>> temp = s.combine(2, 4);

	// 39 combinationSum
	//vector<int> a = {3,2, 6, 7};
	//vector<vector<int>> temp = s.combinationSum(a, 7);
	vector<int> a = {10, 1, 2, 7, 6, 1, 5};
	vector<vector<int>> temp = s.combinationSum2(a, 8);
	//cout << temp.size() << endl;
	for(auto& x:temp)
		cout << x << endl;


	return 0;
}
