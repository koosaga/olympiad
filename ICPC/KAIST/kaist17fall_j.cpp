#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 +7;

int n;
map<int, int> mp;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

bool query(int x, int y){
	auto l = mp.lower_bound(x);
	if(l == mp.end()) return false;
	if(l == mp.begin()){
		if(y <= l->second) return true;
		return false;
	}
	pi cur = *l;
	pi prv = *--l;
	return ccw(prv, pi(x, y), cur) >= 0;
}

void add(int x, int y){
	if(query(x, y)) return;
	if(mp.find(x) != mp.end()){
		mp.erase(x);
	}
	if(mp.empty()){
		mp.insert(pi(x, y));
		return;
	}
	auto l = mp.lower_bound(x);
	while(l != mp.end()){
		if(l->second >= y) l = mp.erase(l);
		else break;
	}
	while(l != mp.begin()){
		l--;
		if(l->second <= y) l = mp.erase(l);
		else break;
	}
	l = mp.lower_bound(x);
	while(l != mp.end()){
		l = mp.lower_bound(x);
		auto nxt = l;
		nxt++;
		if(nxt != mp.end() && ccw(pi(x, y), *l, *nxt) >= 0) l = mp.erase(l);
		else break;
	}
	l = mp.lower_bound(x);
	while(l != mp.begin()){
		l--;
		auto nxt = l;
		if(nxt != mp.begin()){
			nxt--;
			if(ccw(*nxt, *l, pi(x, y)) >= 0){
				l = mp.erase(l);
			}
			else break;
		}
		else break;
	}
	mp[x] = y;
}

int main(){
	cin >> n;
	add(0, 0);
	while(n--){
		int x, y;
		scanf("%d %d",&x,&y);
		add(x, y);
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int x, y;
		scanf("%d %d",&x,&y);
		if(query(x, y)) puts("No");
		else{
			puts("Yes");
			add(x, y);
		}
	}
}
