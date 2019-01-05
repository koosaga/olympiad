#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 1005;
using pi = pair<int, int>;

int n;
vector<int> gph[MAXN];
int sz[MAXN];

struct pnt{
	int x, y, idx;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	};
}a[MAXN];

lint ccw(pnt a, pnt b, pnt c){
	int dx1 = b.x - a.x;
	int dy1 = b.y - a.y;
	int dx2 = c.x - a.x;
	int dy2 = c.y - a.y;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

void prep(int x, int p){
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i != p){
			prep(i, x);
			sz[x] += sz[i];
		}
	}
}

int dfs(int x, int p, vector<pnt> a){
	swap(a[0], *min_element(a.begin(), a.end()));
	sort(a.begin() + 1, a.end(), [&](const pnt &p, const pnt &q){
		return ccw(a[0], p, q) > 0;
	});
	int ptr = 1;
	for(auto &i : gph[x]){
		if(i != p){
			vector<pnt> b;
			for(int j=ptr; j<ptr + sz[i]; j++){
				b.push_back(a[j]);
			}
			ptr += sz[i];
			int r = dfs(i, x, b);
			printf("%d %d\n", a[0].idx, r);
		}
	}
	return a[0].idx;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	vector<pnt> a(n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i].idx = i;
	}
	prep(0, -1);
	dfs(0, -1, a);
}
