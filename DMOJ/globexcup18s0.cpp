// Ivan Carvalho
// Solution to https://dmoj.ca/problem/globexcup18s0
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll check(ll a,ll b,vector<ll>& A, vector<ll>& B){
	ll tot = 0;
	for(int i = 0;i<A.size();i++){
		tot += abs(A[i] - a) + abs(B[i]-b);
	}
	return tot;
}

int main(){

	ll ans;
	int N;
	vector<ll> X,Y;

	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		ll x,y;
		scanf("%lld %lld",&x,&y);
		X.push_back(x);
		Y.push_back(y);
	}

	sort(X.begin(),X.end());
	sort(Y.begin(),Y.end());
	ll x0 = X[N/2],y0 = Y[N/2];

	ans = check(x0,y0,X,Y);
	
	printf("%lld\n",ans);

	return 0;
}
