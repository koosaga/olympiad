// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SUBSET/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 20;
const int INF = 1e9 + 2;
const int SZ = (1 << 20) + 2;
bitset<INF> positivo,certeza,comcerteza;
bitset<SZ> possibilidades;
inline void add(int val){
	if(val < 0) val = -val;
	positivo.set(val,1);
}
inline void remove(int val){
	if(val < 0) val = -val;
	positivo.set(val,0);
}
inline int check(int val){
	if(val < 0) val = -val;
	return positivo.test(val); 
}
vector<int> v1,v2,todos,completo;
vector<ii> possiveis,provaveis;
int tam1,tam2,bandeira,nt,n,m,k,matching1,matching2;
void gera_duplas(int pos,int soma,int bitmask){
	if(pos == n){
		if(soma == 0) possibilidades.set(bitmask,1);
		possiveis.push_back(ii(abs(soma),bitmask));
		return;
	}
	gera_duplas(pos+1,soma + v1[pos],bitmask | (1 << pos));
	gera_duplas(pos+1,soma - v1[pos],bitmask | (1 << pos));
	gera_duplas(pos+1,soma,bitmask);
}
void gera_somas(int pos,int soma){
	if(pos == k){
		add(soma);
		if(certeza.test(abs(soma))) matching1 = 1;
		if(comcerteza.test(abs(soma))) matching2 = 1;
		return;
	}
	gera_somas(pos+1,soma + todos[pos]);
	gera_somas(pos+1,soma - todos[pos]);
}
void remove_somas(int pos,int soma){
	if(pos == k){
		remove(soma);
		return;
	}
	remove_somas(pos+1,soma + todos[pos]);
	remove_somas(pos+1,soma - todos[pos]);
}
 
void valida(int bitmask){
	matching1 = 0;
	matching2 = 0;
	if(bitmask == 0) return;
	todos.clear();
	for(int i = 0;i<m;i++){
		if(bitmask & (1 << i)) todos.push_back(v2[i]);
	}
	k = todos.size();
	gera_somas(0,0);
	if(matching1){
		for(int i = 0;i<possiveis.size();i++){
			int soma = possiveis[i].first, mascara = possiveis[i].second;
			if(check(soma)){
				int junta = (bitmask << n) | mascara;
				possibilidades.set(junta,1);
			}
		}	
	}
	if(matching2){
		for(int i = 0;i<provaveis.size();i++){
			int soma = provaveis[i].first, mascara = provaveis[i].second;
			if(check(soma)){
				int junta = (bitmask << n) | mascara;
				possibilidades.set(junta,1);
			}
		}	
	}
	remove_somas(0,0);
}
void subsets(int pos,int bitmask){
	if(pos == m){
		valida(bitmask);
		return;
	}
	subsets(pos+1, bitmask | (1 << pos) );
	subsets(pos+1,bitmask);
}
int main(){
	cin >> nt;
	for(int i = 0;i<nt;i++){
		int x;
		cin >> x;
		completo.push_back(x);
	}
	random_shuffle(completo.begin(),completo.end());
	while(!completo.empty()){
		if(!completo.empty()){
			v1.push_back(completo.back());
			completo.pop_back();
		}
		if(!completo.empty()){
			v2.push_back(completo.back());
			completo.pop_back();
		}
	}
	n = v1.size();
	m = v2.size();
	gera_duplas(0,0,0);
	sort(possiveis.begin(),possiveis.end());
	possiveis.erase(unique(possiveis.begin(),possiveis.end()),possiveis.end());
	random_shuffle(possiveis.begin(),possiveis.end());
	while(provaveis.size() <= possiveis.size()){
		provaveis.push_back(possiveis.back());
		possiveis.pop_back();
	}
	for(int i = 0;i<possiveis.size();i++){
		certeza.set(abs(possiveis[i].first),1);
	}
	for(int i = 0;i<provaveis.size();i++){
		comcerteza.set(abs(provaveis[i].first),1);
	}
	subsets(0,0);
	possibilidades.set(0,0);
	cout << possibilidades.count() << endl;
	return 0;
} 