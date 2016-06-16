#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <map>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int lim = 1e9 + 2;
 
int a[200005];
 
struct bit{
	map<int, int> bit;
	void add(int x, int v){
		while(x <= lim){
			bit[x] += v;
			x += x & -x;
		}
	}
	int sum(int x){
		int ret = 0;
		while(x){
			ret += bit[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;
 
int main(){
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		if(a[i-1] < a[i]){
			bit.add(a[i-1] + 1, 1);
			bit.add(a[i] + 1, -1);
		}
	}
	for(int i=0; i<m; i++){
		int t; scanf("%d",&t);
		if(t == 1){
			int v;
			scanf("%d",&v);
			printf("%d\n", bit.sum(v));
		}
		else{
			int p, v;
			scanf("%d %d",&p, &v);
			if(a[p-1] < a[p]){
				bit.add(a[p-1] + 1, -1);
				bit.add(a[p] + 1, 1);
			}
			if(a[p] < a[p+1]){
				bit.add(a[p] + 1, -1);
				bit.add(a[p+1] + 1, 1);
			}
			a[p] = v;
			if(a[p-1] < a[p]){
				bit.add(a[p-1] + 1, 1);
				bit.add(a[p] + 1, -1);
			}
			if(a[p] < a[p+1]){
				bit.add(a[p] + 1, 1);
				bit.add(a[p+1] + 1, -1);
			}
		}
	}
}