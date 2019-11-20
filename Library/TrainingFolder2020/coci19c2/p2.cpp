#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 800005;

vector<int> v[2][2];
int src, snk, ans[MAXN];

bool doable(int src, int snk){
	if(src != snk && sz(v[src][snk]) != sz(v[snk][src]) + 1){
		return 0;
	}
	if(src == snk && sz(v[0][1]) != sz(v[1][0])){
		return 0;
	}
	if(src == snk && sz(v[0][1]) == 0 && sz(v[src^1][snk^1])){
		return 0;
	}
	return 1;
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x, y; scanf("%d %d",&x,&y);
		if(x == 1) v[0][1].push_back(y);
		if(x == 2) v[0][0].push_back(y);
		if(x == 3) v[1][1].push_back(y);
		if(x == 4) v[1][0].push_back(y);
		if(x == 5){
			src = 1;
			ans[0] = y;
		}
		if(x == 6){
			src = 0;
			ans[0] = y;
		}
		if(x == 7){
			snk = 0;
			ans[n-1] = y;
		}
		if(x == 8){
			snk = 1;
			ans[n-1] = y;
		}
	}
	for(int i=0; i<2; i++) for(int j=0; j<2; j++){
		sort(all(v[i][j]));
		reverse(all(v[i][j]));
	}
	if(!doable(src, snk)){
		puts("-1");
		return 0;
	}
	for(int i=1; i<n-1; i++){
		bool option[2] = {1, 1};
		for(int j=0; j<2; j++){
			if(sz(v[src][j]) == 0){
				option[j] = 0;
				continue;
			}
			int bk = v[src][j].back();
			v[src][j].pop_back();
			if(!doable(j, snk)) option[j] = 0;
			v[src][j].push_back(bk);
		}
		auto go = [&](int x){
			ans[i] = v[src][x].back();
			v[src][x].pop_back();
			src = x;
		};
		if(option[0] && option[1]){
			if(v[src][0].back() < v[src][1].back()) go(0);
			else go(1);
		}
		else if(option[0]) go(0);
		else if(option[1]) go(1);
		else assert(0);
	}
	for(int i=0; i<n; i++) printf("%d ", ans[i]);
}
