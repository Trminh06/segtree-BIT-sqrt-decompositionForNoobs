#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 1;
int n;
ll s[4 * maxn], a[maxn];
void build(int id, int l, int r){
    if (l == r){
        s[id] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    s[id] = s[2 * id] + s[2 * id + 1];
}
ll calc(int id, int l, int r, int u, int v){
    if (r < u || l > v)
        return 0;
    if (l >= u && r <= v)
        return s[id];
    int mid = (l + r) >> 1;
    return calc(2 * id, l, mid, u, v) + calc(2 * id + 1, mid + 1, r, u, v);
}
void update(int id, int l, int r, int pos, int x){
    if (r < pos || l > pos)
        return;
    if (l == r){
        s[id] = x;
        return;
    }
    int mid = (l + r) >> 1;
    update(2 * id, l, mid, pos, x);
    update(2 * id + 1, mid + 1, r, pos, x);
    s[id] = s[2 * id] + s[2 * id + 1];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, 1, n);
    int x, l, r;
    while (q--){
        cin >> x >> l >> r;
        if (x == 1)
            update(1, 1, n, l, r);
        else
            cout << calc(1, 1, n, l, r) << "\n";
    }
    return 0;
}

