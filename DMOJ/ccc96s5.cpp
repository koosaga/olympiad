// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc96s5
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int,int> ii;
vector<ii> X,Y; 
set<int> ordenado;
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		ordenado.clear();
		X.clear();
		Y.clear();
		int n,resp = 0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int d;
			scanf("%d",&d);
			X.push_back(ii(d,i));
		}
		for(int i=1;i<=n;i++){
			int d;
			scanf("%d",&d);
			Y.push_back(ii(d,i));
		}
		sort(X.begin(),X.end());
		sort(Y.begin(),Y.end());
		int ptr = 0;
		for(int i = 0;i < n;i++){
			int val = Y[i].first,pos = Y[i].second;
			while(ptr < X.size() && X[ptr].first <= val){
				ordenado.insert(X[ptr].second);
				ptr++;
			}
			if(ordenado.empty()) continue;
			int menor = *(ordenado.begin());
			if(menor > pos) continue;
			resp = max(resp, pos - menor );
		}
		printf("The maximum distance is %d\n",resp);
	}
	return 0;
}