// Ivan Carvalho
// Solution to https://www.spoj.com/problems/MPOLY/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 210;
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
int dp_lo[MAXN][MAXN],dp_hi[MAXN][MAXN],maior_lo[MAXN],maior_hi[MAXN],resp,N,vis_lo[MAXN][MAXN],vis_hi[MAXN][MAXN],TC;
vector<point> P;
int solve_lo(int p1,int p2){
	if(p1 == 0) return 2;
	if(vis_lo[p1][p2]) return dp_lo[p1][p2];
	vis_lo[p1][p2] = 1;
	int ret = -2*MAXN;
	for(int p3 = 0;p3<p1;p3++){
		if(ccw(P[p3],P[p1],P[p2]) > 0) ret = max(ret, 1+solve_lo(p3,p1));
	}
	return dp_lo[p1][p2] = ret;
}
int solve_hi(int p1,int p2){
	if(p1 == 0) return 2;
	if(vis_hi[p1][p2]) return dp_hi[p1][p2];
	vis_hi[p1][p2] = 1;
	int ret = -2*MAXN;
	for(int p3 = 0;p3<p1;p3++){
		if(ccw(P[p3],P[p1],P[p2]) < 0) ret = max(ret, 1+solve_hi(p3,p1));
	}
	return dp_hi[p1][p2] = ret;
}
int main(){
	scanf("%d",&N);
	P.clear();
	resp = 0;
	P.clear();
	point origem(0,0);
	P.push_back(origem);
	for(int i = 1;i<=N;i++){
		point davez;
		scanf("%d %d",&davez.x,&davez.y);
		P.push_back(davez);
	}
	sort(P.begin(),P.end(),compara);
	for(int p1 = 1;p1<=N;p1++){
		for(int p2 = 0;p2<p1;p2++){
			maior_lo[p1] = max(maior_lo[p1], solve_lo(p2,p1) );
			maior_hi[p1] = max(maior_hi[p1], solve_hi(p2,p1) );
		}
		resp = max(resp, maior_lo[p1] + maior_hi[p1] - 2 );
	}
	printf("%d\n",resp);
	return 0;
}