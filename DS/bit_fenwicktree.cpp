int BIT[1000], a[1000], n;

void update(int x, int val){
    for(; x<=n ; x+=x&-x){
        BIT[x] += val;
    }
}

void update2(int x, int val){
    for(; x<0 ; x|=(x+1)){
        BIT[x] += val;
    }
}

int query(int x){
    int sum = 0;
    for(; x>0 ; x-=x&-x){
        sum += BIT[x];
    }
    return sum;
}

int query2(int x){
    int sum = 0;
    for(;x>=0;x=(x&(x+1))-1){
        sum += BIT[x];
    }
    return sum
}
