// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoqr16p3
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> ii;
vector<ii> entrada,intervalos;
int main(){
	int M,N;
	scanf("%d %d",&M,&N);
	for(int i=1;i<=N;i++){
		int r,c;
		scanf("%d %d",&r,&c);
		entrada.push_back(ii(c,M - r + 1));
	}
	sort(entrada.begin(),entrada.end());
	for(int i = 0;i<entrada.size();i++){
		int c = entrada[i].first,r = entrada[i].second;
		if(!intervalos.empty()){
			int nc = intervalos.back().first;
			int nr = intervalos.back().second;
			int atualr = nr - c + nc;
			if(atualr >= r){
				continue;
			} 
			intervalos.push_back(entrada[i]);
		}
		else{
			intervalos.push_back(entrada[i]);
		}
	}
	intervalos.push_back(ii(M+1,0));
	long long resp = 0;
	for(int i = 0;i + 1 < intervalos.size();i++){
		int inic = intervalos[i].first;
		int fimc = intervalos[i+1].first - 1;
		int inir = intervalos[i].second;
		int fimr = inir - (fimc - inic);
		if(fimr < 0){
			int delta = abs(fimr);
			fimc -= delta;
			fimr += delta;
		}
		resp += 1LL*(fimc - inic + 1)*(inir + fimr);
	}
	printf("%lld\n",resp/2LL);
	return 0;
}