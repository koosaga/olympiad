// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoqr16p1
#include <cstdio>
#include <vector>
#include <algorithm>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef long long ll;
const int MAXN = 1e5 + 10;
vector<int> cx,cy;
vector<ii> V[MAXN];
int X[MAXN],Y[MAXN],antes[MAXN],depois[MAXN],baixo[MAXN],cima[MAXN];
int main(){
	int n;
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%d %d",&X[i],&Y[i]);
		cx.push_back(X[i]);
		cy.push_back(Y[i]);
	}
	sort(cx.begin(),cx.end());
	sort(cy.begin(),cy.end());
	unique(cx.begin(),cx.end());
	unique(cy.begin(),cy.end());
	int tamx = cx.size();
	for(int i=1;i<=n;i++){
		X[i] = lower_bound(cx.begin(),cx.end(),X[i]) - cx.begin() + 1;
		Y[i] = lower_bound(cy.begin(),cy.end(),Y[i]) - cy.begin() + 1;
		V[X[i]].push_back(MP(Y[i],i));
	}
	for(int i=1;i<=tamx;i++){
		sort(V[i].begin(),V[i].end());
		for(int j=0;j<V[i].size();j++){
			int t1 = j;
			int t2 = V[i].size() - t1 - 1;
			antes[V[i][j].second] = t1;
			depois[V[i][j].second] = t2;
		}
		V[i].clear();
	}
	for(int i=1;i<=n;i++){
		V[Y[i]].push_back(MP(X[i],i));
	}
	int tamy = cy.size();
	for(int i=1;i<=tamy;i++){
		sort(V[i].begin(),V[i].end());
		for(int j=0;j<V[i].size();j++){
			int t1 = j;
			int t2 = V[i].size() - t1 - 1;
			baixo[V[i][j].second] = t1;
			cima[V[i][j].second] = t2;
		}
		V[i].clear();
	}
	long long resp = 0;
	for(int i=1;i<=n;i++) resp += 2LL*antes[i]*depois[i]*baixo[i]*cima[i];
	printf("%lld\n",resp);
	return 0;
}