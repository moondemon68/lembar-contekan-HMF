const int NMAX = 100*1000;
ll t[4*NMAX+3];
ll lazy[4*NMAX+3];
ll a[NMAX+3];
int n,q;

void build(int v, int s, int e){
    if(s==e){
        t[v] = a[s];
    }else{
        int m = (s+e)/2;
        build(2*v,s,m);
        build(2*v+1,m+1,e);
        t[v] = min(t[2*v],t[2*v+1]);
    }
}

void updateRange(int v, int s, int e, int l, int r, ll val){
    if(lazy[v] != 0){
        t[v] += lazy[v];
        if(s != e){
            lazy[2*v] += lazy[v];
            lazy[2*v+1] += lazy[v];
        }
        lazy[v] = 0;
    }
    if(s > e || s > r || l > e){
        return;
    }
    if(l<=s && e<=r){
        t[v] += val;
        if(s != e){
            lazy[2*v] += val;
            lazy[2*v+1] += val;
        }
        return;
    }
    int m = (s+e)/2;
    updateRange(2*v,s,m,l,r,val);
    updateRange(2*v+1,m+1,e,l,r,val);
    t[v] = min(t[2*v],t[2*v+1]);
}

ll queryRange(int v, int s, int e, int l, int r){
    if(s > e || s > r || l > e){
        return inf;
    }
    if(lazy[v]!=0){
        t[v] += lazy[v];
        if(s!=e){
            lazy[2*v] += lazy[v];
            lazy[2*v+1] += lazy[v];
        }
        lazy[v] = 0;
    }
    if(l <= s && e <= r){
        return t[v];
    }
    int m = (s+e)/2;
    ll p1 = queryRange(2*v,s,m,l,r);
    ll p2 = queryRange(2*v+1,m+1,e,l,r);
    return min(p1,p2);
}
