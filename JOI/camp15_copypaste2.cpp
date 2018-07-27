#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 200005;

char str[MAXN];
int s[MAXN], e[MAXN], x[MAXN];

int main(){
	int n, m, q;
	cin >> n >> m >> str >> q;
	for(int i=0; i<q; i++) scanf("%d %d %d",&s[i],&e[i],&x[i]);
	for(int i=0; i<n; i++){
		int pos = i;
		for(int j=q-1; j>=0; j--){
			int L = e[j] - s[j];
			if(pos >= x[j] + L){
				pos -= L;
			}
			else if(pos >= x[j]){
				pos = (pos - x[j]) + s[j];
			}
		}
		putchar(str[pos]);
	}
}
