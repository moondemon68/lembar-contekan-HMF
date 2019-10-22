void floydWarshall(){
    for(int k=0;k<N;k++){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(a[i][j] > a[i][k]+a[k][j]){
                    a[i][j] = a[i][k]+a[k][j];
                }
            }
        }
    }

    // checking negative cycle
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(a[i][j] < 0){
                cout << "It contains negative cycle!\n";
                return;
            }
        }
    }
}
