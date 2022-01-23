#include<bits/stdc++.h>
using namespace std;

string Encrypt(string plainText,int k)
{
    string cipherText="";
    for(int i=0 ; i<plainText.length() ; ++i)
    {
        cipherText += (((plainText[i]-'a')*k)%26) + 'a';  
    }
    cout<<"Encrypt: "<<cipherText<<endl;
    return cipherText;
}

void Decrypt(string cipherText,int k)
{
    string plainText="";
    for(int i=0 ; i<cipherText.length() ; ++i)
    {
        plainText += (((cipherText[i]-'a')*k)%26) + 'a';  
    }
    cout<<"Decrypt: "<<plainText<<endl;
}

int MultiplicativeInverse(int a,int b)
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
    int k,n=26;
    string pt;
    cout<<"enter your msg: ";
    cin>>pt;
    cout<<"enter your key: ";
    cin>>k;
    while(MultiplicativeInverse(k,n)==-1)
    {
        cout<<"Multiplicative Inverse is not possible for key = "<<k<<endl;
        cout<<"enter other key: ";
        cin>>k;
    }  
    string cipherText=Encrypt(pt,k);
    k=MultiplicativeInverse(k,n);
    Decrypt(cipherText,k);
    return 0;
}