#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 70005;

struct seg{
	int pos, s, e;
	bool operator<(const seg &s)const{
		return pi(pos, e) < pi(s.pos, s.e);
	}
};

vector<seg> vert, hori;
vector<pi> v, w;

int n, t;
int nxt[MAXN][4];

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};

lint dist(int x, int y){
	pi a = v[x];
	pi b = v[y];
	return abs(a.first - b.first) + abs(a.second - b.second);
}

lint check_cycle(int p, int t, int d){
	lint len = 0;
	pi pos = v[p];
	do{
		while(nxt[p][d] == -1) d = (d + 1) % 4;
		len += dist(p, nxt[p][d]);
		p = nxt[p][d];
		d = (d + 1) % 4;
	}while(pos != v[p]);
	return len;
}

void simulate(int p, int t, int d){
	while(true){
		while(nxt[p][d] == -1) d = (d + 1) % 4;
		if(t <= dist(p, nxt[p][d])){
			int X = v[p].first + dx[d] * t;
			int Y = v[p].second + dy[d] * t;
			printf("%d %d\n", X, Y);
			break;
		}
		else{
			t -= dist(p, nxt[p][d]);
		}
		p = nxt[p][d];
		d = (d + 1) % 4;
	}
	// 0^ 1< 2v 3>
}

bool common_segment(vector<seg> &segs, int pos, int s, int e){
	auto l = lower_bound(all(segs), (seg){pos, -1, e});
	if(l != segs.end() && l->pos == pos && l->s <= s && s <= l->e){
		return 1;
	}
	return 0;
}

int main(){
	scanf("%d %d",&n,&t);
	pi sp;
	int sd;
	for(int i=0; i<n; i++){
		int sx, sy, ex, ey;
		scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
		if(i == 0) sp = pi(sx, sy);
		if(sx > ex) swap(sx, ex);
		if(sy > ey) swap(sy, ey);
		if(sx == ex){
			vert.push_back({sx, sy, ey});
		}
		else{
			hori.push_back({sy, sx, ex});
		}
		v.emplace_back(sx, sy);
		v.emplace_back(ex, ey);
		if(i == 0){
			if(sz(vert)){
				if(sp == pi(sx, sy)) sd = 0;
				else sd = 2;
			}
			else{
				if(sp == pi(sx, sy)) sd = 3;
				else sd = 1;
			}
		}
	}
	sort(all(vert));
	sort(all(hori));
	for(auto &i : vert){
		for(auto &j : hori){
			if(j.s <= i.pos && i.pos <= j.e && i.s <= j.pos && j.pos <= i.e){
				v.emplace_back(i.pos, j.pos);
			}
		}
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	w = v;
	for(auto &[x, y] : w) swap(x, y);
	sort(all(w));
	memset(nxt, -1, sizeof(nxt));
	for(int i=0; i+1<sz(v); i++){
		if(v[i].first == v[i+1].first){
			if(common_segment(vert, v[i].first, v[i].second, v[i+1].second)){
				nxt[i][0] = i + 1;
				nxt[i + 1][2] = i;
			}
		}
	}
	for(int i=0; i+1<sz(w); i++){
		if(w[i].first == w[i+1].first){
			if(common_segment(hori, w[i].first, w[i].second, w[i+1].second)){
				int X = lower_bound(all(v), pi(w[i].second, w[i].first)) - v.begin();
				int Y = lower_bound(all(v), pi(w[i+1].second, w[i+1].first)) - v.begin();
				nxt[X][3] = Y;
				nxt[Y][1] = X;
			}
		}
	}
	int spv = lower_bound(all(v), sp) - v.begin();
	lint w = check_cycle(spv, t, sd);
	t %= w;
	simulate(spv, t, sd);
}
