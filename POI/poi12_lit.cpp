#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n, nxt[1000005];
char a[1000005], b[1000005];
vector<int> ca[26], cb[26];

struct bit{
	int tree[1000005];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int main(){
	scanf("%d %s %s",&n,a,b);
	for(int i=0; i<n; i++){
		ca[a[i] - 'A'].push_back(i);
		cb[b[i] - 'A'].push_back(i);
	}
	for(int i=0; i<26; i++){
		for(int j=0; j<ca[i].size(); j++){
			nxt[ca[i][j]] = cb[i][j] + 1;
		}
	}
	lint ans = 0;
	for(int i=0; i<n; i++){
		ans += i - bit.query(nxt[i]);
		bit.add(nxt[i],1);
	}
	cout << ans;
}
