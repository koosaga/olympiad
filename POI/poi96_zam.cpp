#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 5005;

struct rect{
	int sx, ex, sy, ey;
};

struct block{
	int pos, s, e;
	bool operator<(const block &b)const{
		return pi(s, e) < pi(b.s, b.e);
	}
};

struct swp{
	int yc, xs, xe, act;
	bool operator<(const swp &b)const{
		return pi(yc, -act) < pi(b.yc, -b.act);
	}
};

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int n;
pi a[MAXN];
vector<rect> ans;

void make_rect(){
	vector<swp> event;
	set<block> s;
	for(int i=0; i<n; i++){
		pi p1 = a[i];
		pi p2 = a[(i+1)%n];
		if(p1.second == p2.second) continue;
		if(p1.second < p2.second){
			event.push_back({p1.first, p1.second, p2.second, -1});
		}
		else{
			event.push_back({p1.first, p2.second, p1.second, +1});
		}
	}
	sort(event.begin(), event.end());
	auto rect_close = [&](block b, int pos){
		if(b.pos < pos){
			ans.push_back({b.pos, pos, b.s, b.e});
		}
	};
	for(int i=0; i<event.size(); ){
		int e = i;
		while(e < event.size() && event[e].yc == event[i].yc){
			if(event[e].act == 1){
				auto lbnd = s.lower_bound({-1, event[e].xs, event[e].xe});
				int curs = event[e].xs;
				int cure = event[e].xe;
				if(lbnd != s.begin() && prev(lbnd)->e == event[e].xs){
					curs = prev(lbnd)->s;
					rect_close(*prev(lbnd), event[e].yc);
					s.erase(prev(lbnd));
				}
				if(lbnd != s.end() && lbnd->s == event[e].xe){
					cure = lbnd->e;
					rect_close(*lbnd, event[e].yc);
					s.erase(lbnd);
				}
				s.insert({event[e].yc, curs, cure});
			}
			else{
				auto lbnd = --s.lower_bound({-1, event[e].xe + 1, -1});
				if(pi(lbnd->s, lbnd->e) == pi(event[e].xs, event[e].xe)){
					rect_close(*lbnd, event[e].yc);
					s.erase(lbnd);
				}
				else if(lbnd->s == event[e].xs){
					rect_close(*lbnd, event[e].yc);
					s.erase(lbnd);
					s.insert({event[e].yc, event[e].xe, lbnd->e});
				}
				else if(lbnd->e == event[e].xe){
					rect_close(*lbnd, event[e].yc);
					s.erase(lbnd);
					s.insert({event[e].yc, lbnd->s, event[e].xs});
				}
				else{
					rect_close(*lbnd, event[e].yc);
					block nxt1 = {event[e].yc, lbnd->s, event[e].xs};
					block nxt2 = {event[e].yc, event[e].xe, lbnd->e};
					s.erase(lbnd);
					s.insert(nxt1);
					s.insert(nxt2);
				}
			}
			e++;
		}
		i = e;
	}
	for(auto &i : ans){
	//	printf("%d %d %d %d\n", i.sx, i.ex, i.sy, i.ey);
	}
}

bool insec_by_edge(rect x, rect y){
	x.sx = max(x.sx, y.sx);
	x.ex = min(x.ex, y.ex);
	x.sy = max(x.sy, y.sy);
	x.ey = min(x.ey, y.ey);
	if(x.sx > x.ex || x.sy > x.ey) return 0;
	if(x.sx < x.ex && x.sy < x.ey) assert(0);
	if(pi(x.sx, x.sy) == pi(x.ex, x.ey)) return 0;
	return 1;
}

vector<int> gph[MAXN];
int par[MAXN];

void dfs(int x, int p){
	par[x] = p;
	for(auto &i : gph[x]){
		if(i != p){
			dfs(i, x);
		}
	}
}

int Do(vector<rect> seq, int s, int e){
	int ret = 0;
	for(auto &i : seq){
		if(s < i.sx) ret += i.sx - s, s = i.sx;
		if(i.ex < s) ret += s - i.ex, s = i.ex;
	}
	ret += abs(e - s);
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	{
		lint totArr = 0;
		for(int i=1; i<n; i++){
			totArr += ccw(a[0], a[i-1], a[i]);
		}
		if(totArr < 0) reverse(a, a + n);
	}
	a[n] = a[0];
	pi x, y;
	scanf("%d %d %d %d",&x.first,&x.second,&y.first,&y.second);
	make_rect();
	vector<rect> seq;
	auto rect = ans;
	int sx = -1, ex = -1, cnt = 0;
	int ret = 0;
	for(int i=0; i<rect.size(); i++){
		if(rect[i].sx <= x.first && x.first <= rect[i].ex && rect[i].sy <= x.second && x.second <= rect[i].ey){
			sx = i;
		}
		if(rect[i].sx <= y.first && y.first <= rect[i].ex && rect[i].sy <= y.second && y.second <= rect[i].ey){
			ex = i;
		}
	}
	for(int i=0; i<rect.size(); i++){
		for(int j=0; j<i; j++){
			if(insec_by_edge(rect[i], rect[j])){
				gph[i].push_back(j);
				gph[j].push_back(i);
				cnt++;
			}
		}
	}
	assert(cnt + 1 == rect.size());
	dfs(ex, -1);
	while(sx != -1){
		seq.push_back(rect[sx]);
		sx = par[sx];
	}
	int ret1 = Do(seq, x.first, y.first);
	for(auto &i : seq){
	//	printf("%d %d %d %d\n", i.sx, i.ex, i.sy, i.ey);
		swap(i.sx, i.sy);
		swap(i.ex, i.ey);
	}
	int ret2 = Do(seq, x.second, y.second);
	cout << ret1 + ret2 << endl;
}
