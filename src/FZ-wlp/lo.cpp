#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
#define ll long long
#define MAXN 110005
struct node
{
	int x,y;
	bool b;
	node(int a=0,int b=0)
	{
		x=a;
		y=b;
	}
	node operator+(node b)
	{
		return node(x+b.x,y+b.y);
	}
	node operator-(node b)
	{
		return node(x-b.x,y-b.y);
	}
	ll operator*(node b)
	{
		return x*b.y-y*b.x;
	}
	bool operator<(node z)
	{
		if(x!=z.x)return x<z.x;
		if(y!=z.y)return y<z.y;
		return b>z.b;
	}
	bool operator==(node z)
	{
		return x==z.x&&y==z.y;
	}
}a[MAXN],b[MAXN],p[MAXN],s[MAXN];
bool c[505];
int n,m,i,N,t,ans;
bool cmp(node a,node b)
{
	ll t=(a-p[1])*(b-p[1]);
	if(t)return t<0;
	return a<b;
}
int check()
{
	int i,j;
	for(i=1;i<=n;i++)p[i]=a[i];
	for(i=1,N=n;i<=m;i++)if(c[i])p[++N]=b[i];
	for(i=j=1;i<=N;i++)if(p[i]<p[j])j=i;
	swap(p[1],p[j]);
	sort(p+2,p+N+1,cmp);
	for(i=2,j=1;i<=N;i++)if(p[i]==p[i-1])p[j].b=min(p[j].b,p[i].b);
	else p[++j]=p[i];
	N=j;
	t=0;
	if(N==1)return !p[1].b;
	s[++t]=p[1];
	s[++t]=p[2];
	for(i=3;i<=N;s[++t]=p[i++])for(;t>1&&(s[t]-s[t-1])*(p[i]-s[t])>=0;t--);
	for(i=1;i<=t;i++)if(s[i].b)return 0;
	return t;
}
int main()
{
	freopen("lo.in","r",stdin);
	freopen("lo.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;a[i++].b=1)scanf("%d%d",&a[i].x,&a[i].y);
	for(i=1;i<=m;b[i++].b=0)scanf("%d%d",&b[i].x,&b[i].y);
	for(i=1;i<=m;i++)c[i]=1;
	if(!(i=check()))
	{
		puts("-1");
		return 0;
	}
	if(m<=10)
	{
		for(ans=i,i=0;i<1<<m;i++)
		{
			int j;
			for(j=1;j<=m;j++)c[j]=i>>j-1&1;
			j=check();
			if(j)ans=min(ans,j);
		}
		cout<<ans<<endl;
		return 0;
	}
	for(ans=i,i=1;i<=m;i++)c[i]=rand()%3<2;
	for(;clock()<950;)if(i=check()){for(ans=min(ans,i),i=1;i<=m;i++)if(c[i]&&(rand()%4<1))c[i]=0;}
	else for(i=1;i<=m;i++)if(!c[i]&&(rand()%4<1))c[i]=1;
	cout<<ans<<endl;
	return 0;
}

