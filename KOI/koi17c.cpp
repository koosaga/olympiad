#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;
const int oo = 1e9;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

struct max3{
	int v1, p1;
	int v2, p2;
	int v3, p3;
	void add(int x, int y){
		if(v1 > x){
			v3 = v2; p3 = p2;
			v2 = v1; p2 = p1;
			v1 = x; p1 = y;
		}
		else if(v2 > x){
			v3 = v2; p3 = p2;
			v2 = x; p2 = y;
		}
		else if(v3 > x){
			v3 = x; p3 = y;
		}
	}
	int query(int x, int y){
		if(x != p1 && y != p1) return v1;
		if(x != p2 && y != p2) return v2;
		return v3;
	}
}prec[3005];

int n, m, s, e, x;
int a[3005][3005], dp[3005][3005], p[3005];
priority_queue<pi, vector<pi>, greater<pi> > pq[3005];

char buf[20000];


int main(){
	scanf("%d %d %d %d %d\n",&n,&m,&s,&e,&x);
	for(int i=0; i<n; i++){
		fgets(buf, 20000, stdin);
		int ptr = 0;
		for(int j=1; j<=m; j++){
			while(isspace(buf[ptr])) ptr++;
			while(buf[ptr] && !isspace(buf[ptr])){
				a[i][j] *= 10;
				a[i][j] += buf[ptr++] - '0';
			}
		}
		for(int j=1; j<=m; j++){
			a[i][j] += a[i][j-1];
		}
	}
	for(int i=0; i<n; i++){
		cin >> p[i];
		p[i]--;
	}
	fill(prec, prec + m, (max3){oo, -1, oo, -1, oo, -1});
	for(int i=0; i<n; i++){
		prec[0].add(0, i);
	}
	for(int i=1; i<m; i++){
		for(int j=0; j<n; j++){
			dp[i][j] = 1e9;
			if(i >= s) pq[j].push(pi(prec[i-s].query(p[j], j) - a[j][i-s], i-s));
			while(!pq[j].empty() && pq[j].top().second < i-e) pq[j].pop();
			if(!pq[j].empty()) dp[i][j] = pq[j].top().first + x + a[j][i];
			prec[i].add(dp[i][j], j);
		}
	}
	int ans = 1e9;
	for(int j=m-e; j<m; j++){
		for(int k=0; k<n; k++){
			ans = min(ans, prec[j].query(p[k], k) + a[k][m] - a[k][j]);
		}
	}
	cout << ans;
}
