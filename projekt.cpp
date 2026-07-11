#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> g;
vector<int> dist;
int n, m;
int s;

void cin_graf()
{
    cin >> n >> m;
    g.resize(n + 1);
    dist.resize(n + 1, -1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

void bfs(int a) {
    queue<int> q;
    q.push(a);
    dist[a] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << endl;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

void print() {
    for (int i = 1; i < n; i++) {
        cout << i << " : ";
        for (int j = 0; j < g[i].size(); j++)
            cout << g[i][j] << " ";
        cout << endl;
    }
}
void bfs_vaxod() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}
int k;
void bunker() {
    cin >> n >> k;
    g.resize(n + 1);
    dist.resize(n + 1, -1);
    for (int i = 0; i < k; i++) {
        int exit;
        cin >> exit;
        dist[exit] = 0;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bfs_vaxod();
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
}

vector<vector<int>> ves;


void bfs_ves() {
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            int w = ves[u][i];

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (w == 0) {
                    dq.push_front(v);
                }
                else {
                    dq.push_back(v);
                }
            }
        }
    }
}

int ves_reb() {
    cin >> n >> m >> s;
    g.resize(n + 1);
    ves.resize(n + 1);
    dist.resize(n + 1, 10 * 100);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(v);
        ves[u].push_back(w);
        g[v].push_back(u);
        ves[v].push_back(w);
    }
    bfs_ves();
    for (int i = 1; i <= n; i++) {
        if (dist[i] == 10 * 100) {
            cout << -1 << " ";
        }
        else {
            cout << dist[i] << " ";
        }
    }

    return 0;
}

struct SegmentTree
{
    vector<int> tree_max;
    vector<int> tree_idx;
    vector<int> arr;
    vector<int> tree;
    int n;
    void init_task1(int size) {
        n = size;
        tree.resize(4 * n + 5, 0);
    }
    void update(int index, int value) {
        update(index, value, 1, 1, n);
    }
    void update(int index, int value, int node, int l, int r) {
        if (l == r) {
            tree[node] = value;
            return;
        }

        int mid = (l + r) / 2;
        if (index <= mid)
            update(index, value, node * 2, l, mid);
        else
            update(index, value, node * 2 + 1, mid + 1, r);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
    int query(int left, int right) {
        return query(1, 1, n, left, right);
    }
    int query(int node, int l, int r, int left, int right) {
        if (left > r || right < l) {
            return 0;
        }
        if (left <= l && r <= right) {
            return tree[node];
        }
        int mid = (l + r) / 2;
        int left_sum = query(node * 2, l, mid, left, right);
        int right_sum = query(node * 2 + 1, mid + 1, r, left, right);
        return left_sum + right_sum;
    }
    void init_maks(int size) {
        n = size;
        tree_max.resize(4 * n);
        tree_idx.resize(4 * n);
    }
    void build_maks(int node, int l, int r, vector<int>& arr) {
        if (l == r) {
            tree_max[node] = arr[l];
            tree_idx[node] = l;
            return;
        }
        int mid = (l + r) / 2;
        build_maks(node * 2, l, mid, arr);
        build_maks(node * 2 + 1, mid + 1, r, arr);
        if (tree_max[node * 2] > tree_max[node * 2 + 1]) {
            tree_max[node] = tree_max[node * 2];
            tree_idx[node] = tree_idx[node * 2];
        }
        else {
            tree_max[node] = tree_max[node * 2 + 1];
            tree_idx[node] = tree_idx[node * 2 + 1];
        }
    }
    void query_maks(int left, int right, int& max_val, int& idx) {
        query_maks(1, 1, n, left, right, max_val, idx);
    }
    void query_maks(int node, int l, int r, int left, int right, int& max_val, int& idx) {
        if (left > r || right < l) {
            max_val = -1e9;
            idx = -1;
            return;
        }
        if (left <= l && r <= right) {
            max_val = tree_max[node];
            idx = tree_idx[node];
            return;
        }
        int mid = (l + r) / 2;
        int left_max, left_idx, right_max, right_idx;
        query_maks(node * 2, l, mid, left, right, left_max, left_idx);
        query_maks(node * 2 + 1, mid + 1, r, left, right, right_max, right_idx);
        if (left_max > right_max) {
            max_val = left_max;
            idx = left_idx;
        }
        else {
            max_val = right_max;
            idx = right_idx;
        }
    }
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    void init_NOD(int size) {
        n = size;
        tree.resize(4 * n);
    }
    void build_NOD(int node, int l, int r, vector<int>& arr) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build_NOD(node * 2, l, mid, arr);
        build_NOD(node * 2 + 1, mid + 1, r, arr);
        tree[node] = gcd(tree[node * 2], tree[node * 2 + 1]);
    }

    void update_NOD(int index, int value) {
        update_NOD(1, 1, n, index, value);
    }

    void update_NOD(int node, int l, int r, int index, int value) {
        if (l == r) {
            tree[node] = value;
            return;
        }

        int mid = (l + r) / 2;
        if (index <= mid) {
            update_NOD(node * 2, l, mid, index, value);
        }
        else {
            update_NOD(node * 2 + 1, mid + 1, r, index, value);
        }
        tree[node] = gcd(tree[node * 2], tree[node * 2 + 1]);
    }

    int query_NOD(int left, int right) {
        return query_NOD(1, 1, n, left, right);
    }

    int query_NOD(int node, int l, int r, int left, int right) {
        if (left > r || right < l) {
            return 0;
        }
        if (left <= l && r <= right) {
            return tree[node];
        }
        int mid = (l + r) / 2;
        int left_res = query_NOD(node * 2, l, mid, left, right);
        int right_res = query_NOD(node * 2 + 1, mid + 1, r, left, right);

        return gcd(left_res, right_res);
    }
};

void Sum_taske() {
    int n, k;
    cin >> n >> k;
    SegmentTree st;
    st.init_task1(n);
    for (int i = 0; i < k; i++) {
        char type;
        cin >> type;

        if (type == 'A') {
            int index, value;
            cin >> index >> value;
            st.update(index, value);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << '\n';
        }
    }
}

void Maks() {
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    SegmentTree st;
    st.init_maks(n);
    st.build_maks(1, 1, n, arr);

    int k;
    cin >> k;

    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;

        int max_val, idx;
        st.query_maks(l, r, max_val, idx);

        cout << max_val << " " << idx << '\n';
    }
}

void NOD() {
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    SegmentTree st;
    st.init_NOD(n);
    st.build_NOD(1, 1, n, arr);

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;

        if (type == 'u') {
            int index, value;
            cin >> index >> value;
            st.update_NOD(index, value);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << st.query_NOD(l, r) << " ";
        }
    }
    cout << endl;
}

int main() {
    // Sum_taske();   
    // Maks();       
    NOD();

    return 0;
}
// посмотрим что выйдет 