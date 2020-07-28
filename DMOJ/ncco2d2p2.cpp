// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ncco2d2p2
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,ii> quadra;
typedef tuple<int,int,ll> tripla;
typedef pair<tripla,quadra> quinta;
vector<ii> pontos;
vector<quadra> temporario;
vector<tripla> conversao;
vector<quinta> truque;
double resp;
int n;
inline ll sq(int p){
	return 1LL*p*p;
}
void solve(ii A,ii B,ii C,ii D){
	if(A == B || A == C || A == D || B == C || B == D || C == D) return;
	vector<ll> cords;
	cords.push_back(sq(A.F - B.F) + sq(A.S - B.S));
	cords.push_back(sq(C.F - B.F) + sq(C.S - B.S));
	cords.push_back(sq(D.F - B.F) + sq(D.S - B.S));
	cords.push_back(sq(A.F - C.F) + sq(A.S - C.S));
	cords.push_back(sq(A.F - D.F) + sq(A.S - D.S));
	cords.push_back(sq(C.F - D.F) + sq(C.S - D.S));
	sort(cords.begin(),cords.end());
	if(cords[0] != cords[1] || cords[2] != cords[3] || cords[4] != cords[5]) return;
	if(cords[0] + cords[2] != cords[4]) return;
	resp = max(resp, sqrt(cords[0])*sqrt(cords[2]) );
	cords.clear();
}
void calculate(){
	for(int i  =0;i<temporario.size();i++){
		for(int j = i + 1;j < temporario.size();j++){
			solve(temporario[i].F,temporario[i].S,temporario[j].F,temporario[j].S);
		}
	}
	temporario.clear();
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		pontos.push_back(ii(x,y));
	}
	truque.reserve(1376*1376);
	for(int i = 0;i<n;i++){
		for(int j = i+1;j<n;j++){
			tripla davez = make_tuple(pontos[i].F + pontos[j].F,pontos[i].S + pontos[j].S, sq(pontos[i].F - pontos[j].F) + sq(pontos[i].S - pontos[j].S) );
			truque.push_back(make_pair(davez,make_pair(pontos[i],pontos[j])));
		}
	}
	sort(truque.begin(),truque.end());
	for(int i= 0;i < truque.size();i++){
		temporario.push_back(truque[i].S);
		if(i - 1 == truque.size() || truque[i].first != truque[i+1].first){
			calculate();
		}
	}
	printf("%.0lf\n",resp);
	return 0;
}
