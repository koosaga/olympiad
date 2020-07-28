// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADABRANC/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
typedef tuple<int,int,int> tripla;
typedef pair<int,int> ii;
vector<tripla> Kruskal;
vector<ii> pai[MAXN],tamanho[MAXN];
int peso[MAXN],n,m,q;
inline bool compara(ii A,ii B){
	return A.first < B.first;
}
inline int get_first_pai(int x,int kth){
	return (*lower_bound(pai[x].rbegin(),pai[x].rend(),ii(kth,0),compara)).second;
}
inline int get_first_tamanho(int x,int kth){
	return (*lower_bound(tamanho[x].rbegin(),tamanho[x].rend(),ii(kth,0),compara)).second;
}
int find(int x,int kth){
	int y = get_first_pai(x,kth);
	if(x == y) return x;
	return find(y,kth);
}
void join(int x,int y,int kth){
	x = find(x,kth);
	y = find(y,kth);
	if(peso[x] < peso[y]){
		pai[x].push_back(ii(kth,y));
		tamanho[y].push_back(ii(kth,get_first_tamanho(x,kth) + get_first_tamanho(y,kth)));
	}
	else if(peso[x] > peso[y]){
		//swap(x,y);
		pai[y].push_back(ii(kth,x));
		tamanho[x].push_back(ii(kth,get_first_tamanho(x,kth) + get_first_tamanho(y,kth)));
	}
	else{
		peso[y]++;
		pai[x].push_back(ii(kth,y));
		tamanho[y].push_back(ii(kth,get_first_tamanho(x,kth) + get_first_tamanho(y,kth)));
	}
}
int query(int x,int kth){
	return get_first_tamanho(find(x,kth),kth);
}
int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i = 0;i<n;i++){
		tamanho[i].push_back(ii(MAXN,1));
		pai[i].push_back(ii(MAXN,i));
	}
	for(int i = 0;i<m;i++){
		int u,v,peso;
		scanf("%d %d %d",&u,&v,&peso);
		Kruskal.push_back(make_tuple(peso,u,v));
	}
	sort(Kruskal.begin(),Kruskal.end());
	for(int i = m - 1;i>=0;i--){
		int u = get<1>(Kruskal[i]);
		int v = get<2>(Kruskal[i]);
		int peso = get<0>(Kruskal[i]);
		if(find(u,peso) != find(v,peso)){
			//printf("Liga %d %d %d\n",u,v,peso);
			join(u,v,peso);
		}
	}
	//for(int i = 0;i<n;i++){
		//printf("%d:",i);
		//for(int j = tamanho[i].size()-1;j>=0;j--){
		//	printf(" (%d,%d)",tamanho[i][j].first,tamanho[i][j].second);
		//}
		//printf("\n%d:",i);
		//for(int j = pai[i].size()-1;j>=0;j--){
		//	//printf(" (%d,%d)",pai[i][j].first,pai[i][j].second);
		//}
		//printf("\n");
	//}
	while(q--){
		int v,peso;
		scanf("%d %d",&v,&peso);
		printf("%d\n",query(v,peso));
	}
	return 0;
}