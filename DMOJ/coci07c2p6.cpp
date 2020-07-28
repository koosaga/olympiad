// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c2p6
#include <cstdio>
#include <map>
using namespace std;
int X[1501],Y[1501];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d %d",&X[i],&Y[i]);
	int resp = 0;
	for(int i=1;i<=n;i++){
		int specialx = 0, specialy = 0;
		map<double,int> qtd;
		for(int j=1;j<=n;j++){
			if(i == j) continue;
			if(X[i] == X[j]){
				specialx++;
				resp += specialy;
				continue;
			}
			if(Y[i] == Y[j]){
				specialy++;
				resp += specialx;
				continue;
			}
			double dy = Y[i] - Y[j];
			double dx = X[i] - X[j];
			double cof = dy/dx;
			double inv = -dx/dy;
			if(qtd.count(inv)) resp += qtd[inv];
			qtd[cof]++;
		}
	}
	printf("%d\n",resp);
	return 0;
}