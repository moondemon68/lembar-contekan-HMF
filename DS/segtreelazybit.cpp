const int N = 5e4+5;
int n,q;
long long bits[N][33], t[4*N][33], lazy[4*N][33];

void build(int v, int s, int e, int k){
    if(s == e){
        t[v][k] = bits[s][k];
    }else{
        int m = (s+e)>>1;
        build(v<<1,s,m,k);
        build(v<<1|1,m+1,e,k);
        t[v][k] = t[v<<1][k] + t[v<<1|1][k];
    }
}

void update(int v, int s, int e, int l, int r, int k){
    if(lazy[v][k]){
        t[v][k] = (e-s+1) - t[v][k];
        if(s != e){
            lazy[v<<1][k] ^= 1;
            lazy[v<<1|1][k] ^= 1;
        }
        lazy[v][k] = 0;
    }

    if(s > r || l > e){
        return;
    }

    if(l <= s && e <= r){
        t[v][k] = (e-s+1) - t[v][k];
        if(s != e){
            lazy[v<<1][k] ^= 1;
            lazy[v<<1|1][k] ^= 1;
        }
        lazy[v][k] = 0;
        return;
    }

    int m = (s+e)>>1;
    update(v<<1,s,m,l,r,k);
    update(v<<1|1,m+1,e,l,r,k);
    t[v][k] = t[v<<1][k] + t[v<<1|1][k];
}

long long query(int v, int s, int e, int l, int r, int k){
    if(lazy[v][k]){
        t[v][k] = (e-s+1) - t[v][k];
        if(s != e){
            lazy[v<<1][k] ^= 1;
            lazy[v<<1|1][k] ^= 1;
        }
        lazy[v][k] = 0;
    }


    if(s > r || e < l){
        return 0;
    }

    if(l <= s && e <= r){
        return t[v][k];
    }

    int m = (s+e)>>1;
    return query(v<<1,s,m,l,r,k) + query(v<<1|1,m+1,e,l,r,k);
}
