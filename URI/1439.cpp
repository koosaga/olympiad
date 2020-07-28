// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1439
#include <cstdio>
#include <cstring>
int contador[10];
int mao[10][60];
int naipe[1000];
int pilha[300];
int tam, descartada;
int compra(int p){
    mao[p][pilha[tam++]]++;
    contador[p]++;
    return pilha[tam-1];
}
void descarta(int p, int cart){
    mao[p][cart]--;
    contador[p]--;
    descartada = cart;
}
int main(){
    naipe['C']=0;
    naipe['D']=1;
    naipe['H']=2;
    naipe['S']=3;
    int P, M, N;
    while (scanf("%d %d %d", &P, &M, &N) && P){
        memset(mao,0,sizeof(mao));
        for(int p = 0; p < P; p++){
            contador[p] = M;
            for(int m = 0; m < M; m++){
                int a;
                char b;
                scanf(" %d %c", &a, &b);
                mao[p][4*a + naipe[b]]++; 
            }
        }
        for(int i = 0; i < N - P*M; i++){
            int a;
            char b;
            scanf(" %d %c", &a, &b);       
            pilha[i] = 4*a + naipe[b]; 
        }
        int sentido = 1;
        int jogador = 0;
        descartada = pilha[0];
        tam = 1;
        if(descartada/4 == 12) sentido *= -1;
        else if(descartada/4 == 7){
            compra(0);
            compra(0);
            jogador=1;
        }
        else if(descartada/4 == 1){
            compra(0);
            jogador=1;
        }
        else if(descartada/4 == 11) jogador = 1;
        
        while (1){
            int achou = 0;
            for(int i = 55; i > 3; i--){
                if(mao[jogador][i] && (i/4 == descartada/4 || i%4 == descartada%4)){
                    achou=1;
                    descarta(jogador, i);
                    break;
                }
            }
            if(contador[jogador] == 0){
                printf("%d\n", jogador+1);
                break;
            }
            if(!achou){
                int cart = compra(jogador);
                if(cart/4 == descartada/4 || cart%4 == descartada%4){
                    descarta(jogador,cart);
                    achou = 1;
                }
            }   
            if(achou){  
                int proximo = (jogador + sentido + P) % P;
                if(descartada/4 == 12) sentido *= -1;
                else if(descartada/4 == 7){
                    compra(proximo);
                    compra(proximo);
                    jogador=proximo;
                }
                else if(descartada/4 == 1){
                    compra(proximo);
                    jogador=proximo;
                }
                else if(descartada/4 == 11) jogador = proximo;
            }   
            jogador = (jogador + sentido + P) % P;
        }
    }
    return 0;
} 
