// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1552
#include <cstdio>
#include <cmath>
#include <queue>
#define MAXN 10100
#define MAXM 49995100
using namespace std;
int pai[MAXN],peso[MAXN],casos,n;
double coordx[MAXN],coordy[MAXN];
int find(int x){
    if (x==pai[x]) return x;
    return pai[x]=find(pai[x]);
}
void join(int x, int y){
    x = find(x);
    y = find(y);
    if (x==y) return;
    if (peso[x]<peso[y]) pai[x]=y;
    if (peso[x]>peso[y]) pai[y]=x;
    else{
        peso[y]++;
        pai[x]=y;
    }
}
int main(){
    scanf("%d",&casos);
    while(casos--){
        scanf("%d",&n);
        double resposta = 0;
        int contador=0;
        for(int i=1;i<=n;i++){
            pai[i]=i;
            peso[i]=0;
            scanf("%lf %lf",&coordx[i],&coordy[i]);
        }
        priority_queue<pair<double, pair<int,int> >, vector< pair<double, pair<int,int> > >, greater< pair<double, pair<int,int> > > > fila;
        for(int i=1;i<n;i++){
            for(int j=i+1;j<=n;j++){
                fila.push(make_pair(sqrt((coordx[i]-coordx[j])*(coordx[i]-coordx[j])+(coordy[i]-coordy[j])*(coordy[i]-coordy[j])),make_pair(i,j)));
            }
        }
        while(!fila.empty()){
            pair<double, pair<int,int> > davez = fila.top();
            fila.pop();
            if (find(davez.second.first)!=find(davez.second.second)){
                resposta += davez.first;
                join(davez.second.first,davez.second.second);
            }
        }
        printf("%.2lf\n",resposta/100.0);
    }
    return 0;
}
