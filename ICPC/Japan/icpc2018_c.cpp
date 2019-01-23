#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int n, m, q;
int cnt[MAXN];

int main(){
	scanf("%d %d %d",&n,&m,&q);
	while(q--){
		int x, y; scanf("%d %d",&x,&y);
		int l = n + 1 - x;
		if(y <= m) l += m - y + 1;
		else l += y - m;
		cnt[l]++;
	}
	for(int i=0; i<MAXN; i++){
		if(cnt[i] > 1){
			cnt[i+1] += cnt[i] - 1;
			cnt[i] = 1;
		}
	}
	for(int i=MAXN-1; i>=0; i--){
		if(cnt[i]){
			cout << i << endl;
			return 0;
		}
	}

}
