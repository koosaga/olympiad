// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc14s5
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
const int MAXN = 2010;
typedef pair<short,short> ii;
typedef tuple<int,short,short> trinca;
struct node{
	int tamanho;
	vector<short> bit;
	void update(int idx,short val){
		while(idx <= tamanho){
			bit[idx] = max(bit[idx],val);
			idx += LSOne(idx);
		}
	}
	int query(int idx){
		short ans = 0;
		while(idx > 0){
			ans = max(ans,bit[idx]);
			idx -= LSOne(idx);
		}
		return ans;
	}
};
vector<trinca> ordenado;
vector<int> comp[MAXN];
ii pontos[MAXN];
node raiz[MAXN];
int modulo[MAXN],n;
inline int abs(ii davez){
	return int(davez.first)*int(davez.first) + int(davez.second)*int(davez.second);
}
inline int hypot(ii A,ii B){
	return abs(ii(A.first - B.first,A.second - B.second));
}
inline int get_v(int i,int val){
	return prev(upper_bound(comp[i].begin(),comp[i].end(),val)) - comp[i].begin() + 1;
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%hd %hd",&pontos[i].first,&pontos[i].second);
		modulo[i] = abs(pontos[i]);
		comp[i].push_back(0);
		comp[i].push_back(modulo[i]);
		for(int j = 1;j<i;j++){
			int dist = hypot(pontos[i],pontos[j]);
			ordenado.push_back(make_tuple(dist,i,j));
			comp[i].push_back(dist);
			comp[j].push_back(dist);
		}
	}
	sort(ordenado.begin(),ordenado.end());
	for(int i = 1;i<=n;i++){
		sort(comp[i].begin(),comp[i].end());
		comp[i].erase(unique(comp[i].begin(),comp[i].end()),comp[i].end());
		raiz[i].tamanho = (int)comp[i].size();
		raiz[i].bit.assign(raiz[i].tamanho+3,0);
		raiz[i].update(1,1);
	}
	for(int idx = 0;idx<ordenado.size();idx++){
		int dist = get<0>(ordenado[idx]),u = get<1>(ordenado[idx]),v = get<2>(ordenado[idx]);
		raiz[u].update(get_v(u,dist), raiz[v].query(get_v(v,dist-1)) + 1);
		raiz[v].update(get_v(v,dist), raiz[u].query(get_v(u,dist-1)) + 1);
	}
	int resp = raiz[1].query(get_v(1,modulo[1]-1));
	for(int i = 2;i<=n;i++) resp = max(resp, raiz[i].query(get_v(i,modulo[i]-1)));
	printf("%d\n",resp);
	return 0;
}0;
}