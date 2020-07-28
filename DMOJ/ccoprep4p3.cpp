// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoprep4p3
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<ll,ll,ll,ll,ll> edge;
typedef pair<ll,ll> ii;
const ll MAXN = 20010;
const ll MAXM = 50110;
const ll BUCKET = 225;
vector<edge> arestas,especial;
vector<ll> possivel,certeza;
vector<ii> periodos[MAXM];
ll pai[MAXN],peso[MAXN],lazypai[MAXN],lazypeso[MAXN],ultima[MAXN],n,m,q,e1[MAXM],e2[MAXM],custo,iteracao;
void zerar(){for(ll i = 1;i<=n;i++) pai[i] = i, peso[i] = 1;}
ll find(ll x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void lazybuild(){
	for(ll i = 1;i<=n;i++){
		lazypai[i] = pai[i];
		lazypeso[i] = peso[i];
		ultima[i] = iteracao;
	}
}
void join(ll x,ll y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(peso[x] < peso[y]) swap(x,y);
	pai[y] = x;
	peso[x] += peso[y];
}
ll lazyfind(ll x){
	if(ultima[x] != iteracao){
		lazypai[x] = pai[x];
		lazypeso[x] = peso[x];
		ultima[x] = iteracao;
	}
	if(x == lazypai[x]) return x;
	return lazypai[x] = lazyfind(lazypai[x]);
}
void lazyjoin(ll x,ll y){
	x = lazyfind(x);
	y = lazyfind(y);
	if(lazypeso[x] < lazypeso[y]) swap(x,y);
	lazypai[y] = x;
	lazypeso[x] += lazypeso[y];
}
int main(){
	scanf("%lld %lld %lld",&n,&m,&q);
	for(ll i = 1;i<=m;i++){
		scanf("%lld %lld",&e1[i],&e2[i]);
		ll w;
		scanf("%lld",&w);
		periodos[i].push_back(ii(w,-1));
	}
	for(ll i = 0;i<q;i++){
		ll k,w;
		scanf("%lld %lld",&k,&w);
		periodos[k].push_back(ii(w,i));
	}
	for(ll i = 1;i<=m;i++) periodos[i].push_back(ii(MAXM,MAXM));
	ll tot_baldes = (q-1)/BUCKET;
	for(ll i = 1;i<=m;i++){
		for(ll j = 0;j+1<periodos[i].size();j++){
			arestas.push_back(make_tuple(periodos[i][j].first,e1[i],e2[i],periodos[i][j].second,periodos[i][j+1].second -1  ));
			possivel.push_back(0);
			certeza.push_back(0);
		}
	}
	sort(arestas.begin(),arestas.end());
	for(ll balde_davez = 0;balde_davez<=tot_baldes;balde_davez++){
		zerar();
		especial.clear();
		custo = 0;
		ll lo = balde_davez*BUCKET;
		ll hi  = min((balde_davez+1)*BUCKET - 1,q-1);
		for(ll i = 0;i<arestas.size();i++) possivel[i] = 0, certeza[i] = 0;
		for(ll i = 0;i<arestas.size();i++){
			ll u = get<1>(arestas[i]),v = get<2>(arestas[i]),w = get<0>(arestas[i]), t1 = get<3>(arestas[i]),t2 = get<4>(arestas[i]);
			if(t1 > hi || t2 < lo) continue;
			if((lo <= t1 && t1 <= hi) || (lo <= t2 + 1 && t2 + 1 <= hi)){
				continue;
			}
			if(find(u) != find(v)){
				join(u,v);
				possivel[i] = 1;
			}
		}
		zerar();
		for(ll i = 0;i<arestas.size();i++){
			ll u = get<1>(arestas[i]),v = get<2>(arestas[i]),w = get<0>(arestas[i]), t1 = get<3>(arestas[i]),t2 = get<4>(arestas[i]);
			if(t1 > hi || t2 < lo) continue;
			if((lo <= t1 && t1 <= hi) || (lo <= t2 + 1 && t2 + 1 <= hi)){
				join(u,v);
			}
		}
		for(ll i = 0;i<arestas.size();i++){
			ll u = get<1>(arestas[i]),v = get<2>(arestas[i]),w = get<0>(arestas[i]), t1 = get<3>(arestas[i]),t2 = get<4>(arestas[i]);
			if(t1 > hi || t2 < lo) continue;
			if((lo <= t1 && t1 <= hi) || (lo <= t2 + 1 && t2 + 1 <= hi)){
				especial.push_back(arestas[i]);
				continue;
			}
			if(!possivel[i]) continue;
			if(find(u) != find(v)){
				certeza[i] = 1;
				join(u,v);
			}
			else{
				especial.push_back(arestas[i]);
			}
		}
		zerar();
		for(ll i = 0;i<arestas.size();i++){
			ll u = get<1>(arestas[i]),v = get<2>(arestas[i]),w = get<0>(arestas[i]), t1 = get<3>(arestas[i]),t2 = get<4>(arestas[i]);
			if(t1 > hi || t2 < lo) continue;
			if((lo <= t1 && t1 <= hi) || (lo <= t2 + 1 && t2 + 1 <= hi)){
				continue;
			}
			if(certeza[i]){
				join(u,v);
				custo += w;
			}
		}
		lazybuild();
		for(ll tempo = lo;tempo<=hi;tempo++){
			ll delta = 0;
			++iteracao;
			for(ll i = 0;i<especial.size();i++){
				ll u = get<1>(especial[i]),v = get<2>(especial[i]),w = get<0>(especial[i]), t1 = get<3>(especial[i]),t2 = get<4>(especial[i]);
				if(t1 > tempo || t2 < tempo) continue;
				if(lazyfind(u) != lazyfind(v)){
					lazyjoin(u,v);
					delta += w;
				}
			}
			printf("%lld\n",custo + delta);
		}
	}
	return 0;
};
				}
			}
			printf("%lld\n",custo + delta);
		}
	}
	return 0;
}