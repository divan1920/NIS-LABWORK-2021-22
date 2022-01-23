#include<bits/stdc++.h>

using namespace std;
string encrypt(string plainText,int k);
string decrypt(string cipherText, int k);
void cryptanalysis(string cipherText);

string encrypt(string plainText,int k)
{
    string cipherText="";
    for(int i=0 ; i<plainText.length() ; ++i)
    {
        cipherText[i] = plainText[i] - 'a';
        cipherText[i] = (cipherText[i]+k) % 26;
        cipherText += (cipherText[i] + (int)'a');
    }
    cout<<"cipher text : "<<cipherText<<endl;
    return cipherText;
}

string decrypt(string cipherText, int k)
{
    string plainText="";
    for(int i=0 ; i<cipherText.length() ; ++i)
    {
        plainText[i] = cipherText[i] - 'a';
        plainText[i] = plainText[i] - k;
        if(plainText[i] < 0) 
        {
            plainText[i] += 26;
        }
        plainText[i] %= 26;
        plainText += (plainText[i] + (int)'a');
    }
    cout<<"DecryplainTexted Text : "<<plainText<<endl;
    return plainText;
}

//Here number of keys possible are 26 i.e 0 to 25
void cryptanalysis(string cipherText)
{
    string plainText="";
    for(int k = 0 ; k<26 ; ++k)
    {
        for(int i=0 ; i<cipherText.length() ; ++i)
        {
            plainText[i] = cipherText[i] - 'a';
            plainText[i] = plainText[i] - k;
            if(plainText[i] < 0) 
            {
                plainText[i] += 26;
            }
            plainText[i] %= 26;
            plainText += (plainText[i] + (int)'a');
        }
        cout<<"Key : "<<k<<" Decrypted Text : "<<plainText<<endl;
        plainText="";
    }
}

int main()
{
    string plainText;
    int k;
    cin>>plainText>>k;
    cout<<"Plain Text : "<<plainText<<endl;
    string cipherText = encrypt(plainText,k);
    plainText = decrypt(cipherText,k);
    cryptanalysis(cipherText);
    return 0;
}