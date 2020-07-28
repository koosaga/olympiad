// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc00s5
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
int processado[110];
double X[110],Y[110],melhor[110];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf %lf",&X[i],&Y[i]);
	}
	for(double cordx = 0.00;cordx <= 1000.0;cordx+= 0.01){
		double best = 1e9;
		vector<int> escolhidas;
		for(int i=1;i<=n;i++){
			double dist = Y[i]*Y[i] + (X[i] - cordx)*(X[i] - cordx);
			if(dist < best){
				escolhidas.clear();
				best = dist;
				escolhidas.push_back(i);
			}
			else if(dist == best){
				escolhidas.push_back(i);
			}
		}
		for(int i : escolhidas) processado[i] = 1;
	}
	for(int i=1;i<=n;i++){
		if(processado[i]) printf("The sheep at (%.2lf, %.2lf) might be eaten.\n",X[i],Y[i]);
	}
	return 0;
}