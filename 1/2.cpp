#include<bits/stdc++.h>

using namespace std;

string encrypt(string plainText, map<char,char> key)
{
    string cipherText = "";
    for(int i=0 ; i<plainText.length() ; ++i)
    {
        cipherText += key[plainText[i]];
    }
    cout<<"Cipher Text : "<<cipherText<<endl;
    return cipherText;
}

void decrypt(string cipherText, map<char,char> key)
{
    string plainText = "";
    for(int i=0 ; i<cipherText.length() ; ++i)
    {
        plainText += key[cipherText[i]];
    }
    cout<<"Decrypted Text : "<<plainText<<endl;
}

map<char,char> decryptionKey(map<char,char> key)
{
    map<char,char> dkey;
    for(int i=0 ; i<26 ; ++i)
    {
        dkey.insert(make_pair(key['a'+i],('a'+i)));
    }
    return dkey;
}

int main()
{
    //this is a random key
    map<char,char> key{
                        {'a','y'},{'b','z'},{'c','x'},{'d','w'},{'e','v',},
                        {'f','u'},{'g','t'},{'h','s'},{'i','r'},{'j','q'},
                        {'k','p'},{'l','n'},{'m','o'},{'n','m'},{'o','l'},{'p','k'},
                        {'q','j'},{'r','i'},{'s','h'},{'t','g'},{'u','f'},
                        {'v','e'},{'w','d'},{'x','c'},{'y','a'},{'z','b'},
                      };
    string plainText;
    cin>>plainText;
    cout<<"Original Message : "<<plainText<<endl;
    string cipherText = encrypt(plainText,key);
    key = decryptionKey(key);
    decrypt(cipherText,key);
    return 0;
}