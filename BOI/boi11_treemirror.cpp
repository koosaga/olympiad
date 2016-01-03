#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
vector<int> graph[100005];

int root1, root2;
int dist1[100005], dist2[100005], par[100005];
queue<int> q;

void bfs(int* dist, int s){
	q.push(s);
	dist[s] = 0;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(auto &i : graph[x]){
			if(dist[i] > dist[x] + 1){
				dist[i] = dist[x] + 1;
				par[i] = x;
				q.push(i);
			}
		}
	}
}

bool get_root(){
	vector<int> degone;
	for(int i=1; i<=n; i++){
		if(graph[i].size() == 1){
			degone.push_back(i);
		}
	}
	if(degone.size() == 1 || degone.size() > 2){
		return 0;
	}
	if(degone.size() == 2){
		root1 = degone[0];
		root2 = degone[1];
		return 1;
	}
	int nonleaf = -1;
	for(int i=1; i<=n; i++){
		if(graph[i].size() > 2){
			nonleaf = i;
			break;
		}
	}
	memset(dist1, 0x3f, sizeof(dist1));
	int v1 = graph[nonleaf][0];
	int v2 = graph[nonleaf][1];
	graph[nonleaf].erase(find(graph[nonleaf].begin(), graph[nonleaf].end(), v1));
	graph[nonleaf].erase(find(graph[nonleaf].begin(), graph[nonleaf].end(), v2));
	graph[v1].erase(find(graph[v1].begin(), graph[v1].end(), nonleaf));
	graph[v2].erase(find(graph[v2].begin(), graph[v2].end(), nonleaf));
	bfs(dist1, nonleaf);
	int bv1 = v1, bv2 = v2;
	vector<int> trace1, trace2;
	while(v1 != nonleaf){
		trace1.push_back(v1);
		v1 = par[v1];
	}
	while(v2 != nonleaf){
		trace2.push_back(v2);
		v2 = par[v2];
	}
	reverse(trace1.begin(), trace1.end());
	reverse(trace2.begin(), trace2.end());
	graph[nonleaf].push_back(bv1);
	graph[nonleaf].push_back(bv2);
	graph[bv1].push_back(nonleaf);
	graph[bv2].push_back(nonleaf);
	int same = 10000000;
	for(int i=0; i<trace1.size() && i<trace2.size(); i++){
		if(trace1[i] == trace2[i]) same = i;
	}
	if(same%2 != 1) return 0;
	same = trace1[(same - 1) / 2];
	if(graph[same].size() != 2) return 0;
	root1 = graph[same][0];
	root2 = graph[same][1];
	return 1;
}

vector<int> tree1[100005], tree2[100005];

bool generate_tree(int x, int y){
	memset(dist1, 0x3f, sizeof(dist1));
	memset(dist2, 0x3f, sizeof(dist2));
	bfs(dist1, x);
	bfs(dist2, y);
	int v1 = 0, v2 = 0, e1 = 0, e2 = 0;
	for(int i=1; i<=n; i++){
		for(auto &j : graph[i]){
			if(i > j) continue;
			int cd1 = dist1[i] + dist1[j];
			int cd2 = dist2[i] + dist2[j];
			if(cd1 == cd2){
				return 0;
			}
			if(cd1 < cd2){
				tree1[i].push_back(j);
				tree1[j].push_back(i);
				e1++;
			}
			if(cd1 > cd2){
				tree2[i].push_back(j);
				tree2[j].push_back(i);
				e2++;
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(tree1[i].size()) v1++;
		if(tree2[i].size()) v2++;
	}
	if(v1 - 1 != e1 || v2 - 1 != e2) return 0;
	return 1;
}

const int CODE = 409;
const int CODE2 = 433;

int dfs3(int x, int p){
	vector<int> v;
	for(auto &i : tree1[x]){
		if(i == p) continue;
		v.push_back((CODE * dfs3(i, x)) ^ CODE);
	}
	if(v.size() == 0) return x;
	sort(v.begin(), v.end());
	int ret = 0, coeff = 1;
	for(int i=0; i<v.size(); i++){
		ret += (coeff * v[i]);
		coeff *= CODE2;
	}
	return ret;
}

int dfs4(int x, int p){
	vector<int> v;
	for(auto &i : tree2[x]){
		if(i == p) continue;
		v.push_back((CODE * dfs4(i, x)) ^ CODE);
	}
	if(v.size() == 0) return x;
	sort(v.begin(), v.end());
	int ret = 0, coeff = 1;
	for(int i=0; i<v.size(); i++){
		ret += (coeff * v[i]);
		coeff *= CODE2;
	}
	return ret;
}
 
bool isomorphic(int x, int y){
	return dfs3(x, -1) == dfs4(y, -1);
}
 
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	if(n == m){
		int bad = 0;
		for(int i=1; i<=n; i++){
			if(graph[i].size() != 2){
				bad = 1;
				break;
			}
		}
		if(!bad){
			puts(n%2 ? "NO" : "YES");
			return 0;
		}
	}
	if(!get_root()){
		puts("NO");
		return 0;
	}
	if(!generate_tree(root1, root2)){
		puts("NO");
		return 0;
	}
	puts(isomorphic(root1, root2) ? "YES" : "NO");
}