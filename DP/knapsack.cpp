int iterative_dp(){
    for(int i=0;i<=N;i++){
        for(int j=0;j<=W;j++){
            if(i == 0 || j == 0){
                dp[i][j] = 0;
            }else{
                dp[i][j] = dp[i-1][j];
                if(weight[i-1] <= j){
                    dp[i][j] = max(dp[i][j], value[i-1] + dp[i-1][j-weight[i-1]]);
                }
            }
        }
    }
    return dp[N][W];
}
