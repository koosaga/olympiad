#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct disj{
	int pa[2005];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int gcd(int x, int y){
	return y ? gcd(y, x%y) : x;
}

int main(){
	int t;
	cin >> t;
	for(int i=0; i<t; i++){
		int n;
		cin >> n;
		disj.init(n*2);
		int x[1005], y[1005], r[1005];
		for(int i=0; i<n; i++){
			cin >> x[i] >> y[i] >> r[i];
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<i; j++){
				int dx = x[j] - x[i];
				int dy = y[j] - y[i];
				if(dx * dx + dy * dy == (r[i] + r[j]) * (r[i] + r[j])){
					disj.uni(i, n+j);
					disj.uni(n+i, j);
				}
			}
		}
		for(int i=0; i<n; i++){
			if(disj.find(i) == disj.find(0)){
				int t1 = r[0] / gcd(r[0], r[i]);
				int t2 = r[i] / gcd(r[0], r[i]);
				if(t2 == 1) printf("%d clockwise\n",t1);
				else printf("%d/%d clockwise\n",t1,t2);
			}
			else if(disj.find(i) == disj.find(n)){
				int t1 = r[0] / gcd(r[0], r[i]);
				int t2 = r[i] / gcd(r[0], r[i]);
				if(t2 == 1) printf("%d counterclockwise\n",t1);
				else printf("%d/%d counterclockwise\n",t1,t2);
			}
			else{
				puts("not moving");
			}
		}
	}
}