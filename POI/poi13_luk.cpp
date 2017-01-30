#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int n;
vector<int> gph[300005];

int f(int x, int p, int k){
	int ret = 0;
	for(auto &i : gph[x]){
		if(i != p) ret += f(i, x, k) + 1;
	}
	return max(ret - k, 0);
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int s = 0, e = n;
	while(s != e){
		int m = (s+e)/2;
		if(f(1, 0, m) == 0) e = m;
		else s = m+1;
	}
	cout << s;
}
