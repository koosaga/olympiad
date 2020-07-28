// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c6p4
#include <bits/stdc++.h>
using namespace std;
deque<int> l,r,resp,p0,p1,p2;
int meio,n;
int main(){
	scanf("%d",&n);
	for(int i = 0;i<n;i++){
		int x;
		scanf("%d",&x);
		if(x % 3 == 0) p0.push_back(x);
		else if(x % 3 == 1) p1.push_back(x);
		else p2.push_back(x);
	}
	meio = -1;
	if(!p0.empty()){
		meio = p0.back();
		p0.pop_back();
	}
	if(!p1.empty()){
		l.push_front(p1.back());
		p1.pop_back();
	}
	if(!p2.empty()){
		r.push_back(p2.back());
		p2.pop_back();
	}
	while(!p0.empty()){
		if(!l.empty() && l.front() % 3 != 0){
			l.push_front(p0.back());
			p0.pop_back();
			if(!p1.empty()){
				l.push_front(p1.back());
				p1.pop_back();
			}
		}
		else if(!r.empty() && r.back() % 3 != 0){
			r.push_back(p0.back());
			p0.pop_back();
			if(!p2.empty()){
				r.push_back(p2.back());
				p2.pop_back();
			}
		}
		else{
			r.push_back(p0.back());
			p0.pop_back();
		}
	}
	while(!p1.empty()){
		l.push_front(p1.back());
		p1.pop_back();
	}
	while(!p2.empty()){
		r.push_back(p2.back());
		p2.pop_back();
	}
	for(int i : l) resp.push_back(i);
	if(meio != -1) resp.push_back(meio);
	for(int i : r) resp.push_back(i);
	for(int i = 0;i+1<resp.size();i++){
		if((resp[i] + resp[i+1]) % 3 == 0){
			printf("impossible\n");
			return 0;
		}
	}
	for(int i : resp) printf("%d ",i);
	printf("\n");
	return 0;
}}