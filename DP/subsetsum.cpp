bool iterative_is_subset(int n, int v){
    // The value of subset[i][j] will be true if there is a
    // subset of set[0..i-1] with sum equal to j

    bool dp[n+3][v+3];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=v;j++){
            if(j == 0){
                dp[i][j] = true;
            }
            else if(i == 0){
                dp[i][j] = false;
            }else{
                if(sets[i-1] <= j){
                    dp[i][j] = (dp[i-1][j] || dp[i-1][j-sets[i-1]]);
                }else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
    }
    return dp[n][v];
}
