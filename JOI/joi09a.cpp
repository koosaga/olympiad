#include <cstdio>
#include <algorithm>
int main(){
    int n,len;
    scanf("%d %d",&n,&len);
    char a[1000001]={};
    scanf("%s",a);
    int data[100000]={};
    int ioiMode=0;
    int currentDataHead=-1;
    for (int i=0; a[i+2]; i++) {
        if(a[i]=='I' && a[i+1]=='O' && a[i+2]=='I'){
            if(!ioiMode){
                data[++currentDataHead]=1;
                i++;
                ioiMode=1;
            }
            else{
                data[currentDataHead]++;
                i++;
            }
        }
        else if(ioiMode)ioiMode=0;
    }
    int r=0;
    for (int i=0; data[i]; i++) {
        r+=std::max(data[i]+1-n,0);
        // (data[i]+1-n)
    }
    printf("%d",r);
}