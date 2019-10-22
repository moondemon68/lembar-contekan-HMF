typedef long long ll;
const ll inf = 1e18;
ll minimum_coin(){
    dp[0] = 0; // if the value is 0 then include nothing
    for(int i=1;i<=v;i++){
        dp[i] = inf; // set dp[i] to infinite if it is not possible to have a value i
        for(int j=1;j<=n;j++){
            if(c[j-1] <= i){
                dp[i] = min(dp[i], 1+dp[i - c[j-1]]);
            }
        }
    }
    if(dp[v] == inf){
        dp[v] = -1;
    }
    return dp[v];
}
