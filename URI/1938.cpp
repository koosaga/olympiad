// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1938
#include <cstdio>
#include <algorithm>
#include <vector>
#define X second
#define Y first
#define MP make_pair
using namespace std;
typedef pair<int,int> point;
const int NEG = -(1e8 + 1);
int n,resp;
vector<point> pontos;
bool comp(point A,point B){
	if(A.X == B.X) return A.Y < B.Y;
	return A.X < B.X;
}
int main(){
	while(scanf("%d",&n) != EOF){
		resp = 0;
		pontos.clear();
		for(int i=1;i<=n;i++){
			int x,y;
			scanf("%d %d",&x,&y);
			pontos.push_back(MP(y,x));
		}
		sort(pontos.begin(),pontos.end(),comp);
		for(int i=0;i<n;i++){
			point agora = pontos[i];
			int MIN = NEG;
			int MAX = -MIN;
			for(int j=i+1;j<n;j++){
				point proximo = pontos[j];
				if(proximo.Y > MIN && proximo.Y < MAX && proximo.Y != agora.Y){
					resp++;
				}
				if(proximo.Y > agora.Y){
					MAX = min(MAX,proximo.Y);
				}
				if(proximo.Y < agora.Y){
					MIN = max(proximo.Y,MIN);
				}
			}
		}
		printf("%d\n",resp);
	}
	return 0;
}
