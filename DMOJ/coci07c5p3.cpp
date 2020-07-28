// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c5p3
#include <cstdio>
#include <cstdlib>
int area(int x1,int y1,int x2,int y2,int x3,int y3){
	int val = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
	return abs(val);
}
int main(){
	int xa,xb,xc,ya,yb,yc;
	scanf("%d %d %d %d %d %d",&xa,&ya,&xb,&yb,&xc,&yc);
	int dobro = area(xa,ya,xb,yb,xc,yc);
	printf("%.1lf\n",double(dobro)*0.5);
	int n,resp = 0;
	scanf("%d",&n);
	while(n--){
		int x,y;
		scanf("%d %d",&x,&y);
		int val = area(x,y,xb,yb,xc,yc) + area(xa,ya,x,y,xc,yc) + area(xa,ya,xb,yb,x,y);
		if(val == dobro) resp++;
	}
	printf("%d\n",resp);
	return 0;
}