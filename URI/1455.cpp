// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1455
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const double EPS = 1e-5;
double X[2000],Y[2000],squared[2000],x_c,y_c,r;
struct point{
	double x,y;
};
int ccw(point A,point B, point C){
	double val = A.x*(B.y - C.y) - A.y*(B.x - C.x) + B.x*C.y - B.y*C.x;
	if(val >= EPS) return 1;
	if(fabs(val) < EPS) return 0;
	return -1;
}
bool comp(point A, point B){
	if(fabs(A.x - B.x) < EPS){
		return A.y + EPS <= B.y;
	}
	return A.x + EPS <= B.x;
}
vector<point> CH(vector<point> P){
	int n = P.size(), k = 0;
	sort(P.begin(),P.end(),comp);
	vector<point> H(2*n);
	for(int i=0;i<n;i++){
		while(k >= 2 && ccw(H[k-2],H[k-1],P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	for(int i = n-2, t = k+1;i>=0;i--){
		while(k >= t && ccw(H[k-2],H[k-1],P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	H.resize(k-1);
	return H;
}
void addCircle(int A,int B,int C, int n){
	double cof1 = X[A]*(Y[B] - Y[C]) - Y[A]*(X[B] - X[C]) + X[B]*Y[C] - Y[B]*X[C];
	double cof2 = squared[A]*(Y[B] - Y[C]) - Y[A]*(squared[B] - squared[C]) + squared[B]*Y[C] - Y[B]*squared[C];
	double cof3 = squared[A]*(X[B] - X[C]) - X[A]*(squared[B] - squared[C]) + squared[B]*X[C] - X[B]*squared[C];
	double cof4 = squared[A]*(X[B]*Y[C] - Y[B]*X[C]) - X[A]*(squared[B]*Y[C] - Y[B]*squared[C]) + Y[A]*(squared[B]*X[C] - X[B]*squared[C]);
	//printf("Cofs do addCircle(%d,%d,%d,%d)\n",A,B,C,n);
	cof2 *= -1;
	cof4 *= -1;
	for(int i=1;i<=n;i++){
		double val = cof1*squared[i] + cof2*X[i] + cof3*Y[i] + cof4;
		if(val >= EPS){
			return;
		}
	}
	double xdavez = -cof2/(2.0*cof1);
	double ydavez = -cof3/(2.0*cof1);
	double raiodavez = hypot(X[A] - xdavez, Y[A] - ydavez);
	if(raiodavez + EPS <= r){
		r =raiodavez;
		x_c = xdavez;
		y_c = ydavez;
	}
}
void addDiameter(int A,int B,int n){
	double xdavez = (X[A] + X[B])*0.5;
	double ydavez = (Y[A]+Y[B]) *0.5;
	double raiodavez = hypot(X[A] - X[B],Y[A] - Y[B]) * 0.5;
	for(int i=1;i<=n;i++){
		double val = hypot(X[i] - xdavez,Y[i] - ydavez);
		if(val >= raiodavez + EPS) return;
	}
	if(raiodavez + EPS <= r){
		r =raiodavez;
		x_c = xdavez;
		y_c = ydavez;
	}
}
int main(){
	int n,instancia = 1;
	while(scanf("%d",&n) && n){
		x_c = 1e9;
		y_c = 1e9;
		r = 1e9;
		vector<point> entrada;
		for(int i=1;i<=n;i++){
			point temp;
			scanf("%lf %lf",&temp.x,&temp.y);
			entrada.push_back(temp);
		}
		printf("Instancia %d\n",instancia++);
		if(n == 1){
			printf("%.2lf %.2lf %.2lf\n\n",entrada[0].x,entrada[0].y,0.0);
			continue;
		}
		vector<point> H = CH(entrada);
		n = H.size();
		for(int i=0;i<n;i++){
			X[i+1] = H[i].x;
			Y[i+1] = H[i].y;
			squared[i+1] = H[i].x*H[i].x + H[i].y*H[i].y;
		}
		if(n == 2){
			x_c = (X[1] + X[2]) * 0.5;
			y_c = (Y[1] + Y[2]) * 0.5;
			r = hypot(X[1] - X[2],Y[1] - Y[2]) * 0.5;
			printf("%.2lf %.2lf %.2lf\n\n",x_c,y_c,r);
			continue;
		}
		for(int i=1;i<=n-1;i++){
			for(int j=i+1;j<=n;j++){
				addDiameter(i,j,n);
			}
		}
		for(int i=1;i<=n-2;i++){
			for(int j=i+1;j<=n-1;j++){
				for(int k = j+1;k<=n;k++){
					addCircle(i,j,k,n);
				}
			}
		}
		printf("%.2lf %.2lf %.2lf\n\n",x_c,y_c,r);
	}
	return 0;
}
