#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;
const int MAXM = 12;

int n, m, k;
char s[MAXN], t[MAXM];
lint l[MAXM][MAXN], r[MAXM][MAXN];

lint solve(int s, int e){
	if(s == e) return 0;
	int mi = (s+e)/2;
	lint ret = solve(s, mi) + solve(mi + 1, e);
	for(int i=1; i<m; i++){
		for(int j=s; j<=mi; j++) l[i][j] = 0;
		for(int j=mi+1; j<=e; j++) r[i][j] = 0;
		for(int j=0; j<=m; j++) l[j][mi+1] = r[j][mi] = 0;
		l[i][mi+1] = 1;
		r[i][mi] = 1;
		for(int j=i-1; j>=0; j--){
			lint sum = 0;
			for(int k=mi; k>=s; k--){
				sum += l[j+1][k+1];
				sum %= mod;
				if(t[j] == ::s[k]) l[j][k] = sum;
				else l[j][k] = 0;
			}
		}
		for(int j=i; j<m; j++){
			lint sum = 0;
			for(int k=mi+1; k<=e; k++){
				sum += r[j][k-1];
				sum %= mod;
				if(t[j] == ::s[k]) r[j+1][k] = sum;
				else r[j+1][k] = 0;
			}
		}
		lint tmp = 0;
		for(int j=s; j<=mi-k; j++) tmp += l[0][j];
		tmp %= mod;
		for(int j=mi+1; j<=e; j++){
			if(j - k >= s && j - k <= mi){
				tmp += l[0][j - k];
				tmp %= mod;
			}
			ret += r[m][j] * tmp % mod;
		}
	}
	return ret % mod;
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	if(m == 1){
		cout << 0 << endl;
		return 0;
	}
	scanf("%s %s", s + 1, t);
	cout << solve(1, n) << endl;
}
