#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, k, a[2005];
int d1[2005][2005][2], d2[2005][2005][2];

int f1(int pos, int cnt, int bef){
	if(cnt < 0) return -2e9;
	if(pos <= 0) return 0;
	if(~d1[pos][cnt][bef]) return d1[pos][cnt][bef];
	if(bef == 0){
		return d1[pos][cnt][bef] = max(f1(pos-1, cnt, 0), f1(pos-1, cnt-1, 1) + a[pos]);
	}
	else{
		return d1[pos][cnt][bef] = max(f1(pos-1, cnt, 0), f1(pos-2, cnt-1, 1) + a[pos] + (pos > 1 ? a[pos-1] : 0));
	}
}

int f2(int pos, int cnt, int bef){
	if(pos == 2){
		if(cnt <= 0) return -2e9;
		return a[1] + a[2];
	}
	if(pos == 1){
		if(cnt < 0) return -2e9;
		if(bef == 1){
			return a[1];
		}
		return -2e9;
	}
	if(cnt < 0) return -2e9;
	if(~d2[pos][cnt][bef]) return d2[pos][cnt][bef];
	if(bef == 0){
		return d2[pos][cnt][bef] = max(f2(pos-1, cnt, 0), f2(pos-1, cnt-1, 1) + a[pos]);
	}
	else{
		return d2[pos][cnt][bef] = max(max(f2(pos-1, cnt-1, 1) + a[pos], f2(pos-1, cnt, 0)), f2(pos-2, cnt-1, 1) + a[pos] + (pos > 1 ? a[pos-1] : 0));
	}
}

int solve(){
	if(k >= (n+1)/2){
		int ret = 0;
		for(int i=1; i<=n; i++) ret += a[i];
		return ret;
	}
	memset(d1, -1, sizeof(d1));
	memset(d2, -1, sizeof(d2));
	int ret = f1(n, k, 0);
	int cur = a[n], cnt = 1;
	for(int i=n; i>=3 && cnt < k; i-=2){
		ret = max(ret, cur + f2(i-1, k-cnt, 1));
		cnt++;
		cur += a[i-1] + a[i-2];
	}
	return ret;
}

int main(){
	cin >> n >> k;
	for(int i=1; i<=n; i++) cin >> a[i];
	int ret = solve();
	reverse(a+1, a+n+1);
	ret = max(ret, solve());
	cout << ret;
}
