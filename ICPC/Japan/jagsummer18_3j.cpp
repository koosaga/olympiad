#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n , m, s, t;
vector<int> gph[MAXN];
int dist[MAXN][2];

queue<pi> que;

int main(){
	cin >> n >> m >> s >> t;
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	memset(dist, 0x3f, sizeof(dist));
	dist[s][0] = 0;
	que.emplace(s, 0);
	while(!que.empty()){
		auto x = que.front(); que.pop();
		for(auto &i : gph[x.first]){
			if(dist[i][x.second^1] > 1 + dist[x.first][x.second]){
				dist[i][x.second^1] = 1 + dist[x.first][x.second];
				que.emplace(i, x.second ^ 1);
			}
		}
	}
	for(int i=2; i<=2*n+1000; i++){
		bool isprime = 1;
		for(int j=2; j*j<=i; j++){
			if(i % j == 0) isprime = 0;
		}
		if(isprime && dist[t][i%2] <= i){
			cout << i << endl;
			return 0;	
		}
	}
	cout << -1 << endl;
}
