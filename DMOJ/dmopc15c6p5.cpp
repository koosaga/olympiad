// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c6p5
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 3*1e6 + 10;
int final[MAXN],V[MAXN],N,K;
deque<ii> minq,maxq;
long long tot;
int main(){
	scanf("%d %d",&N,&K);
	for(int i = 1;i<=N;i++){
		scanf("%d",&V[i]);
		final[i] = N;
	}
	int i = 1;
	for(int j = 1;j<=N;j++){
		ii p = ii(V[j],j);
		while(!minq.empty() && minq.back() >= p) minq.pop_back();
		while(!maxq.empty() && maxq.back() <= p) maxq.pop_back();
		minq.push_back(p);
		maxq.push_back(p);
		while(maxq.front().first - minq.front().first > K){
			final[i] = j-1;
			if(maxq.front().second == i) maxq.pop_front();
			if(minq.front().second == i) minq.pop_front();
			i++;
		}
	}
	for(int i = 1;i<=N;i++) tot += final[i] - i + 1;
	printf("%lld\n",tot);
	return 0;
}
