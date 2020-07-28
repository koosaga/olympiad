// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1340
#include <cstdio>
#include <queue>
#include <stack>
using namespace std;
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		queue<int> fila;
		priority_queue<int> heap;
		stack<int> pilha;
		bool ispilha=true,isfila=true,isheap=true;
		while(n--){
			int op,valor;
			scanf("%d %d",&op,&valor);
			if (op==1){
				if (ispilha) pilha.push(valor);
				if (isfila) fila.push(valor);
				if (isheap) heap.push(valor);
			}
			else {
				if (ispilha){
					if (pilha.top()==valor) pilha.pop();
					else ispilha=false;
				}
				if (isfila){
					if (fila.front()==valor) fila.pop();
					else isfila=false;
				}
				if (isheap){
					if (heap.top()==valor) heap.pop();
					else isheap=false;
				}
			}
		}
		if (!(ispilha || isfila || isheap)) printf("impossible\n");
		else if ((isfila && ispilha)||(isfila && isheap)||(ispilha && isheap)) printf("not sure\n");
		else if (ispilha) printf("stack\n");
		else if (isfila) printf("queue\n");
		else if (isheap) printf("priority queue\n");
	}
	return 0;
}
