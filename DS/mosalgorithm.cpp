// Variable to represent block size. This is made global
// so compare() of sort can use it.
int block;

// Structure to represent a query range
struct Query
{
    int L, R;
};

// Function used to sort all queries so that all queries
// of the same block are arranged together and within a block,
// queries are sorted in increasing order of R values.
bool compare(Query x, Query y)
{
    // Different blocks, sort by block.
    if (x.L/block != y.L/block)
        return x.L/block < y.L/block;

    // Same block, sort by R value
    return x.R < y.R;
}

// Prints sum of all query ranges. m is number of queries
// n is size of array a[].
void queryResults(int a[], int n, Query q[], int m)
{
    // Find block size
    block = (int)sqrt(n);
    cout << "block => " << block << "\n";
    // Sort all queries so that queries of same blocks
    // are arranged together.
    sort(q, q + m, compare);

    for(int i=0;i<m;i++){
        cout << q[i].L << " " << q[i].R << "\n";
    }
    cout << "\n";
    // Initialize current L, current R and current sum
    int currL = 0, currR = 0;
    int currSum = 0;

    // Traverse through all queries
    for (int i=0; i<m; i++)
    {
        // L and R values of current range
        int L = q[i].L, R = q[i].R;
        cout << L << "," << R << "\n";
        // Remove extra elements of previous range. For
        // example if previous range is [0, 3] and current
        // range is [2, 5], then a[0] and a[1] are subtracted
        while (currL < L)
        {
            currSum -= a[currL];
            currL++;
        }

        // Add Elements of current Range
        while (currL > L)
        {
            currSum += a[currL-1];
            currL--;
        }
        while (currR <= R)
        {
            currSum += a[currR];
            currR++;
        }

        // Remove elements of previous range.  For example
        // when previous range is [0, 10] and current range
        // is [3, 8], then a[9] and a[10] are subtracted
        while (currR > R+1)
        {
            currSum -= a[currR-1];
            currR--;
        }
        cout << currL << " " << currR << "\n";
        // Print sum of current range
        cout << "Sum of [" << L << ", " << R
             << "] is "  << currSum << endl;
    }
}
