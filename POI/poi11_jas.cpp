#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
typedef vector<int> vi;

vector<int> gph[100005];
int n;

int ret;

int f(int x, int p){
	int cnt[22] = {};
	for(auto &i : gph[x]){
		if(i == p) continue;
		int v = f(i, x);
		for(int i=0; i<20; i++){
			cnt[i] += ((v >> i) & 1);
		}
	}
	int lst = -1;
	for(int i=20; i>=0; i--){
		if(cnt[i] >= 2){
			lst = i;
			break;
		}
	}
	int mask = 0;
	for(int i=lst+1; i<20; i++){
		if(cnt[i] == 0){
			ret = max(ret, i);
			for(int j=i+1; j<20; j++){
				if(cnt[j]) mask |= (1<<j);
			}
			mask |= (1<<i);
			return mask;
		}
	}
	assert(0);
}

int main(){
	cin >> n;
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	f(1, -1);
	cout << ret;
}
