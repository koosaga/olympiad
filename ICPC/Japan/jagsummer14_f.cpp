#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
struct vect{
	int x, y, c;
	bool operator<(const vect &v)const{
		return c > v.c;
	}
};

lint ccw(vect a, vect b, vect c){
	lint dx1 = b.x - a.x;
	lint dy1 = b.y - a.y;
	lint dx2 = c.x - a.x;
	lint dy2 = c.y - a.y;
	return dx1 * dy2 - dy1 * dx2;
}


lint ccw(vect b, vect c){
	vect a = {0, 0, 0};
	lint dx1 = b.x - a.x;
	lint dy1 = b.y - a.y;
	lint dx2 = c.x - a.x;
	lint dy2 = c.y - a.y;
	return dx1 * dy2 - dy1 * dx2;
}


lint solve(vector<vect> &v, vector<vect> &w){
	int p = 0;
	lint minc = 1e11, ans = 1e11;
	priority_queue<vect> pq;
	for(auto &i : w) pq.push(i);
	for(int i=0; i<v.size(); i++){
		while(p < w.size() && ccw((vect){0, 0, 0}, v[i], w[p]) > 0) minc = min(minc, 1ll * w[p++].c);
		while(!pq.empty() && ccw((vect){0, 0, 0}, pq.top(), v[i]) <= 0) pq.pop();
		if(!pq.empty()) ans = min(ans, minc + pq.top().c + v[i].c);
	}
	return ans;
}

lint fuck(vector<vect> &v, vector<vect> &w){
	int p = 0;
	vector<lint> tmp;
	for(int i=0; i<v.size(); ){
		int e = i;
		lint ans1 = 1e11, ans2 = 1e11;
		while(e < v.size() && ccw(v[i], v[e]) == 0){
			ans1 = min(ans1, 1ll * v[e++].c);
		}
		while(p < w.size() && ccw(v[i], w[p]) > 0) p++;
		while(p < w.size() && ccw(v[i], w[p]) == 0) ans2 = min(ans2, 1ll * w[p++].c);
		tmp.push_back(ans1 + ans2);
		i = e;
	}
	while(tmp.size() < 2) tmp.push_back(1e11);
	sort(tmp.begin(), tmp.end());
	return tmp[tmp.size()-2] + tmp.back();
}

vector<vect> l, r;

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x, y, c;
		scanf("%d %d %d",&x,&y,&c);
		if(x == 0 && y == 0) continue;
		if(pi(x, y) > pi(0, 0)) l.push_back({x, y, c});
		else r.push_back({x, y, c});
	}
	sort(l.begin(), l.end(), [&](const vect &a, const vect &b){
		return ccw((vect){0, 0, 0}, a, b) > 0;
	});
	sort(r.begin(), r.end(), [&](const vect &a, const vect &b){
		return ccw((vect){0, 0, 0}, a, b) > 0;
	});
	lint x = min(solve(l, r), solve(r, l));
	x = min(x, fuck(l, r));
	if(x > 1e10) x = -1;
	cout << x;
}
