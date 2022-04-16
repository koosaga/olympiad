#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 500005;
 
struct event{
	lint pos;
	lint a, b;
	bool operator<(const event &e)const{
		return pos < e.pos;
	}
};
 
vector<event> ev;
 
void add(lint s, lint e, lint x, lint y, lint R){
	if(R <= s){
		if(x == 1) add(s - R, e - R, x, y + R, R);
		else add(s - R, e - R, x, y - R, R);
		return;
	}
	if(s < R && R <= e){
		add(s, R - 1, x, y, R);
		if(x == 1) add(0, e - R, x, y + R, R);
		else add(0, e - R, x, y - R, R);
		return;
	}
	ev.push_back({s, x, y});
	ev.push_back({e + 1, -x, -y});
}
 
long long findMinClicks(int M, int R, vector <pair<int, int> > P) {
	sort(all(P));
	int ptr = 0;
	vector<lint> v;
	for(auto &i : P) v.push_back(i.second);
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for(int i=0; i<M; i++){
		vector<lint> up;
		while(ptr < sz(P) && P[ptr].first == i) up.push_back(P[ptr++].second);
		lint kek = up[0] + R;
		up.push_back(kek);
		for(int j = 0; j < sz(up) - 1; j++){
			lint l = up[j], r = up[j + 1];
			lint m = (l + r) / 2;
			add(l, m, 1, -l, R);
			add(m + 1, r, -1, r, R);
		}
	}
	sort(all(ev));
	int j = 0;
	lint sa = 0, sb = 0, ret = 1e18;
	for(auto &i : v){
		while(j < sz(ev) && ev[j].pos <= i){
			sa += ev[j].a;
			sb += ev[j].b;
			j++;
		}
		ret = min(ret, sa * i + sb);
	}
	return ret;
}
 
