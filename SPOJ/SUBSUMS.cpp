// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SUBSUMS/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> somas;
ll N,A,B,v1[20],v2[20],N1,N2,resp;
int main(){
	cin >> N >> A >> B;
	ll metade = N/2;
	for(ll i = 0;i<=metade;i++){
		//printf("%lld\n",i);
		cin >> v1[N1++];
	}
	for(ll i = metade + 1;i < N;i++){
		//printf("%lld\n",i);
		cin >> v2[N2++];
	}
	for(ll bitmask = 1;bitmask < (1 << N1);bitmask++){
		ll somatorio = 0;
		for(ll i = 0;i<N1;i++){
			if(bitmask & (1 << i)){
				somatorio += v1[i];
			}
		}
		if(A <= somatorio && somatorio <= B) resp++;
		somas.push_back(somatorio);
	}	
	sort(somas.begin(),somas.end());
	for(ll bitmask = 1;bitmask < (1 << N2);bitmask++){
		ll somatorio = 0;
		for(ll i = 0;i<N2;i++){
			if(bitmask & (1 << i)){
				somatorio += v2[i];
			}
		}
		if(A <= somatorio && somatorio <= B) resp++;
		if(B - somatorio < somas[0] || A - somatorio > somas.back()) continue;
		ll comeco = lower_bound(somas.begin(),somas.end(),A - somatorio) - somas.begin() + 1;
		ll fim = prev(upper_bound(somas.begin(),somas.end(),B - somatorio)) - somas.begin() + 1;
		resp += fim - comeco + 1;
	}
	if(A <= 0 && 0 <= B) resp++;
	printf("%lld\n",resp);
	return 0;
}