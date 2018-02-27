#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 2000005;

int aux[2 * MAXN];
void solve(int n, char *str, int *ret){
	// *ret : number of nonobvious palindromic character pair
	for(int i=0; i<n; i++){
		aux[2*i] = str[i];
		aux[2*i+1] = -1;
	}
	int p = 0, c = 0;
	for(int i=0; i<2*n-1; i++){
		int cur = 0;
		if(i <= p) cur = min(ret[2 * c - i], p - i);
		while(i - cur - 1 >= 0 && i + cur + 1 < 2*n-1 && aux[i-cur-1] == aux[i+cur+1]){
			cur++;
		}
		ret[i] = cur;
		if(i + ret[i] > p){
			p = i + ret[i];
			c = i;
		}
	}
}

int n, trie[MAXN][26];
char buf[MAXN];
int term[MAXN], subpal[MAXN];
int ret[2 * MAXN], piv;

bool ispal(int s, int e, int *ret){
	return ret[s+e] >= e - s;
}

int main(){
	scanf("%d",&n);
	lint ans = 0;
	for(int i=0; i<n; i++){
		int l, p = 0;
		scanf("%d %s",&l, buf);
		for(int i=0; i<2*l+4; i++) ret[i] = 0;
		solve(l, buf, ret);
		for(int j=0; j<l; j++){
			if(ispal(j, l - 1, ret)){
				ans += term[p];
				subpal[p]++;
			}
			if(!trie[p][buf[j] - 'a']){
				trie[p][buf[j] - 'a'] = ++piv;
			}
			p = trie[p][buf[j] - 'a'];
		}
		term[p]++;
		ans += subpal[p];
		subpal[p]++;
	}
	ans <<= 1;
	ans += n;
	cout << ans << endl;
}

