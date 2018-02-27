#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 3005;

int n, m;
char str[MAXN][MAXN];

int R[MAXN], W[MAXN];
int dR[MAXN], dW[MAXN];

int solve(int n){
	for(int i=1; i<=n; i++){
		dR[i] = dR[i-1];
		dW[i] = dW[i-1];
		if(i > 1){
			dR[i] = max(dR[i], dW[i-2]);
			dW[i] = max(dW[i], dR[i-2]);
		}
		if(R[i-1] && W[i]) dR[i]++;
		if(W[i-1] && R[i]) dW[i]++;
	}
	return max(dR[n], dW[n]);
}
bool okR(int x, int y){ return x >= 0 && x < n && y >= 0 && y < m && str[x][y] == 'R'; }
bool okW(int x, int y){ return x >= 0 && x < n && y >= 0 && y < m && str[x][y] == 'W'; }
bool okG(int x, int y){ return x >= 0 && x < n && y >= 0 && y < m && str[x][y] == 'G'; }

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%s", str[i]);
	int ans = 0;
	for(int i=0; i<n+m-1; i++){
		vector<pi> v;
		for(int j=0; j<=i; j++){
			if(okG(j, i-j)) v.push_back(pi(j, i-j));
		}
		for(int i=0; i<v.size(); ){
			int e = i;
			while(e < v.size() && v[e].first - v[i].first == e - i) e++;
			R[0] = okR(v[i].first - 1, v[i].second);
			W[0] = okW(v[i].first, v[i].second + 1);
			for(int j=i; j<e; j++){
				R[j-i+1] = okR(v[j].first, v[j].second-1);
				W[j-i+1] = okW(v[j].first + 1, v[j].second);
			}
			ans += solve(e - i);
			i = e;
		}
	}
	cout << ans << endl;
}

