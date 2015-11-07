include <cstdio>  
  
int found=0,n,result;  
int dp[11][11]={};  
int ncr(int a,int b){  
    if(a==0) return 0;  
    if(dp[a][b]) return dp[a][b];  
    if(b==0 || b==a) return 1;  
    else return dp[a][b]=ncr(a-1,b)+ncr(a-1,b-1);  
}  
  
void haptrack(int a[],bool t[],int i,int current){  
    if(found) return;  
    if(i==n && current==result){  
        for (int l=0; l<n; l++) {  
            printf("%d ",a[l]);  
        }  
        found=1;  
    }  
    else if(i==n) return;  
    else{  
        for (int l=1; l<=n; l++) {  
            if(t[l]) continue;  
            a[i]=l;  
            t[l]=1;  
            haptrack(a,t,i+1,current+ncr(n-1,i)*l);  
            t[l]=0;  
        }  
        a[i]=0;  
    }  
}  
int main(){  
    scanf("%d %d",&n,&result);  
    int a[20]={};  
    bool t[20]={};  
    if(n==1) printf("1");  
    else haptrack(a,t,0,0);  
}  