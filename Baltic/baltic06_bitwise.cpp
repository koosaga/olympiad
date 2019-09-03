#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 305;
 
int n, m;
int l[MAXN], r[MAXN];
vector<int> pos[MAXN];
 
bool good(vector<int> &pos, int msk){
	vector<int> choice[32];
	for(auto &i : pos){
		if(l[i] == r[i]){
			msk &= ~l[i];
			continue;
		}
		int j = 30;
		while((l[i] >> j) == (r[i] >> j)) j--;
		int val = (l[i] >> (j + 1)) << (j + 1);
		msk &= ~val;
		choice[j].push_back(r[i] - val);
	}
	priority_queue<pi> pq;
	for(int i = 30; i >= 0; i--){
		for(auto &j : choice[i]) pq.emplace(i, j);
		if((msk >> i) & 1){
			if(pq.empty()) return 0;
			auto x = pq.top(); pq.pop();
			if(x.first > i){
				return 1;
			}
			msk ^= (1 << i);
			x.second ^= (1 << i);
			int pos = i;
			if(x.second > 0){
				while((x.second >> pos) == 0) pos--;
				choice[pos].push_back(x.second);
			}
		}
	}
	return 1;
}
 
bool good(int msk){
	for(int i=0; i<m; i++){
		if(!good(pos[i], msk)) return 0;
	}
	return 1;
}
 
int main(){
	scanf("%d %d",&n,&m);
	int cur = 0;
	for(int i=0; i<m; i++){
		int x; cin >> x;
		pos[i].resize(x);
		iota(pos[i].begin(), pos[i].end(), cur);
		cur += x;
	}
	for(int i=0; i<n; i++) cin >> l[i] >> r[i];
	int ans = 0;
	for(int i=30; i>=0; i--){
		if(good(ans | (1 << i))) ans |= (1 << i);
	}
	cout << ans << endl;
}
