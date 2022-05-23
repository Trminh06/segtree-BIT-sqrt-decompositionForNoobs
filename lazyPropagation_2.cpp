/*
Bạn được cho một mảng gồm  số nguyên. Nhiệm vụ của bạn là xử lí 2 loại truy vấn:
Loại 1 có dạng    : Tăng giá trị của các phần tử từ vị trí thứ  đến vị trí thứ  trong dãy lên  đơn vị ()
Loại 2 có dạng   : In ra phần tử lớn nhất của dãy từ phần tử thứ  đến phần tử thứ  ()
Với mỗi truy vấn loại 2, hãy in ra câu trả lời trên một dòng.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll oo = 1e18;
const int maxn = 5e4 + 1;
int n;
struct segnode{
    ll val, lz;
} s[4 * maxn];
void lazyPropagation(int id){
    s[2 * id].val += s[id].lz;
    s[2 * id + 1].val += s[id].lz;
    s[2 * id].lz += s[id].lz;
    s[2 * id + 1].lz += s[id].lz;
    s[id].lz = 0;
}
void build(int id, int l, int r){
    if (l == r){
        s[id].val = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    s[id].val = max(s[2 * id].val, s[2 * id + 1].val);
}
void update(int id, int l, int r, int u, int v, int x){
    //lazyPropagation(id, l, r);
    if (r < u || l > v)
        return;
    if (l >= u && r <= v){
        s[id].lz += x;
        s[id].val += x;
        //lazyPropagation(id, l, r);
        return;
    }
    lazyPropagation(id);
    int mid = (l + r) >> 1;
    update(2 * id, l, mid, u, v, x);
    update(2 * id + 1, mid + 1, r, u, v, x);
    s[id].val = max(s[2 * id].val, s[2 * id + 1].val);
}
ll getMax(int id, int l, int r, int u, int v){
    //lazyPropagation(id, l, r);
    if (r < u || l > v)
        return -oo;
    if (l >= u && r <= v)
        return s[id].val;
    int mid = (l + r) >> 1;
    lazyPropagation(id);
    return max(getMax(2 * id, l, mid, u, v), getMax(2 * id + 1, mid + 1, r, u, v));
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q, x, l, r;
    cin >> n >> q;
    for(int i = 1; i <= 4 * n; ++i)
        s[i].lz = 0;
    build(1, 1, n);
    while (q--){
        cin >> x;
        if (x){
            cin >> l >> r;
            cout << getMax(1, 1, n, l, r) << "\n";
        } else {
            cin >> l >> r >> x;
            update(1, 1, n, l, r, x);
        }
    }
    return 0;
}
