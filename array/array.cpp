#include <vector>
#include <unordered_map>
#include <iterator>
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

	// 47 Permutation II
	vector<vector<int>> permuteUnique(vector<int>& nums){
		vector<vector<int>> res;
		if (nums.size() == 0) return res;
		vector<int> valueList;
		vector<int> visited(nums.size(), 0);
		sort(nums.begin(), nums.end());

		permuteUniqueHelper(nums, visited, &res, valueList);

		return res;


	}

	void permuteUniqueHelper(vector<int>& nums, vector<int>& visited, vector<vector<int>> *res, vector<int> valueList){
		if (valueList.size() == nums.size()){
			res->push_back(valueList);
			return;
		}

		for (unsigned i=0; i<nums.size(); i++){
			if (visited[i] == 1 || (i>0 && nums[i-1] == nums[i] && visited[i-1] == 0)) continue;
			valueList.push_back(nums[i]);
			visited[i] = 1;
			permuteUniqueHelper(nums, visited, res, valueList);
			valueList.pop_back();
			visited[i] = 0;
		}
	}

	// 89 grayCode
	vector<int> grayCode(int n){
		vector<int> res;
		if (n == 0) {
			res.push_back(0);
			return res;
		}
		if (n > 32) return res;
		if (n == 1) {
			res.push_back(0);
			res.push_back(1);
			return res;
		}
		vector<int> temp = grayCode(n-1);
		for (unsigned i=temp.size(); i>0; i--)
			temp.push_back(temp[i-1] | 1<<(n-1));

		return temp;
	}

	// 93 restoreIpAddresses
	vector<string> restoreIpAddresses(string s){
		vector<string> res;
		if (s.length() == 0 || s.length()>12) return res;
		string value;
		restoreIpAddressesHelper(s, 0, 1, &res, value);
		return res;

	}

	void restoreIpAddressesHelper(string s, unsigned pos, int cnt, vector<string>*res, string value){
		if (pos >= s.length()) return;
		if (cnt == 4){
			int temp = stoi(s.substr(pos));
			if (temp > 255 || (s[pos]=='0' && (temp != 0)) || (temp == 0 && pos<s.length()-1)){
				return;
			} else {
				res->push_back(value  + s.substr(pos));
				return;
			}
		}

		for (int i=pos; i<pos+3; i++){
			int temp = stoi(s.substr(pos, i-pos+1));
			if (temp > 255 || (s[pos]=='0' && (temp != 0)) || (temp == 0 && i>pos))
				return;
			string value_temp(value);
			value_temp += (s.substr(pos, i-pos+1)+ string("."));
			restoreIpAddressesHelper(s, i+1, cnt+1, res, value_temp);
		}
	}

	void nextPermutation(vector<int> & nums){
		int k=-1, j=0;
		cout << "before " << nums << endl;
		for (unsigned i=0; i<nums.size()-1; i++){
			if (nums[i+1] - nums[i] > 0)
				k = i;
		}

		if (k == -1){
			std::reverse(nums.begin(), nums.end());
			cout << "after " << nums << endl;
			return;
		}

		for (unsigned i=k+1; i<nums.size(); i++){
			if (nums[i] > nums[k])
				j = i;
		}

		int temp = nums[k] ^ nums[j];
		nums[k] = temp^nums[k];
		nums[j] = temp^nums[j];

		vector<int>::iterator it = nums.begin();
		std::advance(it, k+1);
		std::reverse(it, nums.end());

		cout << "after " << nums << endl;
	}

	// 60 permutation sequence getPermutation
	string getPermutation_1(int n, int k){
		// this one does not pass because time limit exceeded
		string res;
		if (n < 1 || n > 9 || k<1) return res;
		vector<int> x;
		for (int i=1; i<=n; i++)
			x.push_back(i);

		for (int i=1; i<k; i++)
			nextPermutation(x);
		
		for (auto i:x)
			res += to_string(i);
		return res;
	}

	string getPermutation(int n, int k){
		string res;
		if (n < 1 || n > 9 || k<1) return res;

		vector<int> a = {0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

		if (k>a[n]) return res;
		vector<int> x;
		for (int i=1; i<=n; i++) x.push_back(i);

		while(k != 0){
			for (int i=1; i<=n; i++){
				if (k == a[i]){
					vector<int>::iterator it = x.begin();
					std::advance(it, n-i);
					reverse(it, x.end()); // in this case, it is a reverse
					k -= a[i];
					break;
				}
				if (i<n && k > a[i] && k < a[i+1]){
					vector<int>::iterator it = x.begin();
					std::advance(it, n-i);
					std::reverse(it, x.end());
					k -= a[i];
					nextPermutation(x);
				}
			}
		}
		for (auto i:x)
			res += to_string(i);
		return res;
	}

	// 131 Palindrome partition
	bool checkPalindrome(string s){
		return s == string(s.rbegin(), s.rend());
	}

	vector<vector<string>> partition(string s){
		vector<vector<string>> res;
		if (s.length() == 0) return res;
		vector<string> valueList;
		partitionHelper(s, 0, &res, valueList);
		return res;
	}

	void partitionHelper(string s, unsigned pos, vector<vector<string>> *res, vector<string> &valueList){
		if (pos == s.length()){
			res->push_back(valueList);
			return;
		}

		for (unsigned i=pos; i<s.length(); i++){
			string temp = s.substr(pos, i-pos+1);
			if (!checkPalindrome(temp)) continue;
			valueList.push_back(temp);
			partitionHelper(s, i+1, res, valueList);
			valueList.pop_back();
		}
	}

	// 17 letterCombinations
	vector<string> letterCombinations(string digits){
		unordered_map<char, string> d = {
			{'2', string("abc")},
			{'3', string("def")},
			{'4', string("ghi")},
			{'5', string("jkl")},
			{'6', string("mno")},
			{'7', string("pqrs")},
			{'8', string("tuv")},
			{'9', string("wxyz")}
		};

		vector<string> res;
		if (digits.length() == 0) return res;

		vector<string> a;
		for (unsigned i=0; i<digits.length(); i++)
			a.push_back(d[digits[i]]);
		string str("");
		res.push_back(str);
		vector<string> temp;
		for (unsigned k=0; k<a.size(); k++){
			temp = res;
			res.clear();
			for (unsigned i=0; i<a[k].length(); i++){
				for (unsigned j=0; j<temp.size();j++){
					res.push_back(temp[j] + a[k].substr(i, 1));
				}
			}
		}
		return res;

	}

	// 132 minCut
	bool checkPalindromeOpt(string s){
		if (s.length() == 0) return false;
		int lo = 0, hi = s.length()-1;
		while (lo < hi){
			if (s[lo] != s[hi]) return false;
			lo++;
			hi--;
		}
		return true;
	}

	//int minCut(string s){
		//if (s.length() == 0) return;
		//if (s.length() == 1) return 0;

	vector<int> twoSum(vector<int>& nums, int target){
		vector<int> res;
		if (nums.size() == 0) return res;
		vector<int> temp = nums;

		unsigned i=0, j=nums.size()-1;
		sort(nums.begin(), nums.end());
		while (i<=j){
			if (nums[i] + nums[j] > target)
				j--;
			else if (nums[i] + nums[j] < target)
				i++;
			else {
				for (unsigned k=0; k<temp.size(); k++){
					if (temp[k] == nums[i])
						res.push_back(k);
					else if (temp[k] == nums[j])
						res.push_back(k);
					if (res.size() == 2)
						return res;
				}
			}
		}
		return res;
	}



};

int main(){

	Solution s;
	// 1 twoSum
	//vector<int> temp = {2, 7, 11, 15};
	vector<int> temp = {3,2, 4};
	cout << s.twoSum(temp, 6) << endl;

	//// 17 letterCombination
	//vector<string> temp = s.letterCombinations(string("23"));

	
	//// 131 patition	
	//vector<vector<string> > temp = s.partition("aba");
	//cout << s.partition("aab") << endl;
	//cout << s.partition("aba") << endl;

	////60. getPermutation
	//string res = s.getPermutation(5,120);
	//cout << res << endl;
	
	//// 31. nextPermutation
	//vector<int> a = {3,2,1};
	//s.nextPermutation(a);

	////93 restoreIpAddresses
	//cout << s.restoreIpAddresses(string("25525511135")) << endl;
	//cout << s.restoreIpAddresses(string("22725511135")) << endl;
	//cout << s.restoreIpAddresses(string("2511135")) << endl;
	//cout << s.restoreIpAddresses(string("0279245587303")) << endl;
	//cout << s.restoreIpAddresses(string("010010")) << endl;

	//// 89 grayCode
	//cout << s.grayCode(2) << endl;
	
	//// 47 permuteUnique
	//vector<int> a = {1,1,2,2,3,3,4};
	//vector<vector<int>> temp = s.permuteUnique(a);
	//cout << temp.size() << endl;

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
