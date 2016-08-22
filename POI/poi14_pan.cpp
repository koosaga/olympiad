#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int iceil(int s, int v){
	return (s + v - 1) / v;
}

bool insec(pi a, pi b){
	return max(a.first, b.first) <= min(a.second, b.second);
}

pi lintv[25005], rintv[25005];
int sl, sr;

int main(){
	int t; cin >> t;
	while(t--){
		sl = sr = 0;
		int sx, ex, sy, ey;
		cin >> sx >> ex >> sy >> ey;
		int ret = 1;
		int sex1 = 40005, sex2 = 25000;
		if(max(ex, ey) <= 1e7){
			sex1 = 4005;
			sex2 = 2500;
		}
		for(int i=2; i<=sex1; i++){
			if(1ll * iceil(sx, i) * i <= ex && 1ll * iceil(sy, i) * i <= ey){
				ret = i;
			}
		}
		for(int i=sex2; i; i--){
			pi ins = pi(iceil(sx, i), ex / i);
			if(ins.first > ins.second || ins.second <= sex1) continue;
			while(sl && lintv[sl-1].second >= ins.first){
				ins.first = lintv[--sl].first;
			}
			lintv[sl++] = ins;
		}
		for(int i=sex2; i; i--){
			pi ins = pi(iceil(sy, i), ey / i);
			if(ins.first > ins.second || ins.second <= sex1) continue;
			while(sr && rintv[sr-1].second >= ins.first){
				ins.first = rintv[--sr].first;
			}
			rintv[sr++] = ins;
		}
		int pnt = 0;
		for(int i=0; i<sl; i++){
			while(pnt+1 < sr && rintv[pnt+1].first <= lintv[i].second){
				pnt++;
			}
			if(pnt < sr && insec(lintv[i], rintv[pnt])){
				ret = max(ret, min(rintv[pnt].second, lintv[i].second));
			}
		}
		printf("%d\n", ret);
	}
}

