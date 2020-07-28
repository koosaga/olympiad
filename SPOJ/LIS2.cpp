// Ivan Carvalho
// Solution to https://www.spoj.com/problems/LIS2/
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef tuple<int,int,int> trinca;
const int MAXN = 1e5 + 10;
int X[MAXN],Y[MAXN],N;
vector<int> compressaox,compressaoy,bit[MAXN],compbit[MAXN];
vector<trinca> ordenado;
void precalcu(int posx,int posy){
	while(posx <= N){
		if(compbit[posx].empty() || compbit[posx].back() != posy){
			compbit[posx].push_back(posy);
		}
		posx += LSOne(posx);
	}
}
void precalcq(int posx,int posy){
	while(posx > 0){
		if(compbit[posx].empty() || compbit[posx].back() != posy){
			compbit[posx].push_back(posy);
		}
		posx -= LSOne(posx);
	}
}
void update1d(int posx,int posy,int val){
	posy = lower_bound(compbit[posx].begin(),compbit[posx].end(),posy) - compbit[posx].begin() + 1;
	int M = compbit[posx].size();
	while(posy <= M){
		bit[posx][posy] = max(bit[posx][posy],val);
		posy += LSOne(posy);
	}
}
void update2d(int posx,int posy,int val){
	while(posx <= N){
		update1d(posx,posy,val);
		posx += LSOne(posx);
	}
}
int query1d(int posx,int posy){
	posy = lower_bound(compbit[posx].begin(),compbit[posx].end(),posy) - compbit[posx].begin() + 1;
	int ans = 0;
	while(posy > 0){
		ans = max(bit[posx][posy],ans);
		posy -= LSOne(posy);
	}
	return ans;
}
int query2d(int posx,int posy){
	int ans = 0;
	while(posx > 0){
		ans = max(ans, query1d(posx,posy) );
		posx -= LSOne(posx);
	}
	return ans;
}
int main(){
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		scanf("%d %d",&X[i],&Y[i]);
		compressaox.push_back(X[i]);
		compressaoy.push_back(Y[i]);
	}
	sort(compressaox.begin(),compressaox.end());
	sort(compressaoy.begin(),compressaoy.end());
	for(int i = 1;i<=N;i++){
		X[i] = lower_bound(compressaox.begin(),compressaox.end(),X[i]) - compressaox.begin() + 1;
		Y[i] = lower_bound(compressaoy.begin(),compressaoy.end(),Y[i]) - compressaoy.begin() + 1;
		ordenado.push_back(make_tuple(Y[i],X[i],0));
		ordenado.push_back(make_tuple(Y[i]-1,X[i]-1,1));
	}
	sort(ordenado.begin(),ordenado.end());
	for(int i = 0;i<ordenado.size();i++){
		if(get<2>(ordenado[i]) == 0) precalcu(get<1>(ordenado[i]),get<0>(ordenado[i]));
		else precalcq(get<1>(ordenado[i]),get<0>(ordenado[i]));
	}
	for(int i = 1;i<=N;i++) bit[i].assign(compbit[i].size()+2,0);
	int resp = 0;
	for(int i = 1;i<=N;i++){
		int best = query2d(X[i]-1,Y[i]-1) + 1;
		resp = max(resp,best);
		update2d(X[i],Y[i],best);
	}
	printf("%d\n",resp);
	return 0;
}