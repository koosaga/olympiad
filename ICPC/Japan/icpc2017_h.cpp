#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

int n, a, b, q;
int y[MAXN], h[MAXN];

int find(int x){
	for(int i=b-1; i>=0; i--){
		if(!h[i] || !(y[i] <= x && x < y[i+1])) continue;
		int delta = (x - y[i]) / (y[i] - h[i]);
		x -= delta * (y[i] - h[i]);
		while(y[i] <= x && x < y[i + 1]){
			x -= (y[i] - h[i]);
		}
	}
	return x;
}

map<int, char> mp;

int main(){
	cin >> n >> a >> b >> q;
	vector<pair<int, string>> v(a);
	for(auto &i : v) cin >> i.first >> i.second;
	for(int i=0; i<b; i++) cin >> y[i] >> h[i];
	y[b] = n + 1;
	for(auto &i : v){
		i.first = find(i.first);
		mp[i.first] = i.second[0];
	}
	while(q--){
		int x; cin >> x;
		x = find(x);
		if(mp.count(x)) printf("%c", mp[x]);
		else printf("?");
	}
}
