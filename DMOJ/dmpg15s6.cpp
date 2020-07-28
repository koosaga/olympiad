// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg15s6
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#define MAXN 501
using namespace std;
map<string,int> conversao;
int de[MAXN*MAXN],para[MAXN*MAXN];
long double dist[MAXN],custo[MAXN*MAXN];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		string s;
		cin >> s;
		conversao[s] = i;
	}
	for(int i=1;i<=m;i++){
		string a,b;
		long double peso;
		cin >> a >> b >> peso;
		de[i] = conversao[a];
		para[i] = conversao[b];
		custo[i] = peso;
	}
	int id = conversao["APPLES"];
	dist[id] = 1.0;
	for(int vez=1;vez<=n;vez++){
		for(int i=1;i<=m;i++){
			int u = de[i];
			int v  = para[i];
			long double peso = custo[i];
			if(dist[v] < dist[u]*peso) dist[v] = dist[u]*peso;
		}
	}
	for(int i=1;i<=m;i++){
		int u = de[i];
		int v  = para[i];
		long double peso = custo[i];
		if(dist[v] < dist[u]*peso){
			cout << "YA" << '\n';
			return 0;
		}
	}
	cout << "NAW" << '\n';
	return 0;
}