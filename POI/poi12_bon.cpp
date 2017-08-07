#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 9;
const int MAXN = 1000000;

set<int> s;
int n, m, x;
int mxp[MAXN + 5], ocp[MAXN + 5], vou[MAXN + 5];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&x);
		vou[x] = i;
	}
	fill(mxp, mxp + MAXN + 5, 1);
	scanf("%d",&m);
	vector<lint> ret;
	lint sum = 0;
	for(int i=0; i<m; i++){
		scanf("%d",&x);
		for(int j=0; j<x && x * mxp[x] <= MAXN; j++){
			while(mxp[x] * x <= MAXN && ocp[mxp[x] * x]) mxp[x]++;
			if(x * mxp[x] <= MAXN){
				if(vou[x * mxp[x]]) ret.push_back(sum + j + 1);
				ocp[mxp[x] * x] = 1;
				mxp[x]++;
			}
		}
		sum += x;
	}
	printf("%d\n", ret.size());
	for(auto &i : ret) printf("%lld\n", i);
}
