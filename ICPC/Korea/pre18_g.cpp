#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 50505;

int main(){
	int n, k, x;
	cin >> n >> k;
	vector<int> v;
	for(int i=0; i<n; i++){
		cin >> x;
		auto p = lower_bound(v.begin(), v.end(), -x) - v.begin();
		if(p == v.size()) v.push_back(-x);
		else v[p] = -x;
	}
	cout << (v.size() <= k ? "YES" : "NO") << endl;
}
