#include "functions.h"

/**************************************************************************************
--> This is code for elgamal cryptosystem.
 
--> In this code I implemented functions for encyption and decryption using rules of elgamal cryptosystem. 

--> I also implemented functions for finding primitive roots and group <zp*,x>.  
 
--> There is also function for key generation which generates private and public key.

**Input** 

--> We need to input one bigger prime number. Here note bigger the number bigger the msg you can encrypt.
    If msg is greater than prime number used than program may give wrong output.
--> I noticed one thing here that you need to enter prime numer such that primeNumber>(your msg) 

**Output**

--> There is encrypted and decrypted msg with other parameter like key.  

 ****************************************************************************************/

struct Key
{
    int e1, e2, p, d;
};

vector<int> findGroupZp(int p)
{
    vector<int> zp; //it is Zp*
    for (int i = 1; i < p; ++i)
    {
        if (multiplicativeInverse(i, p) != -1)
        {
            zp.push_back(i);
        }
    }
    return zp;
}

int findPrimitiveRoot(int prime)
{
    int a;
    vector<int> groupZp = findGroupZp(prime);
    //until we find primitive root
    for (int j = 0; j < groupZp.size(); ++j)
    {
        //finding element of zp*
        a = groupZp[j];
        for (int i = 2; i <= (prime - 1); ++i)
        {
            int m = (squareAndMultiply(a, i, prime));
            if (i == (prime - 1) && m == 1)
            {
                return a;
            }
            else if (m == 1)
            {
                break;
            }
        }
    }
    return 0;
}

Key generateKey()
{
    int prime;
    Key keys;
    while (1)
    {
        cout << "Enter a large prime number: ";
        cin >> prime;
        if (isPrime(prime))
            break;
    }
    vector<int> groupZp = findGroupZp(prime);
    keys.e1 = findPrimitiveRoot(prime);
    int k = 0;
    while (groupZp[k] <= 1 && groupZp[k] > (prime - 2))
    {
        k++;
    }
    keys.d = groupZp[k];
    keys.e2 = squareAndMultiply(keys.e1, keys.d, prime);
    keys.p = prime;
    return keys;
}

pair<int, int> encryption(int msg, int e1, int e2, int p)
{
    vector<int> groupZp = findGroupZp(p);
    int r = groupZp[2];
    cout << "\nr: " << r << endl;
    int c1 = squareAndMultiply(e1, r, p);
    int c2 = ((msg % p) * squareAndMultiply(e2, r, p)) % p;
    return make_pair(c1, c2);
}

int decryption(int c1, int c2, int d, int p)
{
    int c1_d = squareAndMultiply(c1, d, p);
    int c1_inverse = multiplicativeInverse(c1_d, p);

    return (c1_inverse * c2) % p;
}

int main()
{
    Key keys;
    int msg;
    cout << "Enter your msg: ";
    cin >> msg;
    keys = generateKey();
    pair<int, int> encryptedMsg = encryption(msg, keys.e1, keys.e2, keys.p);
    cout << "e1: " << keys.e1 << " e2: " << keys.e2 << " d: " << keys.d << " p: " << keys.p << endl;
    cout << "C1: " << encryptedMsg.first << endl;
    cout << "C2: " << encryptedMsg.second << endl;
    cout << "Decrypted Msg: " << decryption(encryptedMsg.first, encryptedMsg.second, keys.d, keys.p) << endl;

    return 0;
}