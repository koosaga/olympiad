#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using ll = long long;
const int MAXN = 1000005;

int n, a[MAXN];
int choice[MAXN];
int indeg[MAXN];
bool inq[MAXN];

bool bad(int x){
	int cur_idx = (x + choice[x]) % n;
	int nxt_idx = (x + 1 - choice[x]) % n;
	int cur_profit = a[cur_idx] / indeg[cur_idx];
	int nxt_profit = a[nxt_idx] / (indeg[nxt_idx] + 1);
	return nxt_profit > cur_profit;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		a[i] *= 2;
	}
	a[n] = a[0];
	for(int i=0; i<n; i++){
		if(a[i] < a[i + 1]) choice[i] = 1;
		indeg[(i + choice[i]) % n]++;
	}
	queue<int> que;
	auto enq = [&](int x){
		if(!inq[x]){
			inq[x] = 1;
			que.push(x);
		}
	};
	for(int i=0; i<n; i++){
		if(bad(i)) enq(i);
	}
	while(sz(que)){
		int x = que.front(); que.pop();
		inq[x] = 0;
		indeg[(x + choice[x]) % n]--;
		choice[x] ^= 1;
		indeg[(x + choice[x]) % n]++;
		if(bad((x + 1) % n)) enq((x + 1) % n);
		if(bad((x + n - 1) % n)) enq((x + n - 1) % n);
	}
	for(int i=0; i<n; i++) printf("%d ", 1 + (i + choice[i]) % n);
}
