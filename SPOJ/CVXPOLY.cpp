// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CVXPOLY/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110;
const int MOD = 1234567;
struct point{
	int x,y;
	point(int _x,int _y) : x(_x),y(_y){}
	point() : x(0),y(0){}
};
bool compara(point A,point B){
	if(A.x == B.x) return A.y < B.y;
	return A.x < B.x;
}
int ccw(point A,point B,point C){
	int val = A.x*(B.y - C.y) - A.y*(B.x - C.x) + B.x*C.y - B.y*C.x;
	if(val > 0) return 1;
	if(val == 0) return 0;
	return -1; 
}
int dp_lo[MAXN][MAXN],dp_hi[MAXN][MAXN],qtd_lo[MAXN],qtd_hi[MAXN],resp,N,vis_lo[MAXN][MAXN],vis_hi[MAXN][MAXN],TC;
deque<point> P;
int solve_lo(int p1,int p2){
	if(p1 == 0) return 1;
	if(vis_lo[p1][p2]) return dp_lo[p1][p2];
	vis_lo[p1][p2] = 1;
	int ret = 0;
	for(int p3 = 0;p3<p1;p3++){
		if(ccw(P[p3],P[p1],P[p2]) > 0) ret = (ret + solve_lo(p3,p1)) % MOD;
	}
	return dp_lo[p1][p2] = ret;
}
int solve_hi(int p1,int p2){
	if(p1 == 0) return 1;
	if(vis_hi[p1][p2]) return dp_hi[p1][p2];
	vis_hi[p1][p2] = 1;
	int ret = 0;
	for(int p3 = 0;p3<p1;p3++){
		if(ccw(P[p3],P[p1],P[p2]) < 0) ret = (ret + solve_hi(p3,p1)) % MOD;
	}
	return dp_hi[p1][p2] = ret;
}
int main(){
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&N);
		P.clear();
		resp = 0;
		P.clear();
		for(int i = 1;i<=N;i++){
			point davez;
			scanf("%d %d",&davez.x,&davez.y);
			P.push_back(davez);
		}
		sort(P.begin(),P.end(),compara);
		while(!P.empty()){
			memset(vis_lo,0,sizeof(vis_lo));
			memset(vis_hi,0,sizeof(vis_hi));
			memset(dp_lo,0,sizeof(dp_lo));
			memset(dp_hi,0,sizeof(dp_hi));
			memset(qtd_lo,0,sizeof(qtd_lo));
			memset(qtd_hi,0,sizeof(qtd_hi));
			N = P.size() - 1;
			for(int p1 = 1;p1<=N;p1++){
			for(int p2 = 0;p2<p1;p2++){
				qtd_lo[p1] = (qtd_lo[p1] + solve_lo(p2,p1)) % MOD;
				qtd_hi[p1] = (qtd_hi[p1]+ solve_hi(p2,p1) ) % MOD;
			}
			resp += (qtd_lo[p1]*qtd_hi[p1]) - 1;
			resp %= MOD;
			}
			P.pop_front();
		}
		printf("%d\n",resp);
	}
	return 0;
} 