#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
struct node
{
	int s,t,d;
	bool operator<(const node& y)const
	{
		return d<y.d;
	}
}e[5005];
int n,m,q,i,j,k,ans,f[155][155][155];
int main()
{
	freopen("ha.in","r",stdin);
	freopen("ha.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(i=0;i<m;i++)scanf("%d%d%d",&e[i].s,&e[i].t,&e[i].d);
	sort(e,e+m);
	memset(f,127,sizeof(f));
	for(i=1;i<=n;i++)f[i][i][0]=0;
	for(i=0;i<m;i++)for(j=1;j<=n;j++)for(k=0;k<n;k++)f[j][e[i].t][k+1]=min(f[j][e[i].t][k+1],f[j][e[i].s][k]+e[i].d);
	while(q--)
	{
		scanf("%d%d%d",&i,&j,&k);
		for(ans=f[0][0][0];~k;k--)ans=min(ans,f[i][j][k]);
		if(ans==f[0][0][0])ans=-1;
		cout<<ans<<endl;
	}
	return 0;
}

