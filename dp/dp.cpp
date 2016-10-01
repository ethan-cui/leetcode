#include <vector>
#include <algorithm>
#include "../utils.hpp"

using namespace std;

class Solution{

public:
	int combinationSum4(vector<int>& nums, int target){

		sort(nums.begin(), nums.end());
		vector<int> res(target+1, 0);
		res[0] = 1;

		for (int i=1; i<=target; i++){
			int cnt = 0;

			for (int num : nums){
				if (num > target || num > i)
					break;
				else
					cnt += res[i-num];
			}
			res[i] = cnt;

		}
		return res[target];
	}

	int wiggleMaxLenth(vector<int>& nums){
		vector<int> z1;int sign1 = 1; // start with increasing
		vector<int> z2;int sign2 = -1; // start with increasing
		for (unsigned i=0; i<nums.size();i++){
			if(i==0){
				z1.push_back(nums[i]);
				z2.push_back(nums[i]);
			} else {
				if ((nums[i] - nums[i-1]) * sign1 > 0){
					z1.push_back(nums[i]);
					sign1 *= -1;
				} else {
					int last = z1.size() -1;
					z1[last] = nums[i];
				}

				if ( (nums[i] - nums[i-1])*sign2 >0) {
					z2.push_back(nums[i]);
					sign2 *= -1;
				} else {
					int last = z2.size() -1;
					z2[last] = nums[i];
				}
			}
		}

		if (z1.size() >=z2.size()){
			return z1.size();
		} else {
			return z2.size();
		}
	}


int lastRemaining(int n) {
    if (n == 1) return 1;
    n = n % 2 ? n - 1 : n;
    if (n == 2) return 2;
    return n % 4 == 0 ? 4*lastRemaining(n/4) - 2:4*lastRemaining(n/4);
}	

	int lastRemaining2(int n){
		if (n == 1) return 1;
		return 2*(n/2 + 1 - lastRemaining2(n/2));
	}


};	

int main(){

	Solution s;

	//// combinationSum4
	//vector<int> a = {4,3,5,7};
	//cout << s.combinationSum4(a,6) << endl;
	//cout << s.combinationSum4(a,8) << endl;

	//wiggleMaxLenth
	vector<int> a1 = {1,7,4,9,2,5};
	vector<int> a2 = {1,17,5,10,13,15,10,5,16,8};
	vector<int> a3 = {1,2,3,4,5,6,7,8,9};
	cout << s.wiggleMaxLenth(a1) << endl;
	cout << s.wiggleMaxLenth(a2) << endl;
	cout << s.wiggleMaxLenth(a3) << endl;

	// last remaining
	for (int i =1; i<=10000;i++)
		if ( s.lastRemaining(i) != s.lastRemaining2(i))
		//cout << "for i =" << i << "result :" << s.lastRemaining(i) << "; result2 = " << s.lastRemaining2(i) << endl;
			cout << "for i =" << i << "result :" << (s.lastRemaining(i) == s.lastRemaining2(i)) << endl;


	return 0;
}
