// O(N^2) solution
int iterative_dp(){
    int dp[n+3];
    for(int i=1;i<=n;i++){
        dp[i] = 1;
        for(int j=1;j<i;j++){
            if(a[j-1] < a[i-1]){
                dp[i] = max(dp[i],dp[j]+1);
            }
        }
    }
    return *max_element(dp+1,dp+1+n);
}

// O(N Log N) solution
int lis(){
    int tail[n+3], len = 1;
    MEM(tail,0);

    tail[0] = a[0];
    for(int i=1;i<n;i++){
        if(a[i] > tail[len-1]){
            // if there is an element bigger than the tail
            // change the tail to that element
            len++;
            tail[len-1] = a[i];
        }else{
            // find wether a[i] is already in the subsequence or not
            auto it = find(tail,tail+len,a[i]);
            if(it != tail+len){
                // if found then continue
                continue;
            }
            // if there is no a[i], then change the tail element to a[i]
            it = upper_bound(tail,tail+len,a[i]);
            *it = a[i];
        }
    }
    return len;
}
