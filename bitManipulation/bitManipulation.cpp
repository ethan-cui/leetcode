#include <vector>
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
	vector<int> countBits(int num){
		if (num == 0) return vector<int> (1, 0);

		vector<int> ret(num+1);
		int offset = 1;

		for (int i=0; i<=num; i++){
			if (i == 0) {
				ret[i] = 0;
				continue;
			}

			if (i == (offset<<1)){
				offset <<= 1;
				ret[i] = ret[i-offset] + 1;
			} else {
				ret[i] = ret[i-offset] + 1;

			}

		}
		return ret;
	}


	bool canWinNim(int n){
		return (! (n%4==0));
	}
	int hammingWeight(uint32_t n){


		int count = 0;
		//vector<int> bit;

		while (n != 0){

			if (n%2 == 1)
				count++;
			//bit.push_back(n%2);
			n = n/2;
		}
		//for (vector<int>::reverse_iterator it=bit.rbegin(); it!=bit.rend(); it++) 
			//cout << *it;
		
		return count;
	}

	int hammingWeight2(uint32_t n){

		int cnt = 0;
		while (n){
			if ((n&1) == 1) cnt++;
			n >>=1 ;
		}
		return cnt;
	}




	uint32_t reverseBits(uint32_t n){

		unsigned N=32;
		uint32_t res=0;
		for (unsigned i=0; i<N;i++){
			res += pow(2, 31-i)*(n%2);
			n = n/2;
		}
		return res;
	}
	
	uint32_t reverseBits1(uint32_t n){
		uint32_t res=0;
		for (unsigned i=0; i<31;i++){
			res += (n&1);
			res <<=1;
			n>>=1;
		}

		return res + (n&1);
	}


	int romanToInt(string s){
		map<char,int> roman;
		roman['M'] = 1000;
		roman['D'] = 500;
		roman['C'] = 100;
		roman['L'] = 50;
		roman['X'] = 10;
		roman['V'] = 5;
		roman['I'] = 1;

		string romanChar("MDCLXVI");
		int res = 0;

		for(unsigned i=0; i < romanChar.size(); i++){
			char curChar = romanChar[i];
			unsigned index = s.rfind(curChar);

			if (index < s.size()){
			// if 
				string sub = s.substr(0,index+1);
				for (unsigned j=0; j<sub.size(); j++){
					if (romanChar.find(sub[j]) > romanChar.find(curChar) && sub[j] != curChar)
						// if something is after the current, we subtract
						res += -1* roman[sub[j]];
					else
						res += roman[sub[j]];
				}
				s = s.substr(index+1);
			}

		}

		cout << res << endl;
		//string test("AAA");
		//cout << test.find('A') << endl;
		//cout << test.substr(0,1) << endl;
		return res;

	}

	void rotateImp(vector<int>& nums, int k){
		vector<int>::reverse_iterator it_h = nums.rbegin()+k;
		vector<int>::reverse_iterator it_t = nums.rbegin();

		int temp[k];
		int i=k;
		for (;it_h!=nums.rend();it_t++,it_h++,i--){
			if (i-1>=0)
				temp[i-1]=*it_t;
			*it_t = *it_h;
		}

		for (int j=0; j<k; j++)
			nums[j] = temp[j];
		return;
	}

	void rotateImp1(vector<int>& nums, int k){
		int n=nums.size();
		vector<int>::iterator it_t = nums.begin()+ n-k;
		vector<int>::iterator it_h = nums.begin();

		int temp[n-k];
		int i=0;
		for (;it_t!=nums.end();it_t++,it_h++,i++){
			if (i<n-k)
				temp[i]=*it_h;
			*it_h = *it_t;
		}

		for (int j=0; j<n-k; j++)
			nums[k+j] = temp[j];
		return;
	}

	void rotate(vector<int>& nums, int k){
		if (nums.size()==1 || k==0 || k % nums.size()==0) return;
		if (k > nums.size()){
			if (k % nums.size() <=nums.size() / 2){
				rotateImp(nums,k%nums.size());
				return;
			}
			else {
				rotateImp1(nums,k%nums.size());
				return;
			}
		}
		else if(k<=nums.size() / 2){
			rotateImp(nums, k);
			return;
		}else {
			rotateImp1(nums,k);
			return;
		}
	}

	int singleNumber(vector<int>& nums){
		int single=0;
		for (int i:nums)  single^=i;
		return single;
	}

	int addDigits(int num){
		if (num == 0) return 0;
		if (num%9 == 0) return 9;
		else return num%9;
	}


	int missingNumber(vector<int>& nums){
		int n = nums.size();
		int missing = 0;
		for (int i=0; i<=n; i++) missing ^= i;
		for (int i:nums) missing ^= i;
		return missing;
	}


	bool isPowerOfTwo(int n){

		if (n <= 0) return false;
		int cnt = 0;
		while (n){
			if ((n&1) == 1) cnt++;
			n >>=1 ;
		}
		if (cnt == 1) return true;
		else return false;
	}

	bool isPowerOfTwo1(int n){
		if (n<=0) return false;
		else return !(n&(n-1));
	}

	void subsets(vector<int>& nums){
		vector<int> subs;
		subsetsHelper(nums, 0, &subs);
	};

	void subsetsHelper(const vector<int>& nums, int m, vector<int>* subs){
		if (!subs->empty())
			cout << *subs;
		cout << endl;

		for (unsigned i=m; i<nums.size();i++){
			subs->emplace_back(nums[i]);
			subsetsHelper(nums, i+1, subs);
			subs->pop_back();
		}
	}

	vector<vector<int>> subsets1(vector<int>& nums){
		vector<vector<int>> res;
		subsets1Helper(0, nums,&res);

		for (auto elem:res){
			cout << elem << endl;
		}

		return res;
	}

	void subsets1Helper(int i, vector<int>& nums, vector<vector<int>>* res){
		int n = nums.size();
		if (i == n){
			vector<int> a;
			res->push_back(a);
			return;
		}

		int cur = nums[i];
		subsets1Helper(i+1, nums, res);
		unsigned length = res->size();
		for (unsigned j=0; j<length;j++){
			vector<int> curSet = (*res)[j];
			curSet.push_back(cur);
			res->push_back(curSet);
		}
		return;
	}

	vector<vector<int>> subsets2(vector<int>& nums){
		// using bit operation
		int N = 1<<nums.size();// number of loops
		vector<vector<int>> res;
		for (unsigned i=0; i<N;i++){
			int x = i;
			vector<int> elem;
			while(x){
				unsigned idx = log2(x &~(x-1));
				elem.push_back(nums[idx]);
				x&= (x-1);
			}
			res.push_back(elem);
		}
		for (auto elem:res){
			cout << elem << endl;
		}
		return res;
	}

	int singleNumberII(vector<int>& nums){

		int ones=0, twos=0, xthree=0;
		for (int x:nums){
			twos = twos | (ones & x);
			ones = ones ^ x;
			xthree = ~(ones & twos);
			ones &= xthree;
			twos &= xthree;
		}
		return ones;
	}

	int majorityElement(vector<int>& nums){

		int x;// current candidate
		unsigned cnt=0;
		for (int cur:nums){
			if (cnt == 0){
				x = cur;
				cnt++;
			} else{
			if (cur == x)
				cnt++;
			else
				cnt--;
			}
		}
		return x;
	}

	int rangeBitwiseAnd(int m, int n){

		int res=0;
		for (int i=0; i<31; i++){
			if ((m&1) ^ (n&1)){
				res &= 0;
			} else {
				if (m&1)
					res |= (1<<i);
			}
			m >>= 1;
			n >>= 1;
		}
		return res;
	}

	int rangeBitwiseAnd1(int m, int n){
		int i=0;
		while(!(m==n)){
			m>>=1;
			n>>=1;
			i++;
		}
		return (m<<i);
	}

	bool isPowerOfFour(int num){
		if (num <=0) return false;

		if (!(num & (num-1))){
			for (int i=0; i<16;i++){
				if (num &1)
					return true;
				num >>= 2;
			}
			return false;
		} else {
			return false;

		}
	}

	bool isPowerOfFour1(int num){
		return (num>0) && (!(num & (num-1))) && (num & 0x55555555);
	}

	int getSum(int a, int b){
		if ( !(a&b)) return a|b;
		return getSum(a^b, (a&b)<<1);
	}

	vector<int> singleNumberIII(vector<int>& nums){
		// first compute a^b
		vector<int> res;
		int x = 0;
		for (int elem:nums)
			x^=elem; // This a^b
		int i=x&~(x-1); // get the least signicant bit, use it to distinguish a and b
		vector<int> p, q;
		for (int elem: nums){
			if(i&elem) p.push_back(elem);
			else q.push_back(elem);
		}

		int a=0, b=0;
		for (int elem:p) a^=elem;
		for (int elem:q) b^=elem;

		res.push_back(a);
		res.push_back(b);

		return res;
	}

	int findMaximumXOR(vector<int>& nums){

		if (nums.size() == 0) return 0;
		int max = 0;
		int mask = 0;
		unordered_set<int> prefix;

		
		for (int i=31; i>=0; i--){
			// create mask
			mask |= 1<<i;
			prefix.clear();

			for (int x:nums)
				prefix.insert(x&mask);

			int candidate = max | 1<<i;
			
			for (int x:prefix){
				unordered_set<int>::const_iterator got = prefix.find(candidate^x);
				if (got != prefix.end()){
					max = candidate;
					break;
				}
			}
		}

		return max;
	}
	// this one returns the a_i and a_j as well
	vector<int> findMaximumXOR_test(vector<int>& nums){

		int max = 0;int mask = 0;int a = 0;
		vector<int> res;
		unordered_set<int> prefix;

		for (int i=31; i>=0; i--){
			// create mask
			mask |= 1<<i;
			prefix.clear();

			for (int x:nums)
				prefix.insert(x&mask);

			int candidate = max | 1<<i;
			
			for (int x:prefix){
				unordered_set<int>::const_iterator got = prefix.find(candidate^x);
				if (got != prefix.end()){
					max = candidate;
					a = x;
					break;
				} else {
					unordered_set<int>::const_iterator got_1 = prefix.find(max^x);
					if (got_1 != prefix.end())
						a |= x & 1<<i;
				}
			}
		}
		res.push_back(max); res.push_back(a); res.push_back(a^max);
		return res;
	}

	// 405 toHex
	string toHex(int num){

		if (num == 0) {
			string value("0");
			return value;
		}
		
		int mask = 15;
		unordered_map<int, string> dict;
		dict[0] = string("0");
		dict[1] = string("1");
		dict[2] = string("2");
		dict[3] = string("3");
		dict[4] = string("4");
		dict[5] = string("5");
		dict[6] = string("6");
		dict[7] = string("7");
		dict[8] = string("8");
		dict[9] = string("9");
		dict[10] = string("a");
		dict[11] = string("b");
		dict[12] = string("c");
		dict[13] = string("d");
		dict[14] = string("e");
		dict[15] = string("f");

		vector<string> res;

		for (int i=0; i<8; i++){
			if (num == 0) break;
			string v = dict[num&mask];
			res.push_back(v);
			num >>= 4;
		}

		string ret;
		for (string& x:res)
			ret = x + ret;
		return ret;
	}

	string toHex_1(int num){
		if (num == 0) {
			string v("0");
			return v;
		}

		char * label = "0123456789abcdef";
		string res;
		for (int i=0; i<8; i++){
			if (num == 0) break;
			res = string(1, label[num&15]) + res;
			num >>= 4;
		}
		return res;
	}


};

int main(){

	Solution s;

	//// for toHex
	//cout << s.toHex(10) << endl;
	//cout << s.toHex(0) << endl;
	//cout << s.toHex(-1) << endl;
	//cout << s.toHex(26) << endl;
	//cout << s.toHex(1000) << endl << endl;

	//cout << s.toHex_1(10) << endl;
	//cout << s.toHex_1(0) << endl;
	//cout << s.toHex_1(-1) << endl;
	//cout << s.toHex_1(26) << endl;
	//cout << s.toHex(1000) << endl;
	
	//// for singleNumberIII
	//vector<int> nums = {1, 2, 1, 3, 2, 5};
	//cout << s.singleNumberIII(nums) << endl;
	
	//// for findMaximumXOR
	//vector<int> temp = {10, 32, 2234, 18, 28};
	//cout << s.findMaximumXOR(temp) << endl;	
	//cout <<  s.findMaximumXOR_test(temp) << endl;

	//// for getSum
	//cout << s.getSum(5,6) << 5+6 << endl;
	//cout << s.getSum(-5,6) << -5+6 << endl;
	//cout << s.getSum(-5,-6) << -5-6 << endl;
	//cout << s.getSum(0,-6) << -6 << endl;

	//// for isPowerOfFour
	//cout << s.isPowerOfFour1(16) << s.isPowerOfFour(16) << endl;
	//cout << s.isPowerOfFour1(1<<30) << s.isPowerOfFour(1<<30) << endl;
	//cout << s.isPowerOfFour1(1<<31) << s.isPowerOfFour(1<<31) << endl;

	//// for rangeBitwiseAnd
	//cout << s.rangeBitwiseAnd1(5,7) << s.rangeBitwiseAnd(5, 7) << endl;
	//cout << s.rangeBitwiseAnd1(9, 10) << s.rangeBitwiseAnd(9, 10) << endl;
	//cout << s.rangeBitwiseAnd1(9,9) << s.rangeBitwiseAnd(9, 9) << endl;
	
	//// for majorityElement
	//vector<int> nums = {1,2,3,4,3,2,2,2,2,3,3,2,2,2,3,2,3,3};
	//cout << s.majorityElement(nums)<< endl;



	// for subsets
	vector<int> nums=range(2);
	s.subsets(nums);
	s.subsets1(nums);
	s.subsets2(nums);
	
	
	//// for singleNumberII
	//vector<int> nums = {1,1,1,3, 4,4,4,5,5,5};
	//cout << s.singleNumberII(nums) << endl;


	//// for romanToInt
	
	//cout << "VI:  ";s.romanToInt("VI");	
	//cout << "IV:  ";s.romanToInt("IV");
	//cout << "MMCC:  ";s.romanToInt("MMCC");
	//cout << "MCMLIV:  ";s.romanToInt("MCMLIV");
	//cout << "MMXIV:  ";s.romanToInt("MMXIV");
	//cout << "MCMXC:  ";s.romanToInt("MCMXC");

	//vector<int> nums;
	//for (int i=0; i<6; i++) nums.push_back(i+1);
	//s.rotate(nums, 11);
	//for (int i=0; i<6; i++)
		//cout << nums[i] << " ";


	//// singleNumber
	//// missingNumber
	//// addDigits
	//vector<int> a ={1,1,2,2,4,4,5,5,33333,33333,3};
	//vector<int> b ={0,1,2,3,5,6,7};
	
	//cout << s.singleNumber(a) << endl;
	//cout << s.missingNumber(b) << endl;
	////cout << s.addDigits(1234) << endl;
	////cout << s.addDigits(81) << endl;
	


	//// reverseBits
	//for (unsigned i=0; i<1000000; i++)
		//if (s.reverseBits1(i) != s.reverseBits(i)){
			//cout << s.reverseBits(i) << endl;
			//cout << s.reverseBits1(i) << endl;
		//}



	//// isPowerOfTwo
	//cout << s.isPowerOfTwo(343232435) << endl;
	//cout << s.isPowerOfTwo1(343232435) << endl;
	//cout << s.isPowerOfTwo(-16) << endl;
	//cout << s.isPowerOfTwo1(-16) << endl;
	//cout << s.isPowerOfTwo(1024) << endl;
	//cout << s.isPowerOfTwo1(1024) << endl;
	//cout << s.isPowerOfTwo(23) << endl;
	//cout << s.isPowerOfTwo1(23) << endl;
	//cout << s.isPowerOfTwo(8) << endl;
	//cout << s.isPowerOfTwo1(8) << endl;
	
	//// hammingWeight
	//cout << s.hammingWeight(343232435) << endl;
	//cout << s.hammingWeight(5) << endl;
	//cout << s.hammingWeight2(5) << endl;
	//cout << s.hammingWeight(23) << endl;
	//cout << s.hammingWeight2(23) << endl;

	//// countBits
	//cout << s.countBits(10) << endl;

	//// canWinNim
	//cout << s.canWinNim(4) << endl;
	//cout << s.canWinNim(10) << endl;
	return 0;

}



