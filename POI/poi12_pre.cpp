#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 1000005;

vector<int> get_fail(string str){
	int n = str.size();
	int p = 0;
	vector<int> fail(n + 1);
	for(int i=1; i<n; i++){
		while(p && str[p] != str[i]) p = fail[p];
		if(str[p] == str[i]) p++;
		fail[i + 1] = p;
	}
	return fail;
}

int n;
string s;
char t[MAXN];

int aux[2 * MAXN - 1];
int ret[2 * MAXN - 1];
void solve(int n, char *str, int *ret){
	// *ret : number of nonobvious palindromic character pair
	for(int i=0; i<n; i++){
		aux[2*i] = str[i];
		if(i != n-1) aux[2*i+1] = -1;
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

bool ok(int x, int y){
	assert(x%2 != y%2);
	return ret[x+y] >= y-x;
}

int chk[MAXN];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    for(int i=0; i<n/2; i++){
    	t[2*i] = s[n-i-1];
		t[2*i+1] = s[i];
	}
	int m = (n/2)*2;
	reverse(t, t + m);
	solve(m, t, ret);
	vector<int> fail = get_fail(s);
	for(int i=fail[n]; i; i=fail[i]){
		if(i <= n / 2){
			chk[m - 2 * i] = 1;
		}
	}
	int p = 0;
	int ret = 0;
	if(chk[0]) ret = m;
	for(int i=1; i<=m; i++){
		if(p && ok(p - 1, i - 1)) p--;
		else p++;
		while(!ok(p, i - 1)) p+=2;
		if(chk[i]) ret = max(ret, m - p);
	}
	assert(ret%2==0);
	cout << ret/2 << endl;
}

