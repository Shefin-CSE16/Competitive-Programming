// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define sl(n) scanf("%lld", &n)
#define si(n) scanf("%d", &n)
#define sd(n) scanf("%lf", &n)
#define pll pair <ll, ll>
#define pii pair <int, int>
#define mp make_pair
#define pb push_back
#define all(v) v.begin(), v.end()
#define inf (1LL << 62)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; ++i)
#define for0(i, stop) for(ll i = 0; i < stop; ++i)
#define rep1(i, start) for(ll i = start; i >= 1; --i)
#define rep0(i, start) for(ll i = (start-1); i >= 0; --i)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

/***
   * Multiply (7x^2 + 8x^1 + 9x^0) with (6x^1 + 5x^0)
   * ans = 42x^3 + 83x^2 + 94x^1 + 45x^0
   * A = {9, 8, 7}
   * B = {5, 6}
   * V = multiply(A,B)
   * V = {45, 94, 83, 42}
***/

/*** Tricks
   * Use vector < bool > if you need to check only the status of the sum
   * Use bigmod if the power is over same polynomial && power is big
   * Use long double if you need more precision
   * Use long long for overflow
***/
typedef vector <int> vi;
const double PI = 2.0 * acos(0.0);
using cd = complex<double>;

void fft(vector<cd> & a, bool invert = 0)

{
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

void ifft(vector <cd> & p)

{
    fft(p, 1);
}

vi multiply(vi const& a, vi const& b)
{

    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa);
    fft(fb);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    ifft(fa);

    vi result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());

    return result;
}

const ll sz = 5e5 + 10, offset = 5e5;
char s[sz], r[sz];

vi num1[4], num2[4], res[4];

int main()
{
    scanf("%s %s", s, r);

    ll len1 = strlen(s), len2 = strlen(r);

    for0(i, 4)
        num1[i].resize(len1+1,0), num2[i].resize(len2+1+offset,0);

    for(ll i = 0; s[i] != '\0'; i++) {
        if(s[i] == 'A')
            num1[0][i]++;
        else if(s[i] == 'C')
            num1[1][i]++;
        else if(s[i] == 'T')
            num1[2][i]++;
        else
            num1[3][i]++;
    }

    for(ll i = 0; r[i] != '\0'; i++) {

        if(r[i] == 'A')
            num2[0][-i + offset]++;
        else if(r[i] == 'C')
            num2[1][-i + offset]++;
        else if(r[i] == 'T')
            num2[2][-i + offset]++;
        else
            num2[3][-i + offset]++;
    }

    for0(i, 4) res[i] = multiply(num1[i], num2[i]);

    ll ans = inf;
    for(ll i = 0; i <= len1 - len2; i++) {
        ll match = 0;
        for0(j, 4) match += res[j][i+offset];

        ans = min(ans, len2-match);
    }

    cout << ans << EL;

    return 0;
}
