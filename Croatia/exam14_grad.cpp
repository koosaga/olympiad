#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 100005;
typedef long long lint;

struct mat{
	double adj[3][3];
}spt[17][MAXN];
int par[17][MAXN], dep[MAXN];

mat merge(mat s, mat e){
	mat x;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			x.adj[i][j] = 1e18;
			for(int k=0; k<3; k++){
				x.adj[i][j] = min(x.adj[i][j], s.adj[i][k] + e.adj[k][j]);
			}
		}
	}
	return x;
}

double dist(pi a, pi b){
	return hypot(a.first - b.first, a.second - b.second);
}

int lca(int s, int e){
	if(dep[s] < dep[e]) swap(s, e);
	int dx = dep[s] - dep[e];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) s = par[i][s];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

int n = 2;
pi a[MAXN * 2];
pi pos[MAXN * 2];
int num[MAXN][3];

mat init(int p){
	mat r;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			r.adj[i][j] = dist(a[num[p][i]], a[num[p][j]]);
		}
	}
	return r;
}

mat path(int s, int e){
	int dx = dep[s] - dep[e];
	mat m = init(s);
	for(int i=0; i<17; i++){
		if((dx >> i) & 1){
			m = merge(m, spt[i][s]);
			s = par[i][s];
		}
	}
	return m;
}

double query(pi s, pi e){
	int l = lca(s.first, e.first);
	mat m = path(s.first, l);
	mat n = path(e.first, l);
	double ans = 1e18;
	for(int i=0; i<3; i++){
		ans = min(ans, m.adj[s.second][i] + n.adj[e.second][i]);
	}
	return ans;
}

int main(){
	for(int i=1; i<=2; i++){
		cin >> a[i].first >> a[i].second;
	}
	int q;
	cin >> q;
	char buf[5];
	while(q--){
		scanf("%s", buf);
		if(*buf == 'u'){
			int x, y;
			scanf("%d %d",&x,&y);
			if(n == 2){
				printf("%.5f\n", dist(a[x], a[y]));
			}
			else{
				printf("%.5f\n", query(pos[x], pos[y]));
			}
		}
		else{
			n++;
			scanf("%d %d",&a[n].first,&a[n].second);
			int p, q;
			scanf("%d %d",&p,&q);
			if(n == 3){
				pos[1] = pi(1, 0);
				pos[2] = pi(1, 1);
				pos[3] = pi(1, 2);
				num[1][0] = 1, num[1][1] = 2, num[1][2] = 3;
			}
			else{
				pos[n] = pi(n-2, 2);
				num[n-2][0] = p, num[n-2][1] = q, num[n-2][2] = n;
				if(pos[p].first > pos[q].first) swap(p, q);
				par[0][n-2] = pos[q].first;
				int prv = par[0][n-2];
				int cur = n-2;
				dep[cur] = dep[prv] + 1;
				set<pi> s;
				for(int i=0; i<3; i++){
					for(int j=0; j<3; j++){
						if(i == j) continue;
						s.insert(pi(num[prv][i], num[prv][j]));
						s.insert(pi(num[cur][i], num[cur][j]));
					}
				}
				mat m;
				for(int j=0; j<3; j++){
					for(int k=0; k<3; k++){
						if(num[cur][j] == num[prv][k]) m.adj[j][k] = 0;
						else if(s.find(pi(num[cur][j], num[prv][k])) != s.end()){
							m.adj[j][k] = dist(a[num[cur][j]], a[num[prv][k]]);
						}
						else m.adj[j][k] = min(dist(a[num[cur][j]], a[p]) + dist(a[p], a[num[prv][k]]),
								dist(a[num[cur][j]], a[q]) + dist(a[q], a[num[prv][k]]));
					}
				}
				spt[0][cur] = m;
				for(int i=1; i<17; i++){
					par[i][cur] = par[i-1][par[i-1][cur]];
					spt[i][cur] = merge(spt[i-1][cur], spt[i-1][par[i-1][cur]]);
				}
			}
		}
	}
}
