#include <bits/stdc++.h>

using namespace std;

string GenerateKey(int k1,string plainText)
{
    string key="";
    key+=(char)('a'+k1);
    for(int i=0 ; i<plainText.length() ; ++i)
    {
        key+=plainText[i];
    }
    return key;
}

string Encryption(string key , string plainText)
{
    string cipherText="";
    for(int i=0 ; i<plainText.length() ; ++i)
    {
        cipherText += ((plainText[i] - 'a') + (key[i] -'a')) % 26;
        cipherText[i] = cipherText[i] + 'a';
    }
    return cipherText;
}

string Decryption(string key, string cipherText)
{
    string plainText="";
    for(int i=0 ; i<cipherText.length() ; ++i)
    {
        plainText += ((cipherText[i] - 'a') - (key[i] - 'a'));
        if(plainText[i] < 0)
        {
            plainText[i]+=26;
        }
        plainText[i] %= 26;
        plainText[i] = plainText[i] + 'a';
    }
    return plainText;
}

int main()
{
    int k1;
    string plainText;
    cin>>plainText>>k1;
    string key = GenerateKey(k1,plainText);
    string cipherText = Encryption(key,plainText);
    cout<<cipherText<<endl;
    string decryptedText = Decryption(key , cipherText);
    cout<<decryptedText<<endl;
    return 0;
}
