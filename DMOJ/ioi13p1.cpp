// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi13p1
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> ii;
typedef tuple<ll,ll,ll> trinca;

const int MAXN = 1e5 + 10;
const ll INF = 1e18;
const ll NEG = -INF;

vector<ii> grafo[MAXN];
vector<ll> centers;
int N,M,L,processado[MAXN];
ll whole_diameter,furthest_distance[MAXN];

int bfs_diameter(int X){

	queue<trinca> bfs;
	bfs.push(make_tuple(0,X,-1));

	ii ans = ii(NEG,NEG);

	while(!bfs.empty()){
		trinca davez = bfs.front();
		bfs.pop();
		ll dist = get<0>(davez);
		int v = get<1>(davez),p = get<2>(davez);
		processado[v]++;
		ans = max(ans, {dist,v} );
		furthest_distance[v] = max(furthest_distance[v],dist); 

		for(ii aresta : grafo[v]){
			int u = aresta.first, w = aresta.second;
			if(u == p) continue;
			bfs.push( make_tuple(dist + w,u,v) );
		}

	}

	//printf("X %d {%lld %lld}\n",X,ans.first,ans.second);
	whole_diameter = max(whole_diameter,ans.first);
	return ans.second;

}

ll bfs_radius(int X){

	queue<trinca> bfs;
	bfs.push(make_tuple(0,X,-1));

	ii ans = ii(INF,INF);

	while(!bfs.empty()){
		trinca davez = bfs.front();
		bfs.pop();
		ll dist = get<0>(davez);
		int v = get<1>(davez),p = get<2>(davez);
		ans = min(ans, {furthest_distance[v],v} );

		for(ii aresta : grafo[v]){
			int u = aresta.first, w = aresta.second;
			if(u == p) continue;
			bfs.push( make_tuple(dist +w,u,v) );
		}

	}

	//printf("Xr %d {%lld %lld}\n",X,ans.first,ans.second);

	return ans.first;

}

ll process_tree(int v){

	int x = bfs_diameter(v);
	int y = bfs_diameter(x);
	int z = bfs_diameter(y);

	ll ret = bfs_radius(z);
	//printf("V %d X %d Y %d Z %d RET %lld\n",v,x,y,z,ret);
	return ret;

}

int travelTime(int n, int m, int l, int A[], int B[], int T[]){

	N = n;
	M = m;
	L = l;

	for(int i = 0;i<M;i++){
		int u,v,w;
		u = A[i];
		v = B[i];
		w = T[i];
		grafo[u].push_back({v,w});
		grafo[v].push_back({u,w});
	}

	for(int i = 0;i<N;i++){
		if(processado[i]) continue;
		centers.push_back(process_tree(i));
	}

	sort(centers.rbegin(),centers.rend());
	if(centers.size() >= 2) whole_diameter = max(whole_diameter, 
centers[0] + centers[1] + L );
	if(centers.size() >= 3) whole_diameter = max(whole_diameter, 
centers[1] + centers[2] + 2*L );

	return (int)whole_diameter;

}

int main(){
	return 0;
}
