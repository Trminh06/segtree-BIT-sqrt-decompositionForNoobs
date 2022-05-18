#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef long long ll;
const int maxn = 2e5 + 1;
const int Bsize = 300;
int n;
pair <int,ll> B[maxn], a[maxn];
void update(int i, int x){
    B[a[i].fi].se -= a[i].se;
    a[i].se = x;
    B[a[i].fi].se += x;
}
ll solve(int l, int r){
    int posL = a[l].fi;
    int posR = a[r].fi;
    if (posL == posR){
        ll sum = 0;
        for(int i = l; i <= r; ++i)
            sum += a[i].se;
        return sum;
    }
    int pos = 0;
    ll sumL = 0;
    ll sumR = 0;
    ll sum = 0;
    for(int i = 1; i <= posL; ++i)
        pos += B[i].fi;
    for(int i = l; i <= pos; ++i)
        sumL += a[i].se;
    for(int i = posL + 1; i < posR; ++i){
        sum += B[i].se;
        pos += B[i].fi;
    }
    for(int i = pos + 1; i <= r; ++i)
        sumR += a[i].se;
    return sum + sumL + sumR;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i)
        cin >> a[i].se;
    int j = 1, cnt = 0;;
    for(int i = 1; i <= n; ++i){
        ++cnt;
        B[j].se += a[i].se;
        B[j].fi = cnt;
        a[i].fi = j;
        if (cnt == Bsize){
            j++;
            cnt = 0;
        }
    }
    int x, l, r;
    while (q--){
        cin >> x >> l >> r;
        if (x == 1)
            update(l, r);
        else{
            cout << solve(l, r) << "\n";
        }
    }
    return 0;
}

