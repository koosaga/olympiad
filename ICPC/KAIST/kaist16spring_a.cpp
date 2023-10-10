#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;

char buf[100005];

int n, k;
int a[100005];

int b[100005];

void transform(int x){
	if(x == 0) return;

	memset(b, 0, sizeof(b));
	for(int i=0; i<n; i++){
		for(int j=n-x; j<=n+x; j+=x){
			b[(i+j)%n] += a[i];
		}
	}
	for(int i=0; i<n; i++){
		a[i] = b[i] % 3;
	}
}

int main(){
	cin >> n >> k;
	cin >> buf;
	for(int i=0; i<n; i++){
		if(buf[i] == 'R') a[i] = 2;
		if(buf[i] == 'G') a[i] = 1;
		if(buf[i] == 'B') a[i] = 0;
	}
	int piv = 1;
	while(k){
		for(int j=0; j<k%3; j++){
			transform(piv);
		}
		piv *= 3;
		k /= 3;
		piv %= n;
	}
	for(int i=0; i<3; i++){
		printf("%d ", count(a, a+n, 2-i));
	}
}