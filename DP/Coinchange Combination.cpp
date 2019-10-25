typedef long long ll;
ll compressed(){
    ll table[v+1];
    MEM(table,0);
    table[0] = 1;
    for(int i=0;i<n;i++){
        for(int j=c[i];j<=v;j++){
            table[j] += table[j-c[i]];
        }
    }
    return table[v];
}
