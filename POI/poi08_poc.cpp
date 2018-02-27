#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef unsigned long long hash_t;
typedef pair<int, int> pi;

const int MAXN = 1005;
const int MAXL = 105;

hash_t magic[MAXL];
hash_t value[MAXN];

int n, m, q;
char str[MAXN][MAXL];
int pcnt;

map<hash_t, int> mp;

int ans[MAXN];

void insert(hash_t hv){
	mp[hv]++;
	int tmp = mp[hv];
	for(int i=0; i<n; i++){
		if(value[i] == hv) ans[i] = max(ans[i], tmp);
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&q);
	mt19937 rng(time(0));
	for(int i=0; i<m; i++) magic[i] = uniform_int_distribution<hash_t>(0ull, ~0ull)(rng); 
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
		for(int j=0; j<m; j++){
			value[i] += str[i][j] * magic[j];
		}
	}
	for(int i=0; i<n; i++) insert(value[i]);
	while(q--){
		int p1, w1, p2, w2;
		scanf("%d %d %d %d",&p1,&w1,&p2,&w2);
		p1--, w1--, p2--, w2--;
		mp[value[p1]]--;
		if(p2 != p1) mp[value[p2]]--;
		value[p1] -= str[p1][w1] * magic[w1];
		value[p2] -= str[p2][w2] * magic[w2];
		swap(str[p1][w1], str[p2][w2]);
		value[p1] += str[p1][w1] * magic[w1];
		value[p2] += str[p2][w2] * magic[w2];
		insert(value[p1]);
		if(p2 != p1) insert(value[p2]);
	}
	for(int i=0; i<n; i++) printf("%d\n", ans[i]);
}


