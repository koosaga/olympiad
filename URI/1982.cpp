// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1982
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
struct point{
	int x,y;
};
bool comp(point A, point B){
	if (A.x < B.x) return true;
	if (A.x > B.x) return false;
	return A.y < B.y;
}
int ccw(point A, point B, point C){
	int val = A.x*(B.y - C.y) - A.y*(B.x-C.x) + B.x*C.y - B.y*C.x;
	if (val == 0) return 0;
	if (val > 0) return 1;
	return -1;
}
double CH(vector<point> P){
	int n = P.size(), k = 0;
	vector<point> H(2*n);
	sort(P.begin(),P.end(),comp);
	for(int i=0;i<n;i++){
		while(k >= 2 && ccw(H[k-2],H[k-1],P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	for(int i=n-2,t=k+1;i>=0;i--){
		while(k >= t && ccw(H[k-2],H[k-1],P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	H.resize(k-1);
	H.resize(k-1);
	H.push_back(H[0]);
	double answer = 0;
	for(int i=0;i<H.size()-1;i++) answer += hypot(H[i].x - H[i+1].x,H[i].y - H[i+1].y);
	return answer;
}
int main(){
	int quantidade;
	while(scanf("%d",&quantidade) && quantidade){
		vector<point> entrada;
		for(int i=0;i<quantidade;i++){
			point temp;
			scanf("%d %d",&temp.x,&temp.y);
			entrada.push_back(temp);
		}
		printf("Tera que comprar uma fita de tamanho %.2lf.\n",CH(entrada));
	}
	return 0;
}
