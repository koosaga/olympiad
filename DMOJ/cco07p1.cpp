// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco07p1
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
struct point{
	int x,y;
};
bool compara(point A,point B){
	if(A.x < B.x) return true;
	if(A.x > B.x) return false;
	return A.y < B.y;
}
int ccw(point A,point B,point C){
	int val = A.x*(B.y - C.y) - A.y*(B.x - C.x) + B.x*C.y - B.y*C.x;
	if(val > 0) return 1;
	if(val == 0) return 0;
	return -1;
}
int main(){
	int resp = 0,n;
	scanf("%d",&n);
	vector<point> entrada,H(2*n);
	for(int i=0;i<n;i++){
		point davez;
		entrada.push_back(davez);
		scanf("%d %d",&entrada[i].x,&entrada[i].y);
	}
	sort(entrada.begin(),entrada.end(),compara);
	int k = 0;
	for(int i = 0;i<n;i++){
		while(k >= 2 && ccw(H[k-2],H[k-1],entrada[i]) <= 0) k--;
		H[k++] = entrada[i];
	}
	int t = k + 1;
	for(int i = n - 2;i >= 0;i--){
		while(k >= t && ccw(H[k-2],H[k-1],entrada[i]) <= 0) k--;
		H[k++] = entrada[i];
	}
	H.resize(k-1);
	H.push_back(H[0]);
	for(int i = 0;i + 1 < H.size();i++){
		resp += H[i].x*H[i+1].y - H[i].y*H[i+1].x;
	}
	printf("%d\n",resp/100);
	return 0;
}