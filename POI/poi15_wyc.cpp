#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const lint LIM = 1e18 + 696969;

int n, m; lint k;

lint MUL(lint x, lint y){
	if(y && LIM / y < x) return LIM;
	return x * y;
}

struct mtrx{
	lint a[120][120];
	mtrx(){
		memset(a, 0, sizeof(a));
	}
	mtrx(int x){
		memset(a, 0, sizeof(a));
		for(int i=0; i<3*n; i++) a[i][i] = x;
	}
	mtrx operator+(const mtrx &m)const{
		mtrx r;
		for(int i=0; i<3*n; i++){
			for(int j=0; j<3*n; j++){
				r.a[i][j] = min(LIM, a[i][j] + m.a[i][j]);
			}
		}
		return r;
	}
	mtrx operator*(const mtrx &m)const{
		mtrx r;
		for(int i=0; i<3*n; i++){
			for(int j=0; j<3*n; j++){
				for(int k=0; k<3*n; k++){
					r.a[j][k] += MUL(a[j][i], m.a[i][k]);
					if(r.a[j][k] > LIM) r.a[j][k] = LIM;
				}
			}
		}
		return r;
	}
}pwr[62], sum[62], E;

bool Try(mtrx m){
	lint ret = 0;
	for(int i=2*n; i<3*n; i++){
		for(int j=2*n; j<3*n; j++){
			ret += m.a[i][j];
			if(ret >= k) return true;
		}
	}
	return false;
}

int main(){
	cin >> n >> m >> k;
	k += n;
	E = mtrx(1);
	for(int i=0; i<2*n; i++) pwr[0].a[i][i + n]++;
	for(int i=0; i<m; i++){
		int s, e, x; cin >> s >> e >> x;
		s--, e--, x--;
		pwr[0].a[2 * n + s][e + (2 - x) * n]++;
	}
	sum[0] = E;
	int lg = 0;
	for(int i=1; (1ll << i) <= 3 * k; i++){
		lg++;
		pwr[i] = pwr[i-1] * pwr[i-1];
		sum[i] = (pwr[i-1] + E) * sum[i-1];
		if(Try((pwr[lg] + E) * sum[lg])){
			break;
		}
	}
	if((1ll << (lg + 1)) > 3 * k){
		puts("-1");
		return 0;
	}
	mtrx cur(0);
	lint ans = 0;
	for(int i=lg; i>=0; i--){
		if(!Try(cur * pwr[i] + sum[i])){
			cur = cur * pwr[i] + sum[i];
			ans += (1ll << i);
		}
	}
	cout << ans  << endl;
}
