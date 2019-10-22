int n, m;
struct Node
{
    vector<int> adj;
};
Node graf[MAX_N];
stack<int> Stack;
bool onStack[MAX_N];
int Indices, Index[MAX_N], LowLink[MAX_N], component[MAX_N], numComponents;

// Complexity : O(V + E)

void tarjanDFS(int i)
{
    Index[i] = ++Indices;
    LowLink[i] = Indices;
    Stack.push(i); onStack[i] = true;
    for (int j=0;j<graf[i].adj.size();j++)
    {
        int w = graf[i].adj[j];
        if (Index[w] == 0)
        {
            tarjanDFS(w);
            LowLink[i] = min(LowLink[i], LowLink[w]);
        }
        else if (onStack[w])
        {
            LowLink[i] = min(LowLink[i], Index[w]);
        }
    }
    if (LowLink[i] == Index[i])
    {
        int w = 0;
        do
        {
            w = Stack.top(); Stack.pop();
            component[w] = numComponents;
            onStack[w] = false;
        } while (i != w && !Stack.empty());
        numComponents++;
    }
}

void Tarjan()
{
    Indices = 0;
    while (!Stack.empty()) Stack.pop();
    for (int i=n;i>0;i--) onStack[i] = LowLink[i] = Index[i] = 0;
    numComponents = 0;
    for (int i=n;i>0;i--) if (Index[i] == 0) tarjanDFS(i);
}
