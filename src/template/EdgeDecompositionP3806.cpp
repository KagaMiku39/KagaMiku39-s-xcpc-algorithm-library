#include<bits/stdc++.h>
using namespace std;
struct eg{
	int t,v,id;
};
struct e{
	int xx,yy,v;
}d[40005];
vector<int>vv;
int n,m,x,y,z,sz[40005],tt,pv[40005],s1,s2;
int b[105],t[10000005],as[105],p[40005];
vector<eg>v[40005],vp[10005];
void f1(int x,int fa){
    sz[x]=1;
    for(int i=0;i<v[x].size();i++){
        if(v[x][i].t==fa||p[v[x][i].id]) continue;
        f1(v[x][i].t,x),sz[x]+=sz[v[x][i].t];
    }
    return;
}
int f2(int x,int fa,int nm){
    for(int i=0,pp;i<v[x].size();i++){
        if(v[x][i].t==fa||p[v[x][i].id]) continue;
        pp=f2(v[x][i].t,x,nm);
        if(sz[v[x][i].t]<2*(nm+1)/3&&nm-sz[v[x][i].t]<=2*(nm+1)/3) return v[x][i].id;
        if(pp) return pp;
    }
    return 0;
}
void f(int x,int fa,int ds){
	for(int i=1;i<=m;i++) if(ds<=b[i]&&b[i]-ds<=1e7&&t[b[i]-ds]) as[i]=1;
	for(int i=0;i<v[x].size();i++){
		if(v[x][i].t==fa||p[v[x][i].id]) continue;
		f(v[x][i].t,x,ds+v[x][i].v);
	}
	return;
}
void ff(int x,int fa,int ds){
	if(ds<=1e7) t[ds]=1,vv.push_back(ds);
	for(int i=0;i<v[x].size();i++){
		if(v[x][i].t==fa||p[v[x][i].id]) continue;
		ff(v[x][i].t,x,ds+v[x][i].v);
	}
	return;
}
void bfz(int x){
	if(!x) return;
	p[x]=p[x&1]=1;
	ff(d[x].yy,d[x].xx,0);
	t[0]=t[d[x].v]=1;
	f(d[x].xx,d[x].yy,d[x].v),t[d[x].v]=0;
	for(int i=0;i<vv.size();i++) t[vv[i]]=0;
	vv.clear(); 
	f1(d[x].xx,d[x].yy),bfz(f2(d[x].xx,d[x].yy,sz[d[x].xx]));
	f1(d[x].yy,d[x].xx),bfz(f2(d[x].yy,d[x].xx,sz[d[x].yy]));
	return;
}
void dfs(int x,int fa){
	if(vp[x].size()==1&&fa) return;
	pv[x]=x;
	for(int i=0;i<vp[x].size();i++){
		if(vp[x][i].t==fa) continue;
		v[pv[x]].push_back({++n,0,++tt}),v[n].push_back({pv[x],0,++tt}),pv[x]=n;
		v[n].push_back({vp[x][i].t,vp[x][i].v,++tt}),v[vp[x][i].t].push_back({n,vp[x][i].v,++tt});
		dfs(vp[x][i].t,x);
	}
	return;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<n;i++){
    	cin>>x>>y>>z;
		vp[x].push_back({y,z}),vp[y].push_back({x,z});	
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) for(int j=0;j<v[i].size();j++) d[v[i][j].id]={i,v[i][j].t,v[i][j].v};
    for(int i=1;i<=m;i++) cin>>b[i];
	f1(1,0),t[0]=1;
	bfz(f2(1,0,n));
	for(int i=1;i<=m;i++){
		if(as[i]) cout<<"AYE\n";
		else cout<<"NAY\n";
	}
    return 0;
}