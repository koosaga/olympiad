// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADACUT/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 3*1e5 + 10;
ll vetor[MAXN],total,N,resp;
int main(){
	scanf("%lld",&N);
	for(ll i = 1;i<=N;i++){
		scanf("%lld",&vetor[i]);
		total += vetor[i];
	}
	resp = total;
	sort(vetor+1,vetor+N+1);
	for(ll i = 1;i<=N;i++){
		resp = min(resp, (N-i+1)*(-vetor[i]) + total);
	}
	printf("%lld\n",resp);
	return 0;
}