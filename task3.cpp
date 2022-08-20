#include <cstdio>
#include <algorithm>

const int maxn = 500005;



class DancingLinksNode
{
public:
    int left[maxn], right[maxn], upper[maxn], down[maxn];
    int row[maxn], col[maxn], sum[maxn];
    int num, cnt, height, width;
    int vis[maxn];

    void add(int piece, int left_c, int right_c, int upper_c, int down_c, int x_c, int y_c)
    {
        // add coordinates for a new piece
        left[piece] = left_c;
        right[piece] = right_c;
        upper[piece] = upper_c;
        down[piece] = down_c;
        row[piece] = x_c;
        col[piece] = y_c;
    }

    void reset(int w, int h)
    {
        // reset node
        num = 0x7FFFFFF;
        width = w;
        height = h;
        for (int i = 0; i <= h; i++)
        {
            add(i, i - 1, i + 1, i, i, 0, i);
            sum[i] = 0;
        }
        left[0] = h, right[h] = 0, cnt = h + 1;
    }

    void insert(int x, int y)
    {
        int temp = cnt - 1;
        if (row[temp] != x)
        {
            add(cnt, cnt, cnt, upper[y], y, x, y);
            upper[down[cnt]] = cnt;
            down[upper[cnt]] = cnt;
        }
        else
        {
            add(cnt, temp, right[temp], upper[y], y, x, y);
            right[left[cnt]] = cnt;
            left[right[cnt]] = cnt;
            upper[down[cnt]] = cnt;
            down[upper[cnt]] = cnt;
        }
        sum[y]++, cnt++;
    }
    void remove(int k)
    {
        right[left[k]] = right[k], left[right[k]] = left[k];
        for (int i = down[k]; i != k; i = down[i])
            for (int j = right[i]; j != i; j = right[j])
            {
                down[upper[j]] = down[j];
                upper[down[j]] = upper[j];
                sum[col[j]]--;
            }
    }
    void resume(int k)
    {
        right[left[k]] = k, left[right[k]] = k;
        for (int i = down[k]; i != k; i = down[i])
            for (int j = right[i]; j != i; j = right[j])
            {
                down[upper[j]] = j;
                upper[down[j]] = j;
                sum[col[j]]++;
            }
    }
    int A()
    {
        int dis = 0;
        for (int i = right[0]; i != 0; i = right[i])
            vis[i] = 0;
        for (int i = right[0]; i != 0; i = right[i])
            if (!vis[i])
            {
                dis++, vis[i] = 1;
                for (int j = down[i]; j != i; j = down[j])
                    for (int k = right[j]; k != j; k = right[k])
                        vis[col[k]] = 1;
            }
        return dis;
    }

    void depthFirstSearch(int k)
    {
        // DFS recursively looking for a best
        if (k + A() >= num)
            return;
        if (!right[0]) {num = std::min(k, num); return;}
        int now = right[0];
        for (int i = now; i != 0; i = right[i])
            if (sum[now]>sum[i]) now = i;
        remove(now);
        for (int i = down[now]; i != now; i = down[i])
        {
            for (int j = right[i]; j != i; j = right[j]) remove(col[j]);
            depthFirstSearch(k + 1);
            for (int j = left[i]; j != i; j = left[j]) resume(col[j]);
        }
        resume(now);
    }
}dlx;

int width, height, piecesCnt, x1, y1, x2, y2;

int main()
{
    int caseCounter;
    scanf("%d", &caseCounter);
    while (caseCounter--)
    {
        scanf("%d %d %d", &width, &height, &piecesCnt);
        dlx.reset(piecesCnt, width * height);
        for (int i = 1; i <= piecesCnt; i++)
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            for (int j = x1; j <x2; j++)
                for (int k = y1; k < y2; k++)
                    dlx.insert(i, j * height + k + 1);
        }
        dlx.depthFirstSearch(0);
        if (dlx.num <= piecesCnt)
            printf("%d\n", dlx.num);
        else
            printf("-1\n");
    }
    return 0;
}
