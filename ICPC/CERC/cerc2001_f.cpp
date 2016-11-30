#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
typedef pair<int,int> pi;
typedef long long lint;

int n, b[50005], h[50005], s[50005], v;

int main(){
	cin >> n;
	lint ret = 0;
	for(int i=0; i<n; i++){
		int w, d;
		cin >> b[i] >> h[i] >> w >> d;
		s[i] = w * d;
		ret += 1ll * h[i] * s[i];
	}
	cin >> v;
	if(ret < v){
		puts("OVERFLOW");
		return 0;
	}
	double st = 0, ed = 1e7;
	for(int i=0; i<50; i++){
		double m = (st+ed)/2.0;
		double vol = 0;
		for(int j=0; j<n; j++){
			vol += max(0.0, min(m - b[j], 1.0 * h[j])) * s[j];
		}
		if(v < vol + 1e-6) ed = m;
		else st = m;
	}
	printf("%.2f",st);
}