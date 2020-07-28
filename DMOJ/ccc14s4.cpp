// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc14s4
#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
typedef pair<long long,long long> i2;
typedef pair<long long,i2> i3;
typedef pair<long long,i3> i4;
const long long MAXN = 2010;
vector<i4> sweep;
vector<long long> comp;
long long n,tint,total,soma[MAXN],resposta,ultimox;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> tint;
	for(long long i=1;i<=n;i++){
		long long x1,y1,x2,y2,adiciona;
		cin >> x1 >> y1 >> x2 >> y2 >> adiciona;
		sweep.push_back(MP(x1,MP(adiciona,MP(y1,y2))));
		sweep.push_back(MP(x2,MP(-adiciona,MP(y1,y2))));
		comp.push_back(y1);
		comp.push_back(y2);
	}
	sort(comp.begin(),comp.end());
	comp.erase(unique(comp.begin(),comp.end()),comp.end());
	sort(sweep.begin(),sweep.end());
	for(long long i=0;i<(long long)sweep.size();i++){
		total = 0;
		for(long long j=0;j+1<(long long)comp.size();j++) if(soma[j] >= tint) total += (comp[j+1] - comp[j]);
		long long x = sweep[i].first;
		long long delta = sweep[i].second.first;
		long long l = sweep[i].second.second.first;
		long long r = sweep[i].second.second.second;
		l = lower_bound(comp.begin(),comp.end(),l) - comp.begin();
		r = lower_bound(comp.begin(),comp.end(),r) - comp.begin();
		resposta += (x - ultimox)*total;
		ultimox = x;
		for(long long j = l;j<r;j++) soma[j] += delta;
	}
	printf("%lld\n",resposta);
	return 0;
}