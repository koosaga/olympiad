#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int n, m, a[505][505];
int b[505], c[505];

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d",&a[i][j]);
			if(a[i][j] == 1) a[i][j] = 1e9;
		}
	}
	for(int i=0; i<m; i++){
		scanf("%d",&b[i]);
		for(int j=0; j<n; j++){
			if(b[i] == 0 && a[j][i]){
				puts("-1");
				return 0;
			}
			a[j][i] = min(a[j][i], b[i]);
		}
	}
	for(int i=0; i<n; i++){
		scanf("%d",&c[i]);
	}
	reverse(c, c+n);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(c[i] == 0 && a[i][j]) return !puts("-1");
			a[i][j] = min(a[i][j], c[i]);
		}
	}
	for(int i=0; i<n; i++){
		if(c[i] != *max_element(a[i], a[i] + m)){
			puts("-1");
			return 0;
		}
	}
	for(int i=0; i<m; i++){
		int mx = 0;
		for(int j=0; j<n; j++) mx = max(mx, a[j][i]);
		if(mx != b[i]){
			puts("-1");
			return 0;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++) printf("%d ", a[i][j]);
		puts("");
	}
}

