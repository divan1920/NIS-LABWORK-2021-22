#include "../functions.h"
#include <bits/stdc++.h>
using namespace std;

bool isPrime(int num)
{
    if (num <= 1)
        return false;
    for (int i = 2; i <= sqrt(num); ++i)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

vector<int> keyGeneration(int p, int q)
{
    int phi, n, e, d;
    vector<int> keys;
    n = p * q;
    phi = (p - 1) * (q - 1);
    // for (int i = 2; i < phi; ++i)
    // {
    //     if (multiplicativeInverse(i, phi) != -1)
    //     {
    //         e = i;
    //         break;
    //     }
    // }
    e = 19;
    d = multiplicativeInverse(e, phi);
    keys.push_back(e);
    keys.push_back(n);
    keys.push_back(d);
    return keys;
}

int encryption(int msg, int e, int n)
{
    int cipher;
    cipher = squareAndMultiply(msg, e, n);
    return cipher;
}

int decryption(int cipher, int d, int n)
{
    int msg;
    msg = squareAndMultiply(cipher, d, n);
    return msg;
}

int main()
{
    int p, q, e, d, n;
    cout << "Please enter Two numbers: ";
    cin >> p >> q;
    while (true)
    {
        if (isPrime(p) && isPrime(q))
            break;
        else
        {
            cout << "You need to enter prime numbers.\nPlease try again: ";
            cin >> p >> q;
        }
    }
    vector<int> keys;
    keys = keyGeneration(p, q);
    e = keys[0];
    n = keys[1];
    d = keys[2];
    int msg, cipher;
    cout << "Enter Your Msg: ";
    cin >> msg;
    cout << "Encrypted Msg: " << (cipher = encryption(msg, e, n)) << endl;
    cout << "Decrypted Msg: " << decryption(cipher, d, n) << endl;

    return 0;
}
