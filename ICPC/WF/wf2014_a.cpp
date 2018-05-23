#include <bits/stdc++.h>
const int MAXN = 105;
const int mod = 1e9 + 7;
using namespace std;
using lint = long long;
using pi = pair<int, int>;

vector<pi> solve(int n){
	if(n == 3){
		vector<pi> ans = {pi(2, -1), pi(5, 2), pi(3, -3)};
		return ans;
	}
	if(n == 4){
		vector<pi> ret = {pi(2*n-2, -1), pi(3, 2*n-2)};
		ret.push_back(pi(0, 2*n-5));
		ret.push_back(pi(2*n-1, 0));
		return ret;
	}
	if(n == 5){
		vector<pi> ans = {pi(8, -1), pi(3, 8), pi(6, 3), pi(0, 6), pi(9, 0)};
		return ans;
	}
	if(n == 6){
		vector<pi> ans = {pi(10, -1), pi(7, 10), pi(2, 7), pi(6, 2), pi(0, 6), pi(11, 0)};
		return ans;
	}
	if(n == 7){
		vector<pi> ans = {pi(8, -1), pi(5, 8), pi(12, 5), pi(3, 12), pi(9, 3), pi(0, 9), pi(13, 0)};
		return ans;
	}
	vector<pi> ret = {pi(2*n-2, -1), pi(3, 2*n-2)};
	vector<pi> rec = solve(n - 4);
	for(auto &i : rec) ret.push_back(pi(i.first + 4, i.second + 4));
	ret.push_back(pi(0, 2*n-5));
	ret.push_back(pi(2*n-1, 0));
	return ret;
}

int main(){
	int n;
	cin >> n;
	auto x = solve(n);
	for(auto &i : x) printf("%d to %d\n", i.first, i.second);
}
