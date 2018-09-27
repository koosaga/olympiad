#include <bits/stdc++.h>
using namespace std;
using real_t = double;
const int mod = 1e9 + 7;
const int MAXN = 10005;

int n, a[MAXN], k;

int main(){
	cin >> n >> k;
	fill(a + 1, a + n, -1);
	k += n * (n - 1) / 2;
	if(k < 0 || k > n * (n - 1) || k % 2){
		puts("NIE");
		return 0;
	}
	k /= 2;
	for(int i=1; i<n; i++){
		if(k >= n - i){
			a[i] += 2;
			k -= n - i;
		}
	}
	for(int i=0; i<n; i++){
		if(i) a[i] += a[i-1];
		printf("%d\n", a[i]);
	}
}
