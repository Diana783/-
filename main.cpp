#include <QTextStream>
#include <iostream>
#include <ctime>
#include <time.h>

using namespace std;

void selection(int *num, int n)
{
        int i, j, mx, nmx;

        for (i = 0; i < n - 1; i++)
        {
                mx = num[i];
                nmx = i;
                for (j = i + 1; j < n; j++)
                {
                        if (num[j]<mx)
                        {
                                mx = num[j];
                                nmx = j;
                        }
                }
                num[nmx] = num[i];
                num[i] = mx;
        }
}

void generation(int *num, int *num1, int n)
{
        for (int i = 0; i < n; i++)
        {
                num[i] = 0 + rand() % 11;
                num1[i] = num[i];
        }

}

void radix(int *num1, int *br, int *cr, int n)
{
        int i, k, l;
        k = 10;
        l = n;
        for (i = 0; i <= k; i++)
                cr[i] = 0;
        for (i = 0; i < l; i++)
                cr[num1[i]] += 1;
        for (i = 1; i < k + 1; i++)
                cr[i] += cr[i - 1];
        for (i = n - 1; i >= 0; i--)
        {
                br[cr[num1[i]] - 1] = num1[i];
                cr[num1[i]] -= 1;
        }
}


int main()
{
    QTextStream cout(stdout);
       cout.stCodec("CP866");
        time_t start, end;
        int n, *num, *num1, *br,*cr;
        cr = new int[10];
        srand(time(NULL));
        cout << "Введите количество элементов: ";
        cin >> n;
        num = new int[n];
        num1 = new int[n];
        br = new int[n];
        cr = new int[10];
        generation(num,num1,n);
        time(&start);
        selection(num, n);
        time(&end);

        for (int i=0; i < 20; i++)
                cout << num[i] << " ";
        double seconds = difftime(end, start);
        printf("The time: %f seconds\n", seconds);

        time(&start);
        radix(num1, br, cr, n);
        time(&end);
        for (int i = 0; i < 20; i++)
                        cout << br[i] << " ";
        double seconds1 = difftime(end, start);
        printf("The time: %f seconds\n", seconds1);

        system("pause");
    return 0;
}
