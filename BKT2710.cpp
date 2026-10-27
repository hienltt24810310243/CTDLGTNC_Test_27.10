#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define MAX 20
#define VO_CUC 1000000

int A[MAX][MAX];
int n;

bool Nhap(const char *tenFile)
{
    ifstream f(tenFile);
    if (!f)
    {
        cout << "Khong mo duoc file " << tenFile << endl;
        return false;
    }
    f >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            f >> A[i][j];
    f.close();
    return true;
}

void HienThi()
{
    cout << "So dinh: " << n << endl;
    cout << "Ma tran trong so:" << endl;

    cout << "     ";
    for (int j = 1; j <= n; j++)
        cout << "   V" << j;
    cout << endl;

    for (int i = 1; i <= n; i++)
    {
        cout << "   V" << i;
        for (int j = 1; j <= n; j++)
            cout << setw(5) << A[i][j];
        cout << endl;
    }
}

void TimDuongDi(int u, int v)
{
    int dist[MAX];
    int truoc[MAX];
    bool daXet[MAX];

    for (int i = 1; i <= n; i++)
    {
        dist[i] = VO_CUC;
        truoc[i] = 0;
        daXet[i] = false;
    }
    dist[u] = 0;

    for (int lan = 1; lan <= n; lan++)
    {
        int k = 0, min = VO_CUC;
        for (int i = 1; i <= n; i++)
            if (!daXet[i] && dist[i] < min)
            {
                min = dist[i];
                k = i;
            }

        if (k == 0) break;
        daXet[k] = true;
        if (k == v) break;

        for (int j = 1; j <= n; j++)
            if (A[k][j] > 0 && !daXet[j] && dist[k] + A[k][j] < dist[j])
            {
                dist[j] = dist[k] + A[k][j];
                truoc[j] = k;
            }
    }

    if (dist[v] == VO_CUC)
    {
        cout << "Khong co duong di tu V" << u << " den V" << v << endl;
        return;
    }

    int duong[MAX], dem = 0;
    for (int x = v; x != 0; x = truoc[x])
        duong[dem++] = x;

    cout << "Duong di ngan nhat tu V" << u << " den V" << v << ": ";
    for (int i = dem - 1; i >= 0; i--)
    {
        cout << "V" << duong[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
    cout << "Do dai: " << dist[v] << endl;
}

int main()
{
    if (!Nhap("Grap2710.txt"))
        return 0;

    HienThi();
    cout << endl;

    TimDuongDi(1, 6);
    return 0;
}
