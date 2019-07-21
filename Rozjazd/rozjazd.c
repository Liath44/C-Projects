#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void rozjazd(int A[], int n, int k)
{
k = k%(2 * n);
if(k%2 == 1)
    {
    for(int i = 0; i < 2* n; i = i + 2)
        {
        int j = i + k;
        int pomoc = A[i];
        if(j >= 2 * n)
            {
            j = j% (2 * n);
            }
        A[i] = A[j];
        A[j] = pomoc;
        }
    }
else
    {
    for(int i = 0; i < k; i = i +2)
        {
        int trzymaj, przekaz;
        trzymaj = A[i];
        int nast = i + k;
        bool kontynuuj = true;
        while(kontynuuj)
            {
            if(nast >= 2 * n)
                {
                nast = nast % (2 * n);
                kontynuuj = false;
                }
            przekaz = trzymaj;
            trzymaj = A[nast];
            A[nast] = przekaz;
            nast = nast + k;
            }
        }
    for(int j = 2 * n - 1; j > 2 * n - k; j = j - 2)
        {
        int trzymaj, przekaz;
        trzymaj = A[j];
        int nast = j - k;
        bool kontynuuj = true;
        while(kontynuuj)
            {
            if(nast < 0)
                {
                kontynuuj = false;
                nast = nast * (-1);
                nast = 2 * n - nast;
                }
            przekaz = trzymaj;
            trzymaj = A[nast];
            A[nast] = przekaz;
            nast = nast - k;
            }
        }
    }
}

int main(void)
{
int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
int k = 3;
int n = 9;
for(int q = 0; q < 18; ++q)
    {
    printf("%d ", A[q]);
    }
printf("\n");
rozjazd(A, n, k);
for(int i = 0; i < 18; ++i)
    {
    printf("%d ", A[i]);
    }
printf("\n");
return 0;
}
