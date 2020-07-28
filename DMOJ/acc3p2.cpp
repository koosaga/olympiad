// Ivan Carvalho
// Solution to https://dmoj.ca/problem/acc3p2
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll check(ll a,ll b,vector<ll>& A, vector<ll>& B){
	ll tot = 0;
	for(int i = 0;i<A.size();i++){
		tot += max(abs(A[i] - a),abs(B[i]-b));
	}
	return tot;
}

int main(){

	ll ans = 1e18;
	int N;
	vector<ll> X,Y,oX,oY;

	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		ll x,y;
		scanf("%lld %lld",&x,&y);
		oX.push_back(x);
		oY.push_back(y);
		X.push_back(x+y);
		Y.push_back(x-y);
	}

	sort(X.begin(),X.end());
	sort(Y.begin(),Y.end());
	ll s1 = X[N/2],s2 = Y[N/2];
	ll x0 = (s1+s2)/2;
	ll y0 = s1 - x0;

	for(int i = -2;i<=2;i++){
		for(int j = -2;j<=2;j++){
			ans = min(ans, check(x0+i,y0+j,oX,oY) );
		}
	}
	
	printf("%lld\n",ans);

	return 0;
}
