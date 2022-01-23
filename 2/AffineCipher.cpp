#include<bits/stdc++.h>

using namespace std;

string Encrypt(string plainText,int k1,int k2)
{
    string cipherText="";
    for(int i=0 ; i<plainText.length() ; ++i)
    {
        cipherText += (((plainText[i]-'a')*k1 + k2)%26) + 'a';  
    }
    cout<<"Encrypted Text: "<<cipherText<<endl;
    return cipherText;
}

void Decrypt(string cipherText,int k1,int k2)
{
    string plainText="";
    for(int i=0 ; i<cipherText.length() ; ++i)
    {
        plainText += (((((cipherText[i]-'a')+k2)*k1)%26) + 'a');  
    }
    cout<<"Decrypted Text: "<<plainText<<endl;
}

int MulInverse(int a,int b)
{
    int r1=max(a,b),r2=min(a,b),t1=0,t2=1;
    int q,r,t;
    while(r2>0)
    {
        q = r1/r2;
        r = r1 - q*r2;
        r1=r2;
        r2=r;
        t=t1-q*t2;
        t1=t2;
        t2=t;
    }
    if(r1!=1)
        return -1;
    else
    {
        if(t1<0)
        {
            t1+=26;
            
        }
        return t1;
    }
}

int main()
{
    int n=26,k1,k2;
    string pt;
    cout<<"enter your msg: ";
    cin>>pt;
    cout<<"enter k1: ";
    cin>>k1;
    cout<<"enter k2: ";
    cin>>k2;
    while(MulInverse(k1,n)==-1)
    {
        cout<<"Multiplicative Inverse is not possible for key = "<<k1<<endl;
        cout<<"enter k1: ";
        cin>>k1;
    }
    string cipherText=Encrypt(pt,k1,k2);
    k1=MulInverse(k1,n); //decryption key will be multiplicative inverse of k1
    k2 = n - k2;//decryption key will be additive inverse of k2
    Decrypt(cipherText,k1,k2);
    return 0;
}