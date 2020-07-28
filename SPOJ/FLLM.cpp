// Ivan Carvalho
// Solution to https://www.spoj.com/problems/FLLM/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD1 = 1e9 + 9;
const ll prime1 = 999983;
const ll MOD2 = 1e9 + 7;
const ll prime2 = 999979;
const ll invprime1 = 943912055;
const ll invprime2 = 672490127;
const ll MOD3 = 1e9 + 21;
const ll prime3 = 1e6 + 3;
const ll invprime3 = 801275613LL;
const int MAXN = 1002;
vector<int> resposta,conversao;
int N,vetor[MAXN][MAXN],tamanho[MAXN],inicio[MAXN],logaritmo2[MAXN];
ll hash1[MAXN][MAXN],pot1[MAXN],invpot1[MAXN],hash2[MAXN][MAXN],pot2[MAXN],invpot2[MAXN],hash3[MAXN][MAXN],pot3[MAXN],invpot3[MAXN];
inline int igualdade2(int p1,int ini1,int fim1,int p2,int ini2,int fim2){
    for(int i1 = ini1, i2 = ini2;i1 <= fim1;i1++,i2++){
        if(vetor[p1][i1] != vetor[p2][i2]) return 0;
    }
    return 1;
}
inline ll get_hash1(int idx,int a,int b){
    ll val = (hash1[idx][b] - hash1[idx][a-1])*invpot1[a-1];
    val %= MOD1;
    if(val < 0) val += MOD1;
    return val;
}
inline ll get_hash2(int idx,int a,int b){
    ll val = (hash2[idx][b] - hash2[idx][a-1])*invpot2[a-1];
    val %= MOD2;
    if(val < 0) val += MOD2;
    return val;
}
inline ll get_hash3(int idx,int a,int b){
    ll val = (hash3[idx][b] - hash3[idx][a-1])*invpot3[a-1];
    val %= MOD3;
    if(val < 0) val += MOD3;
    return val;
}
inline int igualdade(int p1,int ini1,int fim1,int p2,int ini2,int fim2){
    //int flag = igualdade2(p1,ini1,fim1,p2,ini2,fim2);
    if(get_hash1(p1,ini1,fim1) != get_hash1(p2,ini2,fim2)){
        //if(flag) printf("Falso negativo %d %d %d %d %d %d hash1\n",p1,ini1,fim1,p2,ini2,fim2);
        return 0;
    }
    //if(get_hash2(p1,ini1,fim1) != get_hash2(p2,ini2,fim2)){
        //if(flag) printf("Falso negativo %d %d %d %d %d %d hash2\n",p1,ini1,fim1,p2,ini2,fim2);
    //  return 0;
    //}
    //if(get_hash3(p1,ini1,fim1) != get_hash3(p2,ini2,fim2)){
        //if(flag) printf("Falso negativo %d %d %d %d %d %d hash3\n",p1,ini1,fim1,p2,ini2,fim2);
        //return 0;
    //}
    //if(!flag){
        //printf("Falso positivo %d %d %d %d %d %d\n",p1,ini1,fim1,p2,ini2,fim2);
        //printf("%lld %lld hash1\n",get_hash1(p1,ini1,fim1),get_hash1(p2,ini2,fim2));
        //printf("%lld %lld hash2\n",get_hash2(p1,ini1,fim1),get_hash2(p2,ini2,fim2));
        //printf("%lld %lld hash3\n",get_hash3(p1,ini1,fim1),get_hash3(p2,ini2,fim2));
    //}
    return 1;
}
bool comp(int p1,int p2){
    if(vetor[p1][inicio[p1]] != vetor[p2][inicio[p2]]) return vetor[p1][inicio[p1]] < vetor[p2][inicio[p2]];
    int tam1 = tamanho[p1] - inicio[p1] + 1;
    int tam2 = tamanho[p2] - inicio[p2] + 1;
    int tam = min(tam1,tam2);
    int atual = 0;
    for(int i = logaritmo2[tam];i>=0;i--){
        int novo = atual + (1 << i);
        if(novo <= tam && igualdade(p1,inicio[p1],inicio[p1]+novo-1,p2,inicio[p2],inicio[p2]+novo-1)){
            atual = novo;
        }
    }
    if(atual == tam) return tam1 > tam2;
    return vetor[p1][inicio[p1]+atual] < vetor[p2][inicio[p2]+atual];
}
inline bool heap_comp(int p1,int p2){
    return !comp(p1,p2);
}
int main(){
    cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
    cin >> N;
    pot1[0] = invpot1[0] = pot2[0] = invpot2[0] = pot3[0] = invpot3[0] = 1;
    for(int i = 1;i<MAXN;i++){
        pot1[i] = (pot1[i-1]*prime1) % MOD1;
        invpot1[i] = (invpot1[i-1]*invprime1) % MOD1;
        //pot2[i] = (pot2[i-1]*prime2) % MOD2;
        //invpot2[i] = (invpot2[i-1]*invprime2) % MOD2;
        //pot3[i] = (pot3[i-1]*prime3) % MOD3;
        //invpot3[i] = (invpot3[i-1]*invprime3) % MOD3;
        logaritmo2[i] = logaritmo2[i/2] + 1;
    }
    for(int i = 1;i<=N;i++){
        cin >> tamanho[i];
        inicio[i] = 1;
        for(int j = 1;j<=tamanho[i];j++){
            cin >> vetor[i][j];
            conversao.push_back(vetor[i][j]);
        }
    }
    sort(conversao.begin(),conversao.end());
    conversao.erase(unique(conversao.begin(),conversao.end()),conversao.end());
    for(int i = 1;i<=N;i++){
        for(int j = 1;j<=tamanho[i];j++){
            vetor[i][j] = lower_bound(conversao.begin(),conversao.end(),vetor[i][j]) - conversao.begin() + 1;
            hash1[i][j] = (hash1[i][j-1] + vetor[i][j]*pot1[j]) % MOD1;
            //hash2[i][j] = (hash2[i][j-1] + vetor[i][j]*pot2[j]) % MOD2;
            //hash3[i][j] = (hash3[i][j-1] + vetor[i][j]*pot3[j]) % MOD3;
        }
    }
    priority_queue<int, vector<int>, bool(*)(int,int) > pq(heap_comp);
    for(int i = 1;i<=N;i++) pq.push(i);
    while(!pq.empty()){
        int davez = pq.top();
        pq.pop();
        resposta.push_back(vetor[davez][inicio[davez]]);
        inicio[davez]++;
        if(inicio[davez] <= tamanho[davez]) pq.push(davez);
    }
    for(int i : resposta) cout << conversao[i-1] << " ";
    cout << endl;
    return 0;
}
