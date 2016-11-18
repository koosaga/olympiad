#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct pnt{
	int x, y, idx;
	bool operator<(const pnt &a)const{
		return pi(x, y) < pi(a.x, a.y);
	}
};

vector<int> gph[100005];

int n;
pi s, e, a[25005];
vector<pi> v1;
vector<pnt> v2;

void make_edge(){
	sort(a, a+n);
	sort(v2.begin(), v2.end());
	for(auto &i : v2){
		auto l = lower_bound(a, a+n, pi(i.x, i.y)) - a;
		if(l < n && a[l].first == i.x){
			auto w = lower_bound(v2.begin(), v2.end(), (pnt){a[l].first, a[l].second - 1, -1});
			if(w != v2.end() && pi(w->x, w->y) == pi(a[l].first, a[l].second - 1) && pi(w->x, w->y) != pi(i.x, i.y)){
				gph[i.idx].push_back(w->idx);
			}
		}
	}
}

int dist[100005];

int main(){
	cin >> n >> s.first >> s.second >> e.first >> e.second;
	v1.push_back(s);
	v1.push_back(e);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		v1.push_back(pi(a[i].first-1, a[i].second));
		v1.push_back(pi(a[i].first+1, a[i].second));
		v1.push_back(pi(a[i].first, a[i].second-1));
		v1.push_back(pi(a[i].first, a[i].second+1));
	}
	sort(a, a+n);
	sort(v1.begin(), v1.end());
	v1.resize(unique(v1.begin(), v1.end()) - v1.begin());
	for(int i=0; i<v1.size(); i++){
		auto l = lower_bound(a, a+n, v1[i]);
		if(l < a+n && *l == v1[i]) continue;
		v2.push_back({v1[i].first, v1[i].second, (int)v2.size()});
	}
	make_edge();
	for(auto &i : v2) i.y *= -1;
	for(int i=0; i<n; i++) a[i].second *= -1;
	make_edge();
	for(auto &i : v2) i.y *= -1, swap(i.x, i.y);
	for(int i=0; i<n; i++) a[i].second *= -1, swap(a[i].first, a[i].second);
	make_edge();
	for(auto &i : v2) i.y *= -1;
	for(int i=0; i<n; i++) a[i].second *= -1;
	make_edge();
	for(auto &i : v2) i.y *= -1, swap(i.x, i.y);
	sort(v2.begin(), v2.end(), [&](const pnt &a, const pnt &b){
		return a.idx < b.idx;
	});
	queue<int> que;
	memset(dist, 0x3f, sizeof(dist));
	for(int i=0; i<v2.size(); i++){
		if(pi(v2[i].x, v2[i].y) == s){
			que.push(i);
			dist[i] = 0;
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		if(pi(v2[x].x, v2[x].y) == e){
			printf("%d\n", dist[x]);
			return 0;
		}
		for(auto &i : gph[x]){
			if(dist[i] > dist[x] + 1){
				dist[i] = dist[x] + 1;
				que.push(i);
			}
		}
	}
	assert(0);
}
