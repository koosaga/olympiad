#include <bits/stdc++.h>
using namespace std;
const int MAXN = 800005;

int n, w, a[MAXN], chk[MAXN];

int main(){
	cin >> w >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<i-1; j++) chk[a[i-1] + a[j]] = 1;
		for(int j=i+1; j<n; j++){
			if(w - a[i] - a[j] >= 0 && chk[w - a[i] - a[j]]){
				puts("YES");
				return 0;
			}
		}
	}
	puts("NO");
}
