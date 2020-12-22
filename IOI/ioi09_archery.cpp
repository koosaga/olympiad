#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 400005;
const int mod = 1e9 + 7;
 
int n, r, a[MAXN], b[MAXN];
int cnt[MAXN][3];
 
int Do(int r, int s){
	if(s == 1) return 0;
	memset(cnt, 0, sizeof(cnt));
	auto mode = [&](int x){
		if(x < s) return 0;
		if(x == s) return 1;
		return 2;
	};
	if(s > n + 1){
		int myOrig = -1;
		for(int i = 0; i < n; i++){
			int pos = i;
			if(pos == 0) pos = n - 1;
			if(a[i] > n + 1) cnt[pos][mode(a[i])]++;
			if(a[i+n] > n + 1) cnt[pos][mode(a[i+n])]++;
			if(a[i] == s) myOrig = i;
			if(a[i+n] == s) myOrig = i;
		}
		pi minp(0, n-1);
		int cur = 0;
		for(int i=n-1; i>=1; i--){
			cur += cnt[i][0] + cnt[i][1] + cnt[i][2] - 1;
			minp = max(minp, pi(-cur, i-1));
		}
		int cand[3] = {};
		vector<int> reside(n);
		for(int i = 0; i < n - 1; i++){
			int pos = minp.second - i + 2 * (n-1) - 1;
			pos %= n - 1;
			pos += 1;
			for(int j=0; j<3; j++) cand[j] += cnt[pos][j];
			int ptr = 2;
			while(ptr >= 0 && !cand[ptr]) ptr--;
			assert(ptr >= 0);
			cand[ptr]--;
			reside[pos] = ptr;
		}
		int myPos = find(all(reside), 1) - reside.begin();
		assert(myPos < n);
		int rotated = (myPos > myOrig); 
		return myPos - rotated * n;
	}
	else{
		for(int i = 0; i < n; i++){
			cnt[i][mode(a[i])]++;
			cnt[i][mode(a[i + n])]++;
		}
		int winner = 0;
		int rotated = 0;
		while(!cnt[0][winner]) winner++;
		cnt[0][winner]--;
		int cand[3] = {};
		for(int i = 1; i <= 3 * n; i++){
			for(int j=0; j<3; j++){
				cand[j] += cnt[(i-1)%n][j];
				cnt[(i-1)%n][j] = 0;
			}
			int loser = 0;
			while(!cand[loser]) loser++;
			cand[loser]--;
			if(winner > loser) swap(winner, loser);
			// deport loser after round i
			cnt[(i-1)%n][loser]++;
			if(loser == 1){
				rotated++;
				if(i > 2 * n){
					int will_move = (r + n - i) % n;
					if(r < i) rotated--;
					return (n - 1 - will_move) % n - (rotated) * n;
				}
			}
		}
	}
}
  
int main(){
	scanf("%d %d",&n,&r);
	for(int i=0; i<2*n; i++){
		scanf("%d",&b[i]);
	}
	r = (r % n) + 2 * n;
	int s = 0, e = n - 1;
	auto fn = [&](int i){
		vector<int> foo(b, b + 2 * n);
		rotate(foo.begin(), foo.begin() + 1, foo.begin() + 2 * i + 1);
		for(int i=0; i<n; i++){
			a[i] = foo[2*i];
			a[i+n] = foo[2*i+1];
		}
		return Do(r, b[0]);
	};
	auto Mod = [&](int x){ return (x % n + n) % n; };
	int qq = fn(n - 1);
	while(s != e){
		int m = (s + e) / 2;
		if(fn(m) >= qq - Mod(qq)) e = m;
		else s = m + 1;
	}
	int rr = fn(s);
	s = 0, e = n - 1;
	while(s != e){
		int m = (s + e + 1) / 2;
		if(fn(m) <= rr) s = m;
		else e = m - 1;
	}
	cout << s + 1 << endl;
}

