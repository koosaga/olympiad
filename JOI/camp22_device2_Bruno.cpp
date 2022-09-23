#include "Bruno.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
 
namespace {
	lint dp[155];
	void init(){
		lint dap = 0;
		for(int i = 1; i < 155; i++){
			// [1] 2 3 2 3 3 .... [0+]
			dp[i] = 1 + (i >= 3 ? dp[i - 2] : 0) + (i >= 4 ? dp[i - 3] : 0);
			dap += dp[i];
		}
	}
	lint decode(vector<int> ans){
		int tot = 0;
		for(auto &x : ans) tot += abs(x);
		lint dap = 0;
		for(int i = 1; i < tot; i++){
			dap += dp[i];
		}
		int cur = 0;
		reverse(all(ans));
		for(int i = 0; i < sz(ans); i++){
			if(ans[i] <= 0){
				cur -= ans[i];
				continue;
			}
			else{
				if(ans[i] == 2){
					dap += 1;
					cur += 2;
				}
				else{
					dap += dp[cur + 1] + 1;
					cur += 3;
				}
			}
		}
		return dap;
	}
}
 
long long Bruno(std::vector<int> u) {
	init();
	bool flag = 0;
	if(u[0] == 0){
		flag = 1;
		for(auto &x : u) x ^= 1;
	}
	int ptr = 1;
	int piv = 1, sum = 1;
	int previous = 1;
	vector<int> ans = {1};
	while(ptr < sz(u)){
		int k = piv;
		int U = (k + 3 - (previous == 1));
		int D = (k - 3 + (previous == 0));
		while(ptr < sz(u)){
			sum += u[ptr++] * 2 - 1;
			if(sum >= U) break;
			if(sum <= D + 1) break;
		}
		if(sum == U){
			ans.push_back(1);
			previous = 1;
			piv = U;
		}
		else if(sum == D + 1){
			ans.push_back(0);
			previous = 0;
			piv = D;
		}
	}
	vector<int> foo;
	for(int i = 0; i < sz(ans); ){
		int j = i;
		while(j < sz(ans) && ans[i] == ans[j]) j++;
		foo.push_back(3);
		for(int x = i + 1; x < j; x++) foo.push_back(2);
		i = j;
	}
	foo.erase(foo.begin());
	int rem = sz(u) / 2 - accumulate(all(foo),0);
	if(rem > 0) foo.push_back(-rem);
	cout << flag << " ";
	for(auto &x : foo) cout << x << " ";
	cout << endl;
	return decode(foo) * 2 + flag;
}

