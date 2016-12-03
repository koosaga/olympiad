#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

int n, m;
int a[105], b[105], c[105];
int x[50005], y[50005];

bool colinear(int x, int y){
	return a[x] * b[y] == a[y] * b[x];
}

bool solve(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i], &b[i], &c[i]);
	}
	for(int i=0; i<m; i++){
		scanf("%d %d",&x[i], &y[i]);
	}
	int area = 1;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(!colinear(i, j)) area++;
		}
		area++;
	}
	set<pi> s;
	for(int i=0; i<m; i++){
		pi tmp(0, 0);
		for(int j=0; j<n; j++){
			if(1ll * a[j] * x[i] + 1ll * b[j] * y[i] + c[j] > 0){
				if(j >= 60) tmp.first |= (1ll << (j - 60));
				else tmp.second |= (1ll << j);
			}
		}
		s.insert(tmp);
	}
	return s.size() == area;
}

int main(){
	int t;
	cin >> t;
	while(t--){
		puts(solve() ? "PROTECTED" : "VULNERABLE");
	}
}
