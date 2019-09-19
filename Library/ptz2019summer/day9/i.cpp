#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;

int n, m;
int d[MAXN];
bool mark[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d",&d[i]);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		if((d[s] + 1) % 3 == d[e]) mark[e] = 1;
		if((d[e] + 1) % 3 == d[s]) mark[s] = 1;
	}
	for(int i=1; i<=n; i++){
		if(!mark[i]){
			cout << i << endl;
			return 0;
		}
	}
}
