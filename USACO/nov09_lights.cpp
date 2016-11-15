#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;

vector<pi> v1, v2;
int n, m;
lint msk[36];

void bktk(int cnt, lint x, int s, int e, vector<pi> &v){
	if(s == e){
		v.push_back(pi(x, cnt));
		return;
	}
	bktk(cnt + 1, x ^ msk[s], s+1, e, v);
	bktk(cnt, x, s+1, e, v);
}

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		msk[i] = (1ll << i);
	}
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		s--, e--;
		msk[s] ^= (1ll << e);
		msk[e] ^= (1ll << s);
	}
	bktk(0, 0, 0, n/2, v1);
	bktk(0, 0, n/2, n, v2);
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	int ret = 1e9;
	for(auto &i : v1){
		auto l = lower_bound(v2.begin(), v2.end(), pi(((1ll << n) - 1) ^ i.first, -1));
		if(l != v2.end() && (l->first ^ i.first) == (1ll << n) - 1){
			ret = min(ret, i.second + l->second);
		}
	}
	cout << ret;
}
