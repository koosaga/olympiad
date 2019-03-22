#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 1000005;

int n, a[MAXN], cnt[MAXN];
bool isprime(int x){
	if(x <= 1) return 0;
	for(int i=2; i*i<=x; i++){
		if(x%i == 0) return 0;
	}
	return 1;
}

int main(){
	int l, r;
	cin >> l >> r;
	for(int i=l; i<=r; i++){
		a[n++] = i;
	}
	for(int i=2; i<=40000; i++){
		int s = ((l + i - 1) / i) * i - l;
		for(int j=s; j<n; j+=i){
			while(a[j] % i == 0){
				a[j] /= i;
				cnt[j]++;
			}
		}
	}
	int dap = 0;
	for(int i=0; i<n; i++){
		if(a[i] > 1) cnt[i]++;
		if(isprime(cnt[i])) dap++;
	}
	cout << dap << endl;
}
