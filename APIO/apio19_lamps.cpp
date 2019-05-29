#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
using lint = long long;
using pi = pair<int, int>;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

struct intv{
	int s, e, x;
	bool operator<(const intv &i)const{
		return s < i.s;
	}
};

struct event{
	int x, y, t, type;
	bool operator<(const event &e)const{
		return pi(x, y) < pi(e.x, e.y);
	}
};

int ret[MAXN];
vector<event> ev;
set<intv> s;

void add_rect(int s, int e, int x){
	ev.push_back({s, s, +x, 1});
	ev.push_back({s, e + 1, -x, 1});
	ev.push_back({e + 1, s, -x, 1});
	ev.push_back({e + 1, e + 1, +x, 1});
}

void solve(int s, int e){
	if(s == e) return;
	int m = (s+e)/2;
	solve(s, m);
	solve(m + 1, e);
	vector<event> pupd, quer;
	for(int i=s; i<=m; i++){
		if(ev[i].type == 1){
			pupd.push_back(ev[i]);
		}
	}
	for(int i=m+1; i<=e; i++){
		if(ev[i].type == 2){
			quer.push_back(ev[i]);
		}
	}
	sort(pupd.begin(), pupd.end());
	sort(quer.begin(), quer.end());
	int ptr = 0;
	for(auto &i : quer){
		while(ptr < pupd.size() && pupd[ptr].x <= i.x){
			bit.add(pupd[ptr].y, pupd[ptr].t);
			ptr++;
		}
		ret[i.t] += bit.query(i.y);
	}
	for(int i=0; i<ptr; i++){
		bit.add(pupd[i].y, -pupd[i].t);
	}
}

int n, q;
char str[MAXN];

int main(){
	scanf("%d %d",&n,&q);
	scanf("%s", str + 1);
	for(int i=1; i<=n; ){
		if(str[i] == '0'){
			i++;
			continue;
		}
		int e = i;
		while(e <= n && str[e] == '1') e++;
		s.insert({i, e - 1, 1});
		i = e;
	}
	char buf[10];
	for(int i=1; i<=q; i++){
		scanf("%s", buf);
		if(*buf == 't'){
			int t; scanf("%d",&t);
			if(str[t] == '0'){
				int st = t, ed = t;
				auto l = s.lower_bound({t + 1, -1, -1});
				if(l != s.end() && l->s == t + 1){
					add_rect(l->s, l->e, i + 1 - l->x);
					ed = l->e;
					l = s.erase(l);
				}
				if(l != s.begin() && prev(l)->e == t - 1){
					l--;
					add_rect(l->s, l->e, i + 1 - l->x);
					st = l->s;
					s.erase(l);
				}
				s.insert({st, ed, i + 1});
			}
			if(str[t] == '1'){
				auto l = --s.lower_bound({t + 1, -1, -1});
				add_rect(l->s, l->e, i + 1 - l->x);
				vector<intv> newV;
				if(l->s < t){
					newV.push_back({l->s, t - 1, i + 1});
				}
				if(t < l->e){
					newV.push_back({t + 1, l->e, i + 1});
				}
				s.erase(l);
				for(auto &i : newV) s.insert(i);
			}
			str[t] ^= 1;
			ret[i] = -1;
		}
		else{
			int a, b; scanf("%d %d",&a,&b);
			b--;
			ev.push_back({a, b, i, 2});
			auto l = s.lower_bound({a + 1, -1, -1});
			if(l != s.begin()){
				l--;
				if(l->s <= a && b <= l->e){
					ret[i] += i + 1 - l->x;
				}
			}
		}
	}
	solve(0, ev.size() - 1);
	for(int i=1; i<=q; i++){
		if(ret[i] >= 0) printf("%d\n", ret[i]);
	}
}
