// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc08s4
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
typedef set<int> si;
typedef si::iterator ite;
int possivel;
si uniao(si A,si B){
	si resp;
	for(ite it = A.begin();it != A.end();it++) resp.insert(*it);
	for(ite it = B.begin();it != B.end();it++) resp.insert(*it);
	return resp;
}
si mao2(int a,int b){
	//printf("Mao2 ini\n");
	si cjt;
	cjt.insert(a+b);
	cjt.insert(a-b);
	cjt.insert(b-a);
	cjt.insert(a*b);
	if(a != 0 && b % a == 0) cjt.insert(b/a);
	if(b != 0 && a % b == 0) cjt.insert(a/b);
	return cjt;
}
si mao3(int a,int b,int c){
	//printf("Mao3 ini\n");
	si resposta;
	si bc = mao2(b,c);
	si ab = mao2(a,b);
	si ac = mao2(a,c);
	for(ite it = bc.begin();it != bc.end();it++){
		resposta = uniao(resposta,mao2(a,*it));
	}
	for(ite it = ac.begin();it != ac.end();it++){
		resposta = uniao(resposta,mao2(b,*it));
	}
	for(ite it = ab.begin();it != ab.end();it++){
		resposta = uniao(resposta,mao2(c,*it));
	}
	return resposta;
}
si maodupla(si A,si B){
	//printf("Maod ini\n");
	si resposta;
	for(ite it1  = A.begin();it1 != A.end();it1++){
		for(ite it2  = B.begin();it2 != B.end();it2++){
			resposta = uniao(resposta, mao2(*it1,*it2) );
		}
	}
	return resposta;
}
si mao4(int a,int b,int c,int d){
	//printf("Mao4 ini\n");
	si resposta;
	si bc = mao2(b,c);
	si ab = mao2(a,b);
	si ac = mao2(a,c);
	si ad = mao2(a,d);
	si bd = mao2(b,d);
	si cd = mao2(c,d);
	resposta = uniao(resposta, maodupla(ab,cd) );
	resposta = uniao(resposta, maodupla(ac,bd) );
	resposta = uniao(resposta, maodupla(ad,bc) );
	si abc = mao3(a,b,c);
	si abd = mao3(a,b,d);
	si acd = mao3(a,c,d);
	si bcd = mao3(b,c,d);
	for(ite it = abc.begin();it != abc.end();it++){
		resposta = uniao(resposta,mao2(d,*it));
	}
	for(ite it = abd.begin();it != abd.end();it++){
		resposta = uniao(resposta,mao2(c,*it));
	}
	for(ite it = bcd.begin();it != bcd.end();it++){
		resposta = uniao(resposta,mao2(a,*it));
	}
	for(ite it = acd.begin();it != acd.end();it++){
		resposta = uniao(resposta,mao2(b,*it));
	}
	si retorna;
	for(ite it = resposta.begin();it != resposta.end();it++){
		int x = *it;
		if(x >= 25) continue;
		retorna.insert(x);
	}
	return retorna;
}
int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		int a,b,c,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		si ret = mao4(a,b,c,d);
		printf("%d\n",*(ret.rbegin()));
	}
	return 0;
}et.rbegin()));
	}
	return 0;
}