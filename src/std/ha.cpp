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

const int N=155,oo=1e9;

int n,m,q,f[N][N][N];

struct edge{
	int u,v,l;
}t[5005];

inline bool cmp(const edge &a,const edge &b){
	return a.l<b.l;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("ha.in","r",stdin);
	freopen("ha.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&t[i].u,&t[i].v,&t[i].l);
	}
	sort(t+1,t+m+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=0;k<=n;k++){
				f[i][j][k]=oo;
			}
		}
	}
	for(int i=1;i<=n;i++){
		f[i][i][0]=0;
		for(int j=1;j<=m;j++){
			int u=t[j].u,v=t[j].v,l=t[j].l;
			for(int k=0;k<n;k++){
				f[i][v][k+1]=min(f[i][v][k+1],f[i][u][k]+l);
			}
		}
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				f[i][j][k]=min(f[i][j][k],f[i][j][k-1]);
			}
		}
	}
	while(q--){
		int u,v,l;scanf("%d%d%d",&u,&v,&l);l=min(l,n);
		if(f[u][v][l]>=oo){
			puts("-1");
		}else{
			printf("%d\n",f[u][v][l]);
		}
	}
	return 0;
}
