// Ivan Carvalho
// Solution to https://www.spoj.com/problems/PERFUME/
#include <bits/stdc++.h>
#define X first
#define Y second
const double EPS = 1e-6;
using namespace std;
typedef pair<double,double> point;
int ccw(point A,point B,point C){
	double val =  A.X*(B.Y - C.Y) - A.Y*(B.X - C.X) + B.X*C.Y - B.Y*C.X ;
	if(val > 0) return 1;
	if(val == 0) return 0;
	return -1;
}
double area(point A,point B,point C){
	return abs(A.X*(B.Y - C.Y) - A.Y*(B.X - C.X) + B.X*C.Y - B.Y*C.X);
}
int main(){
	int T;
	scanf("%d",&T);
	for(int tc = 0;tc<T;tc++){
		if(tc) printf("\n");
		int N,Q;
		scanf("%d",&N);
		vector<point> C(2*N),E;
		for(int i = 0;i<N;i++){
			point davez;
			scanf("%lf %lf",&davez.X,&davez.Y);
			E.push_back(davez);
		}
		sort(E.begin(),E.end());
		int k = 0;
		for(int i = 0;i<N;i++){
			while(k >= 2 && ccw(C[k-2],C[k-1],E[i]) <= 0) k--;
			C[k++] = E[i];
		}
		for(int i = N - 2,t = k + 1;i>=0;i--){
			while(k >= t && ccw(C[k-2],C[k-1],E[i]) <= 0) k--;
			C[k++] = E[i];
		}
		C.resize(k-1);
		C.push_back(C[0]);
		double total = 0;
		for(int i = 0;i+1<C.size();i++) total += C[i].X*C[i+1].Y - C[i].Y*C[i+1].X;
		total = abs(total);
		vector<double> minx,miny;
		for(int i = 0;i<C.size();i++) minx.push_back(C[i].X),miny.push_back(C[i].Y);
		sort(minx.begin(),minx.end());sort(miny.begin(),miny.end());
		scanf("%d",&Q);
		while(Q--){
			double temp = 0;
			point davez;
			scanf("%lf %lf",&davez.X,&davez.Y);
			if(davez.X < minx[0] || davez.X > minx.back() || davez.Y < miny[0] || davez.Y > miny.back()){
				printf("No\n");
				continue;
			}
			for(int i = 0;i+1<C.size();i++) temp += area(davez,C[i],C[i+1]);
			if(fabs(temp - total) < EPS) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
} 