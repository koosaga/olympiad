#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

vector<pi> v, w;
double cx, cy;
int n, m;

bool vis[10005];
int a[555][555];

bool ok(pi x, pi y){
	int dx = x.first - y.first;
	int dy = x.second - y.second;
	return dx * dx + dy * dy <= 100;
}

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(int i=0; i<w.size(); i++){
		if(ok(w[i], w[x])) dfs(i);
	}
}

double solve(int p, int q){
	swap(v[0], *min_element(v.begin(), v.end(), [&](const pi &a, const pi &b){
				return a.first * p + a.second * q < b.first * p + b.second * q;
				}));
	double minv = 1e9, maxv = -1e9;
	for(int i=1; i<v.size(); i++){
		int dx = v[i].second - v[0].second;
		int dy = v[i].first - v[0].first;
		if(dx * dx + dy * dy <= 1225) continue;
		double ang = atan2(v[i].second - v[0].second, v[i].first - v[0].first);
		minv = min(minv, ang);
		maxv = max(maxv, ang);
	}
	double w = (maxv - minv) / (2 * M_PI);
	w = 0.5 - w;
	return w;
}

int go_small(){
	double p = -1e9;
	for(int i=0; i<18; i++){
		p = max(p, solve(rand() % 500 + 1, rand() % 500 + 1));
	}
	return (int)round(1/p);
}


int main(){
	scanf("%*s %d %d",&m,&n);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d",&a[i][j]);
			if(a[i][j]){
				v.push_back(pi(i, j));
				cx += i;
				cy += j;
			}
		}
	}
	cx /= v.size();
	cy /= v.size();
	double dis = 0;
	for(auto &i : v){
		dis = max(dis, hypot(cx - i.first, cy - i.second));
	}
	for(auto &i : v){
		if(hypot(cx - i.first, cy - i.second) > dis - 0.63){
			w.push_back(i);
		}
	}
	int cnt = 0;
	for(int i=0; i<w.size(); i++){
		if(!vis[i]) dfs(i), cnt++;
	}
	if(cnt <= 15){
		cnt = go_small();
	}
	cout << cnt;
}
