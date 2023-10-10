#include <cstdio>
#include <cstring>
 
char str[8]="IVXLCDM";
int res[8] ={1,5,10,50,100,500,1000};
 
int fnd(char t){
    for (int i=0; i<7; i++) if(str[i] == t) return res[i];
    return -1;
}
 
void put(int x, int piv){
    if(x==9){
        printf("%c%c",str[2*piv],str[2*piv+2]);
        return;
    }
    if(x>=5){
        printf("%c",str[2*piv+1]);
        x-=5;
    }
    if(x==4){
        printf("%c%c",str[2*piv],str[2*piv+1]);
        return;
    }
    for (int i=0; i<x; i++) {
        printf("%c",str[2*piv]);
    }
}
 
int parseStr(char *str){
    int res = 0;
    int l = (int)strlen(str);
    for (int i=0; i<l; i++) {
        if(i+1<l && fnd(str[i]) < fnd(str[i+1])){
            res += fnd(str[i+1])-fnd(str[i]);
            i++;
        }
        else res += fnd(str[i]);
    }
    return res;
}
 
void printRome(int x){
    put(x/1000,3);
    put((x/100)%10,2);
    put((x/10)%10,1);
    put(x%10,0);
}
 
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        char str1[100];
        scanf("%s", str1);
        if(*str1 <= '9' && *str1 >= '0'){
            int v;
            sscanf(str1, "%d", &v);
            printRome(v);
            puts("");
        }
        else{
            printf("%d\n", parseStr(str1));
        }
    }
}