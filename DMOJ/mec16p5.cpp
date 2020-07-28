// Ivan Carvalho
// Solution to https://dmoj.ca/problem/mec16p5
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> point;
int ccw(point A,point B,point C){
	ll val = A.F*(B.S - C.S) - A.S*(B.F - C.F) + B.F*C.S - B.S*C.F;
	if(val > 0) return 1;
	if(val == 0) return 0;
	return -1;
}
int main(){
	int n;
	scanf("%d",&n);
	vector<point> E,H;
	for(ll i=1;i<=n;i++){
		ll y;
		scanf("%lld",&y);
		E.push_back(point(i,y));
	}
	int k = 0;
	for(int i=0;i < n;i++){
		while(k >= 2 && ccw(H[k-2],H[k-1],E[i]) >= 0){
			k--;
			H.pop_back();
		}
		H.push_back(E[i]);
		k++;
	}
	double resp = 0;
	for(int i = 0;i + 1 < H.size();i++){
		//printf("(%lld,%lld) (%lld,%lld)\n",H[i].F,H[i].S,H[i+1].F,H[i+1].S);
		resp += hypot(H[i].F - H[i+1].F,H[i].S - H[i+1].S);
	}
	printf("%.1lf\n",resp);
	return 0;
}