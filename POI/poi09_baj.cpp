#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct node{
	int s, e, aux, dis;
};

int n, m;
bool vis[404][404][27];
int dis[404][404][27];
int par[404][404][27];
char chr[404][404];
pi par2[404][404];

vector<int> gph[405][27], rev[405][27];

void solve(int s, int e){
	if(vis[s][e][0] == 0){
		puts("-1");
		return;
	}
	printf("%d ", dis[s][e][0]);
	string l;
	while(dis[s][e][0] > 1){
		// step 1
		l.push_back(par2[s][e].second - 1 + 'a');
		s = par2[s][e].first;
		e = par[s][e][l.back() + 1 - 'a'];
	}
	printf("%s", l.c_str());
	if(s != e) putchar(chr[s][e]);
	reverse(l.begin(), l.end());
	puts(l.c_str());
}

queue<node> que;

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		que.push({i, i, 0, 0});
		vis[i][i][0] = 1;
	}
	for(int i=0; i<m; i++){
		int s, e;
		char t[3];
		scanf("%d %d %s",&s,&e,t);
		gph[s][*t - 'a' + 1].push_back(e);
		rev[e][*t - 'a' + 1].push_back(s);
		chr[s][e] = *t;
		if(!vis[s][e][0]) que.push({s, e, 0, 1});
		dis[s][e][0] = 1;
		vis[s][e][0] = 1;
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		if(x.aux == 0){
			for(int i=1; i<=26; i++){
				for(auto &j : gph[x.e][i]){
					if(!vis[x.s][j][i]){
						vis[x.s][j][i] = 1;
						dis[x.s][j][i] = x.dis + 1;
						par[x.s][j][i] = x.e;
						que.push({x.s, j, i, x.dis + 1});
					}
				}
			}
		}
		else{	
			for(auto &j : rev[x.s][x.aux]){
				if(!vis[j][x.e][0]){
					vis[j][x.e][0] = 1;
					dis[j][x.e][0] = x.dis + 1;
					par2[j][x.e] = pi(x.s, x.aux);
					que.push({j, x.e, 0, x.dis + 1});
				}
			}
		}
	}
	int q, st;
	cin >> q >> st;
	for(int i=1; i<q; i++){
		int nxt;
		cin >> nxt;
		solve(st, nxt);
		st = nxt;
	}
}
