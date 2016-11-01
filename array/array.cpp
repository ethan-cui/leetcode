#include <vector>
#include <string>
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

	vector<vector<int>> combine_1(int n, int k){
		vector<vector<int>> res;
		if (n<=0 || k<0 || k>n)
			return res;
		vector<int> valueList;
		combineHelper_1(n, k, 1, &res, valueList);

		return res;

	}

	void combineHelper_1(int n, int k, int pos, vector<vector<int>> *res, vector<int> valueList){
		if (k == 0){
			res->push_back(valueList);
			return;
		}

		for (int i=pos; i<=n; i++){
			vector<int> valueList_temp(valueList);
			valueList_temp.push_back(i);
			combineHelper_1(n, k-1, i+1, res, valueList_temp);
		}
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

	// 216. combinationSum3
	//vector<vector<int>> combinationSum3(int k, int n){
		//vector<vector<int>> res;

		//if (k <=0 || n<=0 || n > 45)
			//return res;
		//vector<int> l = {1,2,3,4,5,6,7,8,9};

		//vector<vector<int>> temp = combineHelper(k, l);
		//for (auto x: temp){
			//int sum = accumulate(x.begin(), x.end(), 2);
			//if (sum == n)
				//res.push_back(x);
		//}
		//return res;
	//}

	// 228. summaryRanges
	vector<string> summaryRanges(vector<int>& nums){

		vector<string> res;
		string arrow("->");
		if (nums.size() == 1){
			res.push_back(to_string(nums[0]));
			return res;
		}
		else{
			bool restart=true;
			int start=0;
			int end=0;
			for (unsigned i=0; i<nums.size(); i++){
				if (restart) {
					start = nums[i];
					restart = false;
				}
				if (i<nums.size()-1){
					if (nums[i+1]==nums[i]+1)
						continue;
					else{
						if (start==nums[i]){
							res.push_back(to_string(start));
							restart=true;
						}
						else{
							end=nums[i];
							restart=true;
							res.push_back(to_string(start) + arrow + to_string(end));
						}
					}
				}
				else{
					if (start==nums[i])
						res.push_back(to_string(start));
					else{
						end = nums[i];
						res.push_back(to_string(start) + arrow + to_string(end));
					}
				}
			}
		}

		return res;
	}

	vector<string> summaryRanges_1(vector<int>& nums){
		vector<string> res;
		if( nums.size() == 0) return res;

		int i=0, j=0; // two pointers for positions
		int max_pos = nums.size() - 1;
		string arrow("->");

		if (max_pos == 0) {
			res.push_back(to_string(nums[i]));
			return res;
		}

		while(i<=max_pos){
			while ( j<max_pos && nums[j+1]-nums[j] == 1)
				j++;
			if (j == i)
				res.push_back(to_string(nums[i]));
			else
				res.push_back(to_string(nums[i]) + arrow + to_string(nums[j]));
			j++;
			i=j;
		}
		return res;
	}

	vector<vector<int>> subsetsWithDup(vector<int>& nums){

		vector<vector<int>> res;
		if (nums.size() == 0) return res;
		sort(nums.begin(), nums.end());

		vector<int> subset;
		subsetsWithDupHelper(nums, 0, &res, subset);
		return res;
	}

	void subsetsWithDupHelper(vector<int> & nums, unsigned pos, vector<vector<int>> * res, vector<int> subset){
		res->push_back(subset);
		for (unsigned i=pos; i<nums.size(); i++){
			if (i>pos && nums[i-1] == nums[i]) continue;
			//subset.push_back(nums[i]);
			//subsetsWithDupHelper(nums, i+1, res, subset);
			//subset.pop_back();
			
			vector<int> subset_temp(subset);
			subset_temp.push_back(nums[i]);
			subsetsWithDupHelper(nums, i+1, res, subset_temp);
		}
	}

	vector<vector<int>> permute(vector<int>& nums){
		vector<vector<int>> res;
		if (nums.size() == 0) return res;
		vector<int> valueList;
		permuteHelper(nums, 0, &res, valueList);
		
		return res;
	}

	void permuteHelper(vector<int>& nums, unsigned pos, vector<vector<int>> *res, vector<int> valueList){
		if (pos == nums.size()){
			res->push_back(valueList);
			return;
		}

		for (unsigned i=pos; i<nums.size(); i++){
			int temp = nums[pos] ^ nums[i];
			nums[pos] ^= temp;
			nums[i] ^= temp;
			valueList.push_back(nums[pos]);
			permuteHelper(nums, pos+1, res, valueList);
			valueList.pop_back();
			nums[pos] ^= temp;
			nums[i] ^= temp;
		}
	}
	vector<vector<int>> permute_1(vector<int>& nums){
		vector<vector<int>> res;
		if (nums.size() == 0) return res;
		permuteHelper(nums, 0, &res);
		
		return res;
	}

	void permuteHelper(vector<int>& nums, unsigned pos, vector<vector<int>> *res){
		if (pos == nums.size()){
			res->push_back(nums);
			return;
		}
		// we actually do not need the valueList, in nums, it's inplace swap.
		for (unsigned i=pos; i<nums.size(); i++){
			int temp = nums[pos] ^ nums[i];
			nums[pos] ^= temp;
			nums[i] ^= temp;
			permuteHelper(nums, pos+1, res);
			nums[pos] ^= temp;
			nums[i] ^= temp;
		}
	}

	vector<vector<int>> permuteUnique(vector<int>& nums){
		vector<vector<int>> res;
		if (nums.size() == 0) return res;

		vector<int> valueList;
		sort(nums.begin(), nums.end());
		permuteUniqueHelper(nums, 0, &res, valueList);

		return res;


	}

	void permuteUniqueHelper(vector<int>& nums,unsigned pos, vector<vector<int>> *res, vector<int> valueList){
		if (pos == nums.size()){
			res->push_back(valueList);
			return;
		}

		for (unsigned i=pos; i<nums.size(); i++){
			if (i>pos && nums[pos] == nums[i]) continue;
			if (i>pos && nums[i-1] == nums[i]) continue;
		

			int temp = nums[pos] ^ nums[i];
			nums[pos] ^= temp;
			nums[i] ^= temp;
			valueList.push_back(nums[pos]);
			permuteUniqueHelper(nums, pos+1, res, valueList);
			valueList.pop_back();
			nums[pos] ^= temp;
			nums[i] ^= temp;
		}
	}
};

int main(){

	Solution s;
	// 47 permuteUnique
	vector<int> a = {1,2,2,1,3,3,4};
	vector<vector<int>> temp = s.permuteUnique(a);

	//// 46 permute
	//vector<int> a = {1,2,3,4};
	//vector<vector<int>> temp = s.permute_1(a);

	////90. subsetsWithDup
	//vector<int> a = {1,2,2,3,3};
	//vector<vector<int>> temp = s.subsetsWithDup(a);

	//// combine
	//vector<vector<int>> temp = s.combine(2, 4);
	//vector<vector<int>> temp = s.combine_1(20, 16);

	// 39 combinationSum
	//vector<int> a = {3,2, 6, 7};
	//vector<vector<int>> temp = s.combinationSum(a, 7);

	//// 40 combinationSum2
	//vector<int> a = {10, 1, 2, 7, 6, 1, 5};
	//vector<vector<int>> temp = s.combinationSum2(a, 8);
	
	//// 228. summaryRanges
	//vector<int> v{1,2,3,4,7,8, 10};
	//cout << s.summaryRanges(v) << endl;
	//cout << s.summaryRanges_1(v) << endl;


	//vector<vector<int>> temp = s.combinationSum3(3, 9);
	//cout << temp.size() << endl;
	

	for(auto& x:temp)
		cout << x << endl;


	return 0;
}
