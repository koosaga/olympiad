// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAQUEUE/
#include <cstdio>
#include <deque>
using namespace std;
deque<int> fila;
int estado,q;
char entrada[200];
int main(){
	scanf("%d",&q);
	while(q--){
		int davez;
		scanf("%s",entrada);
		if(entrada[0] == 'b'){
			if(fila.empty()){
				printf("No job for Ada?\n");
			}
			else{
				if(estado == 0){
					printf("%d\n",fila.back());
					fila.pop_back();
				}
				else{
					printf("%d\n",fila.front());
					fila.pop_front();
				}
			}
		}
		else if(entrada[0] == 'f'){
			if(fila.empty()){
				printf("No job for Ada?\n");
			}
			else{
				if(estado == 1){
					printf("%d\n",fila.back());
					fila.pop_back();
				}
				else{
					printf("%d\n",fila.front());
					fila.pop_front();
				}
			}
		}
		else if(entrada[0] == 'r') estado = 1 - estado;
		else if(entrada[0] == 'p'){
			scanf("%d",&davez);
			if(estado == 0){
				fila.push_back(davez);
			}
			else{
				fila.push_front(davez);				
			}
		}
		else{
			scanf("%d",&davez);
			if(estado == 1){
				fila.push_back(davez);			
			}
			else{
				fila.push_front(davez);
			}
		}
	}
	return 0;
}