#include<bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 3005;

struct point{
	int x, y; char dir;
}a[MAXN];
int n;

auto cmpx = [](const point &a, const point &b){
	return pi(a.x, a.y) < pi(b.x, b.y);
};

auto cmpy = [](const point &a, const point &b){
	return pi(a.y, a.x) < pi(b.y, b.x);
};

int f(int x){
	set<point, decltype(cmpx)> sx(cmpx);
	set<point, decltype(cmpy)> sy(cmpy);
	for(int i=0; i<n; i++){
		sx.insert(a[i]);
		sy.insert(a[i]);
	}
	point cur = a[x];
	int ret = 0;
	while(true){
		sx.erase(cur);
		sy.erase(cur);
		ret++;
		if(cur.dir == '>'){
			auto l = sx.lower_bound((point){cur.x, cur.y, -1});
			if(l != sx.end() && l->x == cur.x){
				cur = *l;
			}
			else break;
		}
		if(cur.dir == '<'){
			auto l = sx.upper_bound((point){cur.x, cur.y, -1});
			if(l != sx.begin() && prev(l)->x == cur.x){
				cur = *prev(l);
			}
			else break;
		}
		if(cur.dir == 'v'){
			auto l = sy.lower_bound((point){cur.x, cur.y, -1});
			if(l != sy.end() && l->y == cur.y){
				cur = *l;
			}
			else break;
		}
		if(cur.dir == '^'){
			auto l = sy.upper_bound((point){cur.x, cur.y, -1});
			if(l != sy.begin() && prev(l)->y == cur.y){
				cur = *prev(l);
			}
			else break;

		}
	}
	return ret;
}

int main(){	
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].x >> a[i].y >> a[i].dir;
		swap(a[i].x, a[i].y);
	}
	int ret = 0;
	for(int i=0; i<n; i++) ret = max(ret, f(i));
	cout << ret << endl;
}
