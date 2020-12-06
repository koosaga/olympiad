#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 800004;

int n;
char str[MAXN];
int f[MAXN];

pi operator+(pi a, pi b){
	return pi(a.first + b.first, a.second + b.second);
}

pi operator-(pi a, pi b){
	return pi(a.first - b.first, a.second - b.second);
}

struct bit{
	pi tree[MAXN];
	void add(int x, pi v){
		for(int i=x; i<MAXN; i+=i&-i) tree[i] = tree[i] + v;
	}
	pi query(int x){
		pi ret(0, 0);
		for(int i=x; i; i-=i&-i) ret = ret + tree[i];
		return ret;
	}
}bit;

lint solve(int x){
	lint ret = 0;
	for(int i=0; i<n; i++){
		ret += abs(f[x + i + 1] - f[x]);
	}
	return ret;
}

int main(){
	scanf("%d %s",&n, str);
	for(int i=0; i<2*n; i++) if(str[i] == 'W') str[i] = 'A';
	for(int i=0; i<2*n; i++){
		f[i + 1] = f[i];
		if(str[i] == 'A') f[i + 1]++;
		if(str[(i + n) % (2 * n)] == 'B') f[i + 1]--;
	}
	for(int i=0; i<2*n; i++) f[i + 2*n] = f[i];
	lint ret = 1e18;
	for(int i=0; i<n; i++) bit.add(MAXN / 2 + f[i], pi(f[i], 1));
	for(int i=0; i<2*n; i++){
		bit.add(MAXN / 2 + f[i + n], pi(f[i + n], 1));
		bit.add(MAXN / 2 + f[i], pi(-f[i], -1));
		lint qp = MAXN / 2 + f[i];
		auto q1 = bit.query(qp);
		auto q2 = bit.query(MAXN - 1) - bit.query(qp);
		qp -= MAXN / 2;
		lint kek = q1.second * qp - q1.first + q2.first - q2.second * qp;
		ret = min(ret, kek);
	}
	cout << 1ll * n * (n - 1) / 2 - ret << endl;
}
