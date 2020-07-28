// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc13s5
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
bitset<5000001> processado;
int main(){
	int n;
	scanf("%d",&n);
	priority_queue< ii, vector<ii>, greater<ii> > heap;
	heap.push(ii(0,n));
	while(!heap.empty()){
		ii davez = heap.top();
		heap.pop();
		int dist = davez.first;
		int v = davez.second;
		//printf("%d %d\n",dist,v);
		if(v == 1){
			printf("%d\n",dist);
			return 0;
		}
		if(processado.test(v)) continue;
		processado.set(v);
		for(int i = 1;(i-1)*(i-1)<=v;i++){
			if(v % i != 0) continue;
			int vemde1 = v - v/i;
			int custo1 = vemde1/(v/i);
			int vemde2 = v - i;
			int custo2 = vemde2/i;
			if(vemde1 >= 1 && !processado.test(vemde1)) heap.push(ii(dist + custo1,vemde1));
			if(vemde2 >= 1 && !processado.test(vemde2)) heap.push(ii(dist + custo2,vemde2));
		}
	}
	return 0;
}