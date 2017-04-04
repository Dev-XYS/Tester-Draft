#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <math.h>
#include   <time.h>
#include   <vector>
#include   <bitset>
#include    <queue>
#include      <set>
#include      <map>
using namespace std;

typedef long long LL;

const int N=5005,Mod=1e9+7;

int n,m,b[N],a[N],f[10000005],C[N],ok[N],Ans;

int Pow(int a,int b){
	int s=1;
	while(b){
		if(b&1){
			s=s*(LL)a%Mod;
		}
		a=a*(LL)a%Mod;b>>=1;
	}
	return s;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("ya.in","r",stdin);
	freopen("ya.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);f[0]=f[1]=1;
	for(int i=2;i<=n;i++){
		f[i]=(f[i-1]+(LL)f[i-2]*(i-1))%Mod;
	}
	C[0]=1;
	for(int i=1;i<=m;i++){
		C[i]=(LL)C[i-1]*(n-m-i+1)%Mod*Pow(i,Mod-2)%Mod;
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&b[i]);
	}
	for(int i=0;i<=m;i++){
		ok[b[i]]=1;
		if(n-m-(m-i)<0){
			continue;
		}
		for(int j=1,k=0;j<=i;++j){
			k++;
			while(!ok[k]){
				k++;
			}
			a[k]=b[j];
		}
		int flag=1;
		for(int j=1;j<=m;j++){
			if(ok[j]&&a[a[j]]!=j){
				flag=0;
			}
		}
		if(flag){
			Ans=(Ans+(LL)C[m-i]*f[n-m-(m-i)])%Mod;
		}
	}
	printf("%d\n",Ans);
	return 0;
}
