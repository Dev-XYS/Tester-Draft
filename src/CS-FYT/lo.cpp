#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define N 100005
using namespace std;
typedef long long ll;
inline int read(){
	int sum = 0, t = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ sum = sum * 10 + ch - '0'; ch = getchar(); }
	return sum * t;
}

struct Point{
	ll x, y;
	Point(){}
	Point(ll _, ll __) : x(_), y(__) {}
	Point operator + (const Point &a){ return Point(x + a.x, y + a.y); }
	Point operator - (const Point &a){ return Point(x - a.x, y - a.y); }
	Point operator * (const ll &k){ return Point(x * k, y * k); }
	ll operator * (const Point &a){ return x * a.y - y * a.x; }
	ll operator & (const Point &a){ return x * a.x + y * a.y; }
	bool operator < (const Point &a) const{
		return x == a.x ? y < a.y : x < a.x; 
	}
}p[N], q[N], p1[N], p2[N];

int n, m, ans, dis[N], t1, t2;

int nxt[N<<4], fir[N], to[N<<4], cnt;

void add(int x, int y){
	nxt[++cnt] = fir[x]; to[cnt] = y; fir[x] = cnt;
}

void bfs(int S){
	queue<int>que;
	memset(dis, 0, sizeof(dis));
	dis[S] = 1;
	que.push(S);
	while(!que.empty()){
		int x = que.front(); que.pop();
		for(int i = fir[x]; i ; i = nxt[i]){
			int y = to[i];
			if(y == S) ans = min(ans, dis[x]); 
			if(!dis[y]) que.push(y), dis[y] = dis[x] + 1;
		}
	}
}

void hill(){
	sort(p + 1, p + n + 1);
	p1[t1 = 1] = p[1];
	for(int i = 2; i <= n; i++){
		while(t1 > 1 && (p[i] - p1[t1 - 1]) * (p1[t1] - p1[t1 - 1]) >= 0) t1--;
		p1[++t1] = p[i];
	}
	p2[t2 = 1] = p[n];
	for(int i = n - 1; i ; i--){
		while(t2 > 1 && (p[i] - p2[t2 - 1]) * (p2[t2] - p2[t2 - 1]) >= 0) t2--;
		p2[++t2] = p[i];
	}
}

ll check(Point P, Point Q, Point P1){
	return (Q - P) * P1;
}

int main(){
	freopen("lo.in", "r", stdin);
	freopen("lo.out", "w", stdout);
	n = read(), m = read();
	ans = m + 1;
	for(int i = 1; i <= n; i++)
		p[i].x = read(), p[i].y = read();
	for(int i = 1; i <= m; i++)
		q[i].x = read(), q[i].y = read();
	hill();
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++) if(q[i].x != q[j].x || q[i].y != q[j].y){
			ll Min = 1e18;
			int l = 1, r = t1;
			Min = min(Min, check(q[j], q[i], p1[l]));
			Min = min(Min, check(q[j], q[i], p1[r]));
			while(r - l > 5){
				int ml = (2 * l + r) / 3;
				int mr = (2 * r + l) / 3;
				if(check(q[j], q[i], p1[ml]) > check(q[j], q[i], p1[mr])) l = ml;
				else r = mr;
			}
			for(int k = l; k <= r; k++)
				Min = min(Min, check(q[j], q[i], p1[k]));
			
			l = 1, r = t2;
			Min = min(Min, check(q[j], q[i], p2[l]));
			Min = min(Min, check(q[j], q[i], p2[r]));
			while(r - l > 5){
				int ml = (2 * l + r) / 3;
				int mr = (2 * r + l) / 3;
				if(check(q[j], q[i], p2[ml]) > check(q[j], q[i], p2[mr])) l = ml;
				else r = mr;
			}
			for(int k = l; k <= r; k++)
				Min = min(Min, check(q[j], q[i], p2[k]));
			if(Min >= q[j] * q[i]) add(i, j);
		}
	for(int i = 1; i <= m; i++)
		bfs(i);
	if(ans <= m) printf("%d\n", ans);
	else puts("-1");
}


