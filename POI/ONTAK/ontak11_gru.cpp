#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define sz(v) ((int)(v).size())

int n, m, h[2005], ans[4005];
char str[2005];

int solve(){
	int ret = 0;
	vector<pi> stk;
	vector<int> opt;
	vector<int> omin;
	stk.push_back(pi(-1, 0));
	for(int i=0; i<m; i++){
		while(!stk.empty() && stk.back().second >= h[i]){
			stk.pop_back();
			if(!opt.empty()){
				omin.pop_back();
				opt.pop_back();
			}
		}
		if(stk.size() > 0){
			opt.push_back(h[i] - stk.back().first);
			int val = sz(omin) ? max(omin.back(), opt.back()) : opt.back();
			omin.push_back(val);
		}
		stk.push_back(pi(i, h[i]));
		if(sz(omin)) ret += 2 * (omin.back() + i);
	}
	return ret;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %d",&n,&m);
		memset(h, 0, sizeof(h));
		memset(ans, 0, sizeof(ans));
		lint ret = 0;
		for(int i=0; i<n; i++){
			scanf("%s", str);
			for(int j=0; j<m; j++){
				if(str[j] == '.') h[j]++;
				else h[j] = 0;
			}
			ret += solve();
		}
		cout << ret << endl;
	}
}

