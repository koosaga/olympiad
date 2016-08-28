#include <cstdio>
#include <cstdlib>
 
int n;
char str[2000005];
 
long long pow[2000005], l_hash, r_hash, c_hash;
int result = -1;
 
void input(){
    scanf("%d %s",&n,str);
    if(!(n&1)){
        puts("NOT POSSIBLE");
        exit(0);
    }
    pow[0] = 1;
    for (int i=1; i<n; i++) {
        pow[i] = pow[i-1] * 697;
    }
}
 
void output(){
    if(result == -1) puts("NOT POSSIBLE");
    else{
        int p = 0;
        for (int i=0; i<n/2+p; i++) {
            if(i == result){
                p++;
                continue;
            }
            putchar(str[i]);
        }
    }
}
 
void calc_left(long long l_hash, long long r_hash){
    int piv = 0;
    for (int i=n/2-1; i>=0; i--) {
        l_hash -= pow[piv] *(str[i] - str[i+1]);
        if(l_hash == r_hash && l_hash != c_hash){
            if(~result){
                puts("NOT UNIQUE");
                exit(0);
            }
            else result = i, c_hash = l_hash;
        }
        piv++;
    }
}
 
void calc_right(long long l_hash, long long r_hash){
    int piv = n/2-1;
    for (int i=n/2+1; i<n; i++) {
        r_hash += (str[i-1] -str[i]) * pow[piv];
        if(l_hash == r_hash && l_hash != c_hash){
            if(~result){
                puts("NOT UNIQUE");
                exit(0);
            }
            else result = i, c_hash = l_hash;
        }
        piv--;
    }
}
 
int main(){
    input();
    for (int i=0; i<n/2; i++) {
        l_hash *= 697;
        r_hash *= 697;
        l_hash += str[i] - 'A';
        r_hash += str[n/2 + 1 + i] - 'A';
    }
    if(l_hash == r_hash) result = n/2, c_hash = l_hash;
    calc_left(l_hash,r_hash);
    calc_right(l_hash,r_hash);
    output();
}
