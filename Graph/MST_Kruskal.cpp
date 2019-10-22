struct E{
    int u,v,w;
};

const int N = 100;
int T,n,m,a,b,c;
E temp;
vector<E> graph; // Store the inputted graph (u, v, w).
vector<E> selected_edges; // Store the edges which is selected for the MST from given graph.
int parent[N+2];

bool cstm(E a, E b){
    return a.w < b.w;
}

int findParent(int r){
    if(r == parent[r])return r;
    return parent[r] = findParent(parent[r]);
}

int Kruskal_MST(){

    for(int i=1;i<=n;i++)parent[i] = i;

    sort(graph.begin(),graph.end(),cstm);

    /*for(int i=0;i<graph.size();i++){
        cout << graph[i].w << "\n";
    }*/

    int edgeCounter = 0, totalCost = 0;

    int len = graph.size();

    for(int i=0; i<len;i++){

        int parent_of_u = findParent(graph[i].u);
        int parent_of_v = findParent(graph[i].v);

        if(parent_of_u != parent_of_v){
            parent[parent_of_u] = parent_of_v;
            totalCost += graph[i].w;
            selected_edges.pb(graph[i]);

            edgeCounter++;
            if(edgeCounter == n-1)
                break;
        }

    }
    return totalCost;
}
