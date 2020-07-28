// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c2p5
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef tuple<int,int,int,int> quadra;
const double EPS = 1e-8;
const int MAXN = 702;
const int MAXM = 702*702;
int conversao[MAXN][MAXN];
int H[MAXN][MAXN],V[MAXN][MAXN];
int last[MAXM],pai[MAXM],sz[MAXM],granderesposta,ultimot,N,ptr,original[MAXM];
vector<quadra> sweep;
int find(int x){
	if(last[x] != ultimot){
		pai[x] = x;
		sz[x] = original[x];
		last[x] = ultimot;
	}
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);y = find(y);
	if(x == y) return;
	if(x > y) swap(x,y);
	pai[y] = x;
	sz[x] += sz[y];
	granderesposta = max(granderesposta,sz[x]);
}
bool compara(quadra Q1,quadra Q2){
	return 1LL*get<0>(Q1)*get<1>(Q2) < 1LL*get<0>(Q2)*get<1>(Q1);
}
bool igual(quadra Q1,quadra Q2){
	return 1LL*get<0>(Q1)*get<1>(Q2) == 1LL*get<0>(Q2)*get<1>(Q1);
}
int main(){
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		for(int j = 1;j<=N;j++){
			scanf("%d",&H[i][j]);
			conversao[i][j] = ++ptr;
			pai[ptr] = ptr;
			sz[ptr] = 1;
		}
	}
	for(int i = 1;i<=N;i++){
		for(int j = 1;j<=N;j++){
			scanf("%d",&V[i][j]);
		}
	}
	granderesposta = 1;
	for(int i = 1;i<=N;i++){
		for(int j = 1;j<=N;j++){
			if(i + 1 <= N && V[i][j] == V[i+1][j] && H[i][j] == H[i+1][j]){
				join(conversao[i][j],conversao[i+1][j]);
			}
			if(j + 1 <= N && V[i][j] == V[i][j+1] && H[i][j] == H[i][j+1]){
				join(conversao[i][j],conversao[i][j+1]);
			}	
		}
	}
	for(int i = 1;i<=N;i++) for(int j = 1;j<=N;j++){
		conversao[i][j] = find(conversao[i][j]);
		original[conversao[i][j]] = sz[conversao[i][j]];
	}
	for(int i = 1;i<=N;i++){
		for(int j = 1;j<=N;j++){
			if(i + 1 <= N && V[i][j] != V[i+1][j]){
				int v1 = -H[i][j] + H[i+1][j];
				int v2 = V[i][j] - V[i+1][j];
				if(v2 < 0){
					v2 *= -1;
					v1 *= -1;
				}
				sweep.push_back(make_tuple(v1,v2,conversao[i][j],conversao[i+1][j]));
			}
			if(j + 1 <= N && V[i][j] != V[i][j+1]){
				int v1 = -H[i][j] + H[i][j+1];
				int v2 = V[i][j] - V[i][j+1];
				if(v2 < 0){
					v2 *= -1;
					v1 *= -1;
				}
				sweep.push_back(make_tuple(v1,v2,conversao[i][j],conversao[i][j+1]));
			}	
		}
	}
	sort(sweep.begin(),sweep.end(),compara);
	for(int i = 0;i<sweep.size();i++){
		//printf("%d %d\n",get<0>(sweep[i]),get<1>(sweep[i]));
		if(i == 0 || !igual(sweep[i],sweep[i-1])) ultimot++;
		join(get<2>(sweep[i]),get<3>(sweep[i]));
	}
	printf("%d\n",granderesposta);
	return 0;
}deresposta);
	return 0;
}