#include<bits/stdc++.h>

using namespace std;

int gcdUsingEEA(int a,int b)
{
    int r1 = std::max(a, b), r2 = std::min(a, b);
    int q, r;
    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
    }
    return r1;
}

int multiplicativeInverse(int a, int b)
{
    int r1 = std::max(a, b), r2 = std::min(a, b), t1 = 0, t2 = 1;
    int q, r, t;
    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }
    if (r1 != 1)
        return -1;
    else
    {
        if (t1 < 0)
        {
            t1 += b;
        }
        return t1;
    }
}

int squareAndMultiply(int a, int b, int n)
{
    int z = 1;
    bitset<16> b_(b); //convert to 16bit binary number
    string binary = b_.to_string();
    for (int i = 0; i < binary.length(); ++i)
    {
        z = (z * z) % n;
        if (binary[i] == '1')
            z = (z * a) % n;
    }
    return z;
}