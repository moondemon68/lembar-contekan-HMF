int cutting_rod(){
    int dp[n+3];
    for(int i=1;i<=n;i++){
        if(i == 1){
            dp[i] = a[i-1];
        }else{
            dp[i] = a[i-1];
            for(int j=1;j<=i/2;j++){
                dp[i] = max(dp[i],dp[j] + dp[i-j]);
            }
        }
    }
    return dp[n];
}
