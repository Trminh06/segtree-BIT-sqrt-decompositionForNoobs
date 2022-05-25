#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll oo = 1e18;
const int maxn = 2e5 + 1;
int n;
ll s[maxn << 1];

void update(int p, ll val){
    s[p += n] = val;
    for(p >>= 1; p; p >>= 1)
        s[p] = min(s[p << 1], s[p << 1 | 1]);
}

ll get(int l, int r){
    ll res = oo;
    for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1){
        if (l & 1)
            res = min(res, s[l++]);
        if (r & 1)
            res = min(res, s[--r]);
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q, l, r;
    ll x;
    cin >> n >> q;
    for(int i = 1; i <= n << 1; ++i)
        s[i] = oo;
    for(int i = 1; i <= n; ++i){
        cin >> x;
        update(i, x);
    }
    while (q--){
        cin >> l;
        if (l & 1){
            cin >> l >> r;
            update(l, r);
        } else {
            cin >> l >> r;
            cout << get(l, r) << "\n";
        }
    }
    return 0;
}
