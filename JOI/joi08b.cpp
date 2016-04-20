#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
char str1[4005], str2[4005];
int len1, len2, res = 0;
 
int f(int s1, int s2){
    int r = 0;
    int res = 0;
    for (int i=0; i<len2-s2 && i<len1-s1; i++) {
        if(str1[i+s1] == str2[i+s2]) r++;
        else res = max(res,r), r = 0;
    }
    return max(res,r);
}
int main(){
    scanf("%s %s",str1,str2);
    len1 = (int) strlen(str1);
    len2 = (int) strlen(str2);
    for (int i=0; i<len1; i++) {
        res = max(res,f(i,0));
    }
    for (int i=0; i<len2; i++) {
        res = max(res,f(0,i));
    }
    printf("%d",res);
}