#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m;
char str[777][777];
lint d[4][777][777];
int up[777];

lint getsum(int p, int sx, int ex, int sy, int ey){
	if(sx > ex || sy > ey) return 0;
	return d[p][ex][ey] - (sx ? d[p][sx-1][ey] : 0) - (sy ? d[p][ex][sy-1] : 0) + 
		(sx && sy ? d[p][sx-1][sy-1] : 0);
}

vector<int> solve(int *p){
	vector<int> ret(m);
	stack<int> stk;
	int ans = 0;
	for(int i=0; i<m; i++){
		while(!stk.empty() && p[stk.top()] >= p[i]){
			int prv = stk.top();
			stk.pop();
			ans -= (p[prv] - p[i]) * (prv - (stk.empty() ? -1 : stk.top()));
		}
		stk.push(i);
		ans += p[i];
		ret[i] = ans;
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%s", str[i]);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '0') up[j] = 0;
			else up[j]++;
		}
		vector<int> v = solve(up);
		for(int j=0; j<m; j++){
			d[0][i][j] = v[j];
		}
		reverse(up, up + m);
		v = solve(up);
		for(int j=m-1; j>=0; j--){
			d[1][i][j] = v[m-1-j];
		}
		reverse(up, up + m);
	}
	memset(up, 0, sizeof(up));
	for(int i=n-1; i>=0; i--){
		for(int j=0; j<m; j++){
			if(str[i][j] == '0') up[j] = 0;
			else up[j]++;
		}
		vector<int> v = solve(up);
		for(int j=0; j<m; j++){
			d[2][i][j] = v[j];
		}
		reverse(up, up + m);
		v = solve(up);
		for(int j=m-1; j>=0; j--){
			d[3][i][j] = v[m-1-j];
		}
		reverse(up, up + m);
	}
	for(int i=0; i<4; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<m; k++){
				if(j) d[i][j][k] += d[i][j-1][k];
				if(k) d[i][j][k] += d[i][j][k-1];
				if(j && k) d[i][j][k] -= d[i][j-1][k-1];
			}
		}
	}
	lint ans = 1e18;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] != '1') continue;
			lint l = getsum(0, 0, i-1, 0, m-1) + getsum(2, i+1, n-1, 0, m-1) +
				getsum(0, 0, n-1, 0, j-1) + getsum(1, 0, n-1, j+1, m-1) - 
				getsum(0, 0, i-1, 0, j-1) - getsum(1, 0, i-1, j+1, m-1) - 
				getsum(2, i+1, n-1, 0, j-1) - getsum(3, i+1, n-1, j+1, m-1);
			ans = min(ans, l);
		}
	}
	printf("%lld\n", ans);
}
