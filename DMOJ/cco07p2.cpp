// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco07p2
#include <cstdio>
#include <deque>
#include <set>
#include <algorithm>
#define MP make_pair
using namespace std;
typedef pair<int,int> i2;
typedef pair<int,i2> i3;
typedef pair<int,i3> i4;
typedef pair<int,i4> i5;
typedef pair<int,i5> i6;
int main(){
	int n;
	set< i6 > conjunto;
	scanf("%d",&n);
	while(n--){
		deque<int> entrada(6),minimo;
		for(int i=0;i<6;i++) scanf("%d",&entrada[i]);
		minimo = entrada;
		for(int i=0;i<6;i++){
			entrada.push_back(entrada.front());
			entrada.pop_front();
			if(entrada < minimo) minimo = entrada;
		}
		reverse(entrada.begin(),entrada.end());
		for(int i=0;i<6;i++){
			entrada.push_back(entrada.front());
			entrada.pop_front();
			if(entrada < minimo) minimo = entrada;
		}
		i6 davez = MP(minimo[0],MP(minimo[1],MP(minimo[2],MP(minimo[3],MP(minimo[4],minimo[5])))));
		if(conjunto.count(davez)){
			printf("Twin snowflakes found.\n");
			return 0;
		}
		conjunto.insert(davez);
	}
	printf("No two snowflakes are alike.\n");
	return 0;
}