#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
//typedef pair<int, int> pi;
const int mod = 1e9 + 7;

struct pi{
	int first, second, x;
	bool operator<(const pi &a)const{
		if(first != a.first) return first < a.first;
		return second < a.second;
	}
}a[100005];

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p&1) ret *= piv;
		piv *= piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret;
}

int n, m, k, nok = 0;

int solve(){
	set<int> s;
	sort(a, a+k);
	int cnt = 0;
	for(int i=0; i<k; ){
		int e = i;
		while(e < k && a[i].first == a[e].first) e++;
		for(int j=i+1; j<e; j++){
			if((a[j].second + a[j].x) % 2 != (a[i].second + a[i].x) % 2){
				nok = 1;
				return 0;
			}
		}
		cnt++;
		i = e;
	}
	return ipow(2, n - cnt);
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	char buf[3];
	for(int i=0; i<k; i++){
		scanf("%s %d %d",buf,&a[i].first,&a[i].second);
		a[i].x = (*buf == '-');
	}
	lint s = solve();
	swap(n, m);
	for(int i=0; i<k; i++) swap(a[i].first, a[i].second);
	s += solve();
	if(!nok){
		if(k > 0) s = (s + mod - 1) % mod;
		else s = (s + mod - 2) % mod;
	}
	cout << s % mod;
}
