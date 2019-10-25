#include <bits/stdc++.h>
using namespace std;

void computeLPSArray(char *pat, int M, int *lps);

void KMPSearch(char *pat, char *txt, vector<int> &ans)
{
	int M = strlen(pat);
	int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix values for pattern
	int *lps = (int *)malloc(sizeof(int)*M);
    int j  = 0;  // index for pat[]

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0;  // index for txt[]
    while (i < N)
    {
    	if (pat[j] == txt[i])
    	{
    		j++;
    		i++;
    	}

    	if (j == M)
    	{
    		ans.push_back(i-j);
        // printf("Found pattern at index %d \n", i-j);
    		j = lps[j-1];
    	}

      // mismatch after j matches
    	else if (i < N && pat[j] != txt[i])
    	{
        // Do not match lps[0..lps[j-1]] characters,
        // they will match anyway
    		if (j != 0)
    			j = lps[j-1];
    		else
    			i = i+1;
    	}
    }
    free(lps); // to avoid memory leak
}

void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;  // lenght of the previous longest prefix suffix
    int i;

    lps[0] = 0; // lps[0] is always 0
    i = 1;

    // the loop calculates lps[i] for i = 1 to M-1
    while (i < M)
    {
    	if (pat[i] == pat[len])
    	{
    		len++;
    		lps[i] = len;
    		i++;
    	}
       else // (pat[i] != pat[len])
       {
            if (len != 0) {
                // This is tricky. Consider the example AAACAAAA and i = 7.
                len = lps[len-1];
                // Also, note that we do not increment i here
            } else // if (len == 0)
                {
                    lps[i] = 0;
                    i++;
                }
        }
    }
}

// Driver program to test above function
int main() {
	int t; 
	scanf("%i", &t);
	while(t--){
		char str[1000020], pat[1000020];
		scanf("%s %s", str, pat);
		vector<int> ans;
		KMPSearch(pat, str, ans);
		if (ans.size() == 0){
			printf("Not Found\n");
			continue;
		}
		printf("%lu\n", ans.size());
		for(int i = 0; i < ans.size(); i++)
			printf("%i ", ans[i]+1);
		printf("\n");
	}
	return 0;
}