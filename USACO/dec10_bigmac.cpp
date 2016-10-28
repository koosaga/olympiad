#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, double> pi;

int n, m, a, b;

vector<pi> gph[2005];
long double dis[2005];
int s[25005], e[25005]; long double v[25005];

int main(){
	cin >> n >> m;
	fill(dis, dis + n + 1, 100);
	long double sex; cin >> sex >> a >> b; dis[a] = log(sex);
	for(int i=0; i<m; i++){
		cin >> s[i] >> e[i] >> v[i];
		v[i] = log(v[i]);
	}
	bool upd = 0;
	for(int i=0; i<n; i++){
		upd = 0;
		for(int j=0; j<m; j++){
			if(v[j] + dis[s[j]] < dis[e[j]]){
				dis[e[j]] = v[j] + dis[s[j]];
				upd = 1;
			}
		}
		if(!upd) break;
	}
	if(upd){
		puts("0");
		return 0;
	}
	printf("%.10Lf\n", exp(dis[b]));
}
