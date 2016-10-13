#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct tup{int x, y, z;};

int n, m;
int dist[255][255][2];
vector<int> gph[255];

queue<tup> que;

void enqueue(int x, int y, int z, int d){
	if(dist[x][y][z] > d){
		dist[x][y][z] = d;
		que.push({x, y, z});
	}
}


int main(){
	memset(dist, 0x3f, sizeof(dist));
	int p, q;
	cin >> n >> m >> p >> q;
	while(m--){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
	}
	que.push({p, q, 0});
	dist[p][q][0] = 0;
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		if(x.x == x.y && x.z == 0){
			printf("%d\n", dist[x.x][x.y][x.z] / 2);
			return 0;
		}
		if(x.z){
			for(auto &i : gph[x.y]){
				enqueue(x.x, i, 0, dist[x.x][x.y][x.z] + 1);
			}
		}
		else{
			for(auto &i : gph[x.x]){
				enqueue(i, x.y, 1, dist[x.x][x.y][x.z] + 1);
			}
		}
	}
	puts("NIE");
}

