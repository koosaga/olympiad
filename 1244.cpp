// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1244
#include <cstdio>
#include <cstring>
#include <cstdlib>
struct palavra{
       int len;
       int pos;
       char *p;
};
int compara(const void * a, const void * b){
    struct palavra *pa = (struct palavra *)a; 
    struct palavra *pb = (struct palavra *)b;
    if(pb->len == pa->len) return pa->pos - pb->pos;
    return pb->len - pa->len;
}
int main(){
    int n, i, cont, j, k;
    char linha[2600];
    char *pch;
    scanf("%d",&n);
    getchar();
    for(i = 0; i < n; i++){
          gets(linha);
          cont = 0;
          struct palavra texto[51];
          pch = strtok (linha," ");
          while (pch != NULL){
                texto[cont].p = pch;
                texto[cont].len = strlen(pch);
                texto[cont].pos = cont; 
                cont++;
                pch = strtok (NULL, " ");
          }
          qsort(texto, cont, sizeof(palavra), compara);
          for(j = 0; j < cont; j++){
                if(j == cont-1) printf("%s\n", texto[j].p);
                else printf("%s ", texto[j].p);
          }
    }   
    return 0;
}
