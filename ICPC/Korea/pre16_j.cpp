#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, s[100005], e[100005], l;
map<int, int> mp;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&s[i],&e[i]);
		if(s[i] > e[i]) swap(s[i], e[i]);
	}
	scanf("%d",&l);
	for(int i=0; i<n; i++){
		if(e[i] - s[i] > l) continue;
		tie(s[i], e[i]) = pi(e[i] - l, s[i]);
		mp[2*s[i]]++;
		mp[2*e[i]+1]--;
	}
	int dap = 0, ret = 0;
	for(auto &i : mp){
		ret += i.second;
		dap = max(dap, ret);
	}
	cout << dap;
}
