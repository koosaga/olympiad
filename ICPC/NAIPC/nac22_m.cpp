#include<bits/stdc++.h>
using namespace std;

int arr[50000][6];


int main(){
	int n;
	scanf("%d",&n);
	int cnt=0;
	int i,j,k,cel,cel2;
	cel=0;
	for(i=0;i<26;i++){
		if(i%2==0){
			for(j=0;j<26;j++){
				arr[cel][2]=i;
				arr[cel][3]=i;
				arr[cel][4]=j;
				arr[cel][5]=j;
				cel++;
				if(j<25){
				arr[cel][2]=i;
				arr[cel][3]=i;
				arr[cel][4]=j;
				arr[cel][5]=j+1;
				cel++;
				}
			}
			arr[cel][2]=i;
			arr[cel][3]=i+1;
			arr[cel][4]=25;
			arr[cel][5]=25;
			cel++;
		}
		else{
			for(j=25;j>=0;j--){
				arr[cel][2]=i;
				arr[cel][3]=i;
				arr[cel][4]=j;
				arr[cel][5]=j;
				cel++;
				if(j>0){
				arr[cel][2]=i;
				arr[cel][3]=i;
				arr[cel][4]=j;
				arr[cel][5]=j-1;
				cel++;
				}
			}
			if(i<25){
				arr[cel][2]=i;
				arr[cel][3]=i+1;
				arr[cel][4]=0;
				arr[cel][5]=0;
				cel++;
			}
			
		}
	}
	
	for(j=0;j<cel;j++){
		arr[j][0]=0;
		arr[j][1]=0;
	}
	arr[cel][0]=0;
	arr[cel][1]=1;
	arr[cel][2]=25;
	arr[cel][3]=25;
	arr[cel][4]=0;
	arr[cel][5]=0;
	cel2=cel+1;
	for(k=1;k<25;k++){
		if(k%2==1){
			for(j=cel-1;j>=0;j--){
				arr[cel2][0]=k;
				arr[cel2][1]=k;
				arr[cel2][2]=arr[j][2];
				arr[cel2][3]=arr[j][3];
				arr[cel2][4]=arr[j][4];
				arr[cel2][5]=arr[j][5];
				cel2++;
				
			}
			arr[cel2][0]=k;
			arr[cel2][1]=k+1;
			arr[cel2][2]=arr[cel2-1][2];
			arr[cel2][3]=arr[cel2-1][3];
			arr[cel2][4]=arr[cel2-1][4];
			arr[cel2][5]=arr[cel2-1][5];
			cel2++;
		}
		else{
			for(j=0;j<cel;j++){
				arr[cel2][0]=k;
				arr[cel2][1]=k;
				arr[cel2][2]=arr[j][2];
				arr[cel2][3]=arr[j][3];
				arr[cel2][4]=arr[j][4];
				arr[cel2][5]=arr[j][5];
				cel2++;
				
			}
			arr[cel2][0]=k;
			arr[cel2][1]=k+1;
			arr[cel2][2]=arr[cel2-1][2];
			arr[cel2][3]=arr[cel2-1][3];
			arr[cel2][4]=arr[cel2-1][4];
			arr[cel2][5]=arr[cel2-1][5];
			cel2++;
		}
	}
	
	for(i=0;i<n;i++){
		printf("%c%c%c%c%c%c\n",'a'+arr[i][0],'a'+arr[i][1],'a'+arr[i][2],'a'+arr[i][3],'a'+arr[i][4],'a'+arr[i][5]);
	}
	
}