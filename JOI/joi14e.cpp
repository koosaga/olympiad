#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct seg{
	int s, e, x;
	bool operator<(const seg &s)const{
		return x < s.x;
	}
};

struct sweep{
	int idx, pos, val;
	bool operator<(const sweep &s)const{
		return pi(idx, val) < pi(s.idx, s.val);
	}
};

struct disj{
	int pa[100050];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int xsz, ysz;
vector<seg> xs, ys; 

int ds[200050];

const int B = 400;
int bkt[505][405];
int rep[505];

void bkt_push(int x){
	if(rep[x] == 0) return;
	for(int i=0; i<B; i++){
		if(bkt[x][i]){
			bkt[x][i] = rep[x];
		}
	}
	rep[x] = 0;
}

void bkt_insert(int p, int v){
	bkt_push(p / B);
	bkt[p / B][p % B] = v;
}

void bkt_merge(int s, int e, int x){
	if(s/B == e/B){
		bkt_push(s/B);
		for(int i=s%B; i<=e%B; i++){
			if(bkt[s/B][i]){
				disj.uni(bkt[s/B][i], x);
			}
		}
		return;
	}
	if(s%B) bkt_push(s/B);
	while(s % B){
		if(bkt[s/B][s%B]){
			disj.uni(bkt[s/B][s%B], x);
		}
		s++;
	}
	if(e%B != B-1) bkt_push(e/B);   
	while(e%B != B-1){
		if(bkt[e/B][e%B]){
			disj.uni(bkt[e/B][e%B], x);
		}
		e--;
	}
	for(int i=s/B; i<=e/B; i++){
		if(rep[i]){
			disj.uni(rep[i], x);
		}
		else{
			int chk = 0;
			for(int j=0; j<B; j++){
				if(bkt[i][j]){
					disj.uni(bkt[i][j], x);
					chk++;
				}
			}
			if(chk) rep[i] = x;
		}
	}
}

int get_component(){
	disj.init(xs.size());
	vector<sweep> swp;
	set<int> s;
	for(auto &i : xs){
		swp.push_back({i.s, i.x, 1});
		swp.push_back({i.e+1, i.x, -1});
	}
	sort(swp.begin(), swp.end());
	int p = 0, q = 0, r = 0;
	int cnt = 1;
	for(int i=1; i<=ysz+1; i++){
		while(p < swp.size() && swp[p].idx == i){
			if(swp[p].val == 1){
				ds[swp[p].pos] = ++r;
				bkt_insert(swp[p].pos, r);
				s.insert(swp[p].pos);
			}
			else{
				bkt_insert(swp[p].pos, 0);
				s.erase(swp[p].pos);
			}
			p++;
		}
		while(q < ys.size() && ys[q].x == i){
			auto t = s.lower_bound(ys[q].s);
			if(t == s.end() || *t > ys[q].e){
				cnt++;
				q++;
				continue;
			}
			bkt_merge(ys[q].s, ys[q].e, ds[*t]);
			q++;
		}
	}
	for(int i=2; i<=xs.size(); i++){
		if(disj.uni(1, i)) cnt++;
	}
	return cnt;
}

struct bit{
	int tree[200050];
	void add(int x, int v){
		while(x <= xsz){
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

lint get_intersection(){
	vector<sweep> swp;
	for(auto &i : xs){
		swp.push_back({i.s, i.x, 1});
		swp.push_back({i.e+1, i.x, -1});
	}
	sort(swp.begin(), swp.end());
	lint ret = 0;
	int p = 0;
	for(auto &j : ys){
		while(p < swp.size() && swp[p].idx <= j.x){
			bit.add(swp[p].pos, swp[p].val);
			p++;
		}
		ret += bit.query(j.e) - bit.query(j.s-1);
	}
	return ret;
}

int main(){
	vector<int> vx, vy;
	int w, h, n;
	scanf("%d %d %d",&w,&h,&n);
	vx.push_back(0);
	vx.push_back(w);
	vy.push_back(0);
	vy.push_back(h);
	for(int i=0; i<n; i++){
		int x1, y1, x2, y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		vx.push_back(x1);
		vx.push_back(x2);
		vy.push_back(y1);
		vy.push_back(y2);
		if(x1 < x2){
			ys.push_back({x1, x2, y1});
		}
		if(y1 < y2){
			xs.push_back({y1, y2, x1});
		}
	}
	xs.push_back({0, h, 0});
	xs.push_back({0, h, w});
	ys.push_back({0, w, 0});
	ys.push_back({0, w, h});
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for(auto &i : xs){
		int l = lower_bound(vy.begin(), vy.end(), i.s) - vy.begin();
		int r = upper_bound(vy.begin(), vy.end(), i.e) - vy.begin() - 1;
		int x = lower_bound(vx.begin(), vx.end(), i.x) - vx.begin();
		i = {l+1, r+1, x+1};
	}
	for(auto &i : ys){
		int l = lower_bound(vx.begin(), vx.end(), i.s) - vx.begin();
		int r = upper_bound(vx.begin(), vx.end(), i.e) - vx.begin() - 1;
		int x = lower_bound(vy.begin(), vy.end(), i.x) - vy.begin();
		i = {l+1, r+1, x+1};
	}
	xsz = vx.size();
	ysz = vy.size();
	cout << get_intersection() + get_component() - (n+4) << endl;
}
