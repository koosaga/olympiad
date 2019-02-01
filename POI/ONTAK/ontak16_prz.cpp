#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

lint dis1[105][100005], dis2[105][100005];
lint dp[205][105][105], tab[105][105];

int n, m, k, s, q, pos[105];
vector<pi> gph[100005], rev[100005];

void dijk1(lint *d, int s){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.push(pi(0, s));
	d[s] = 0;
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(d[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(d[i.second] > d[x.second] + i.first){
				d[i.second] = d[x.second] + i.first;
				pq.push(pi(d[i.second], i.second));
			}
		}
	}
}

void dijk2(lint *d, int s){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.push(pi(0, s));
	d[s] = 0;
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(d[x.second] != x.first) continue;
		for(auto &i : rev[x.second]){
			if(d[i.second] > d[x.second] + i.first){
				d[i.second] = d[x.second] + i.first;
				pq.push(pi(d[i.second], i.second));
			}
		}
	}
}

int main(){
	scanf("%d %d %d %d %d",&n,&m,&k,&s,&q);
	for(int i=0; i<k; i++){
		scanf("%d",&pos[i]);
	}
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		rev[e].push_back(pi(x, s));
	}
	memset(dis1, 0x3f, sizeof(dis1));
	memset(dis2, 0x3f, sizeof(dis2));
	memset(dp, 0x3f, sizeof(dp));
	for(int i=0; i<k; i++){
		dijk1(dis1[i], pos[i]);
		dijk2(dis2[i], pos[i]);
		dp[0][i][i] = 0;
		for(int j=0; j<k; j++){
			if(i == j && s == 1) tab[i][j] = 0;
			else tab[i][j] = 1e18;
		}
	}
	for(int i=1; i<=k+s; i++){
		for(int j=0; j<k; j++){
			for(int l=0; l<k; l++){
				for(int m=0; m<k; m++){
					if(m == l) continue;
					dp[i][j][l] = min(dp[i][j][l], dp[i-1][j][m] + dis1[m][pos[l]]);
				}
				if(i >= s-1) tab[j][l] = min(tab[j][l], dp[i][j][l]);
			}
		}
	}
	while(q--){
		int s, e;
		scanf("%d %d",&s,&e);
		lint ret = 1e18;
		for(int i=0; i<k; i++){
			for(int j=0; j<k; j++){
				ret = min(ret, tab[i][j] + min(ret, dis1[j][e] + dis2[i][s]));
			}
		}
		if(ret > 1e17) ret = -1;
		printf("%lld\n", ret);
	}
}
