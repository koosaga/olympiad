// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi13p5
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

const int MAXN = 1e5 + 10;

vector<int> weak,small;
vector<ii> robots;
int A,B,N;

int checa(int X){
	priority_queue<int> pq;
	int ptr = 0;
	for(int w : weak){
		while(ptr < N && robots[ptr].first < w){
			pq.push(robots[ptr].second);
			ptr++;
		}
		for(int i = 1;i<=X && !pq.empty();i++){
			pq.pop();
		}
	}
	while(ptr < N){
		pq.push(robots[ptr].second);
		ptr++;
	}
	for(int s : small){
		for(int i = 1;i <= X && !pq.empty();i++){
			if(!pq.empty() && pq.top() >= s) return 0;
			pq.pop();
		}
	}
	return pq.empty();
}

int putaway(int a, int b, int n, int X[], int Y[], int W[], int S[]){

	A = a;B = b;N = n;
	for(int i = 0;i<A;i++){
		int x = X[i];
		weak.push_back(x);
	}
	for(int i = 0;i<B;i++){
		int x = Y[i];
		small.push_back(x);
	}
	for(int i = 0;i<N;i++){
		int x = W[i],y = S[i];
		robots.push_back({x,y});
	}

	sort(robots.begin(),robots.end());
	sort(weak.begin(),weak.end());
	sort(small.rbegin(),small.rend());

	int ini = 1,fim = N,meio,resposta = -1;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if(checa(meio)){
			resposta = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}

	return resposta;
}

int main(){
	return 0;
}
