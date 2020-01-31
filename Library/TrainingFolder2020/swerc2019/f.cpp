#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;

lint ccw(pi a, pi b){
	return 1ll * a.first * b.second - 1ll * b.first * a.second;
}

int main(){
	int n;
	scanf("%d",&n);
	lint ans = 0;
	while(n--){
		int m; scanf("%d",&m);
		vector<pi> v(m);
		for(auto &j : v){
			scanf("%d %d",&j.first,&j.second);
		}
		lint ret = 0;
		for(int j=0; j<sz(v); j++) ret += ccw(v[j], v[(j + 1)%m]);
		ans += abs(ret);
	}
	cout << ans  / 2 << endl;
}
