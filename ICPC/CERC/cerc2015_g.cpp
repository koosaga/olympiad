#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;
const int mod = 1e9 + 7;

int n, q, a[MAXN];
int acnt[MAXN], bcnt[MAXN];
char buf[MAXN];
vector<pi> v;

map<int, int> V;

struct node{
	int l, r, mode; // 0 or +1
	int st, ed;
	int sum;
	int upd;
	void move_upd_to(int x){
		int da = acnt[x] - acnt[upd];
		int db = bcnt[x] - bcnt[upd];
		sum -= da + db;
		upd = x;
		while(da > 0){
			int pos = V.lower_bound(st)->first;
			int dx = min(da, V[pos]);
			da -= dx;
			V[pos] -= dx;
			if(!V[pos]) V.erase(pos);
		}
		while(db > 0){
			int pos = (--V.upper_bound(ed))->first;
			int dx = min(db, V[pos]);
			db -= dx;
			V[pos] -= dx;
			if(!V[pos]) V.erase(pos);
		}
	}
}nd[454545];

int piv;
int newnode(){ return ++piv; }
bool removed[454545];
int fr, ed;

queue<int> evt[MAXN];

void insert_event(int x){
	lint new_time = nd[x].upd + nd[x].sum;
	if(new_time <= q){
		evt[new_time].push(x);
	}
}

vector<pi> solve(){
	for(int i=1; i<=q; i++){
		nd[fr].upd = nd[ed].upd = i;
		if(buf[i] == 'B'){
			nd[fr].sum--;
			auto pos = (--V.upper_bound(nd[fr].ed))->first;
			V[pos]--;
			if(!V[pos]) V.erase(pos);
		}
		else{
			nd[ed].sum--;
			auto pos = V.lower_bound(nd[ed].st)->first;
			V[pos]--;
			if(!V[pos]) V.erase(pos);
		}
		while(sz(evt[i])){
			int j = evt[i].front();
			evt[i].pop();
			if(removed[j]) continue;
			nd[j].move_upd_to(i);
			nd[nd[j].l].move_upd_to(i);
			nd[nd[j].r].move_upd_to(i);
			removed[nd[j].l] = removed[nd[j].r] = 1;
			removed[j] = 1;
			node new_node = (node){nd[nd[j].l].l, nd[nd[j].r].r, nd[nd[j].l].mode, nd[nd[j].l].st, nd[nd[j].r].ed, nd[nd[j].l].sum + nd[nd[j].r].sum, i};
			int p = newnode();
			nd[p] = new_node;
			if(nd[p].l) nd[nd[p].l].r = p;
			else fr = p;
			if(nd[p].r) nd[nd[p].r].l = p;
			else ed = p;
			insert_event(p);
		}
	}
	vector<pi> v;
	int cntB = count(buf + 1, buf + q + 1, 'B');
	a[0] = cntB;
	for(int i=fr; i; i=nd[i].r){
		nd[i].move_upd_to(q);
		auto it = V.lower_bound(nd[i].st);
		while(it != V.end() && it->first <= nd[i].ed){
			v.push_back(*it);
			if(nd[i].mode == 0) v.back().second *= -1;
			it++;
		}
	}
	return v;
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]), a[i] += 1000000;
	scanf("%s", buf + 1);
	for(int i=1; i<=q; i++){
		acnt[i] = acnt[i - 1] + (buf[i] == 'A');
		bcnt[i] = bcnt[i - 1] + (buf[i] == 'B');
	}
	for(int i=0; i<=n; i++){
		if(a[i] < a[i+1]) v.emplace_back(a[i+1]-a[i],i);
		if(a[i] > a[i+1]) v.emplace_back(a[i+1]-a[i],i);
	}
	auto mode = [&](pi x){ return x.first > 0; };
	for(int i=0; i<sz(v); ){
		int e = i;
		int sum = 0;
		while(e < sz(v) && mode(v[i]) == mode(v[e])){
			V[v[e].second] = abs(v[e].first);
			sum += abs(v[e].first);
			e++;
		}
		int x = newnode();
		nd[x] = (node){0, 0, v[i].first > 0, v[i].second, v[e-1].second, sum, 0};
		i = e;
	}
	fr = 1;
	ed = piv;
	for(int i=1; i<=piv; i++){
		if(i > 1) nd[i].l = i - 1;
		if(i < piv) nd[i].r = i + 1;
		insert_event(i);
	}
	auto v = solve();
	fill(a + 1, a + n + 2, 0);
	for(auto &i : v){
		a[i.first+1] += i.second;
	}
	for(int i=1; i<=n; i++){
		a[i] += a[i-1];
		printf("%d ", a[i] - 1000000);
	}
}

