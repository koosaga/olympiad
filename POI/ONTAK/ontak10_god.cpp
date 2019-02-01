#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m, c[100005];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&c[i]);
	}
	sort(c+1, c+n+1);
	lint ret = 0;
	int t = 0;
	for(int i=n; i; i--){
		ret += max(c[i] - t, 0);
		t++;
	}
	cout << ret;
}