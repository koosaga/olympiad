#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

char str[1000005];
int n, a, b, c;

bool l[1000005], r[1000005];
int ps[1000005], cnt[100005];

int main(){
	scanf("%d %d %d %d %s",&n,&a,&b,&c,str);
	int cur = 0;
	for(int i=0; i<n; i++){
		cur = cur * 10 + str[i] - '0';
		cur %= a;
		if(cur == 0) l[i] = 1;
		ps[i] = (i ? ps[i-1] : 0) * 10 + str[i] - '0';
		ps[i] %= b;
	}
	int ipow = 1;
	cur = 0;
	for(int i=n-1; i>=0; i--){
		cur = cur + (str[i] - '0') * ipow;
		ipow *= 10;
		cur %= c;
		ipow %= c;
		if(cur == 0 && str[i] != '0') r[i] = 1;
	}
	if(str[n-1] == '0') r[n-1] = 1;
	ipow = 1;
	for(int i=n-1; i>=0; i--){
		ps[i] = (1ll * ps[i] * ipow) % b;
		ipow *= 10;
		ipow %= b;
	}
	lint ret = 0;
	for(int i=n-2; i>=0; i--){
		if(l[i] && str[i+1] != '0') ret += cnt[ps[i]];
		if(r[i+1]) cnt[ps[i]]++;
	}
	for(int i=1; i+1<n; i++){
		if(l[i-1] && r[i+1] && str[i] == '0') ret++;
	}
	cout << ret;
}

