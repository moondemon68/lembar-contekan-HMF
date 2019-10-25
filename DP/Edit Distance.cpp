// (remove => dp[i-1][j], insert => dp[i][j-1], replace => dp[i-1][j-1])
int iterative_edit_distance(){
    int dp[n+3][m+3];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(i == 0){
                dp[i][j] = j;
            }else if(j == 0){
                dp[i][j] = i;
            }else{
                if(str1[i-1] == str2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = 1 + minimum(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]);
                }
            }
        }
    }
    return dp[n][m];
}
