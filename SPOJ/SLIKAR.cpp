// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SLIKAR/
#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int,int> quadra;
const int MAXN = 514;
const int MAXL = 11;
char entrada[MAXN];
int soma_preto[MAXN][MAXN],soma_branco[MAXN][MAXN],exibe[MAXN][MAXN],dp[MAXN][MAXN][MAXL],n;
int calcula_branco(int x1,int y1,int x2,int y2){
    return soma_branco[x2][y2] - soma_branco[x1-1][y2] - soma_branco[x2][y1-1] + soma_branco[x1-1][y1-1];
}
int calcula_preto(int x1,int y1,int x2,int y2){
    return soma_preto[x2][y2] - soma_preto[x1-1][y2] - soma_preto[x2][y1-1] + soma_preto[x1-1][y1-1];
}
int solve(int x,int y,int level){
    int comprimento = (1 << level)/2;
    if(dp[x][y][level] != -1) return dp[x][y][level];
    if(level == 0){
        return dp[x][y][level] = 1;
    }
    vector<quadra> tudo;
    tudo.push_back(make_tuple(x,y,x + comprimento - 1,y + comprimento - 1));
    tudo.push_back(make_tuple(x+comprimento,y,x+2*comprimento-1,y+comprimento-1));
    tudo.push_back(make_tuple(x,y+comprimento,x + comprimento -1,y + 2*comprimento- 1));
    tudo.push_back(make_tuple(x+comprimento,y+comprimento,x + 2*comprimento - 1,y + 2*comprimento - 1));
    sort(tudo.begin(),tudo.end());
    int resposta = 0;
    do{
        resposta = max(resposta, calcula_branco(get<0>(tudo[0]),get<1>(tudo[0]),get<2>(tudo[0]),get<3>(tudo[0])) + calcula_preto(get<0>(tudo[1]),get<1>(tudo[1]),get<2>(tudo[1]),get<3>(tudo[1]))  + solve(get<0>(tudo[2]),get<1>(tudo[2]),level-1) + solve(get<0>(tudo[3]),get<1>(tudo[3]),level-1)   );
    }while(next_permutation(tudo.begin(),tudo.end()));
    return dp[x][y][level] = resposta;
}
void pinta_preto(int x1,int y1,int x2,int y2){
    for(int i = x1;i<=x2;i++){
        for(int j = y1;j<=y2;j++){
            exibe[i][j] = 1;
        }
    }
}
void pinta(int x,int y,int level){
    int comprimento = (1 << level)/2;
    if(level == 0){
        exibe[x][y] = calcula_preto(x,y,x,y);
        return;
    }
    vector<quadra> tudo;
    tudo.push_back(make_tuple(x,y,x + comprimento - 1,y + comprimento - 1));
    tudo.push_back(make_tuple(x+comprimento,y,x+2*comprimento-1,y+comprimento-1));
    tudo.push_back(make_tuple(x,y+comprimento,x + comprimento -1,y + 2*comprimento- 1));
    tudo.push_back(make_tuple(x+comprimento,y+comprimento,x + 2*comprimento - 1,y + 2*comprimento - 1));
    sort(tudo.begin(),tudo.end());
    int resposta = 0;
    do{
        int temp = calcula_branco(get<0>(tudo[0]),get<1>(tudo[0]),get<2>(tudo[0]),get<3>(tudo[0])) + calcula_preto(get<0>(tudo[1]),get<1>(tudo[1]),get<2>(tudo[1]),get<3>(tudo[1]))  + solve(get<0>(tudo[2]),get<1>(tudo[2]),level-1) + solve(get<0>(tudo[3]),get<1>(tudo[3]),level-1);
        if(temp == dp[x][y][level]){
            pinta_preto(get<0>(tudo[1]),get<1>(tudo[1]),get<2>(tudo[1]),get<3>(tudo[1]));
            pinta(get<0>(tudo[2]),get<1>(tudo[2]),level-1);
            pinta(get<0>(tudo[3]),get<1>(tudo[3]),level-1);
            return;
        }
    }while(next_permutation(tudo.begin(),tudo.end()));
}
int main(){
    scanf("%d",&n);
    int pot2 = 0;
    while((1 << pot2) != n){
        pot2++;
    }
    for(int i = 1;i<=n;i++){
        scanf("%s",entrada);
        for(int j = 1;j<=n;j++){
            soma_preto[i][j] = (entrada[j-1] - '0');
            soma_branco[i][j] = (1 ^ soma_preto[i][j]) + soma_branco[i][j-1] + soma_branco[i-1][j] - soma_branco[i-1][j-1];
            soma_preto[i][j] = soma_preto[i][j] + soma_preto[i][j-1] + soma_preto[i-1][j] - soma_preto[i-1][j-1];
        }
    }
    memset(dp,-1,sizeof(dp));
    printf("%d\n",n*n - solve(1,1,pot2));
    pinta(1,1,pot2);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            printf("%d",exibe[i][j]);
        }
        printf("\n");
    }
    return 0;
}