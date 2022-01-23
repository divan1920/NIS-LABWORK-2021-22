//Play-Fair Cipher

/** Some assumption in order to simplify implementation

-> We only encounter text with even lenght
-> there is no two consecutive same letter

---------------------------------------------------------**/
#include <bits/stdc++.h>
#define N 5
using namespace std;

void GenerateKey(string k1,char key[N][N])
{
    pair<char,bool> alphabets[26];
    for(int i=0 ; i<26  ; ++i)
    {
        alphabets[i] = make_pair('a'+i,true);
    }
    int k=0,r=0;
    for(int i=0 ; i<N ; ++i)
    {
        for(int j=0 ; j<N ; ++j)
        {
            if(k<k1.length())
            {
                key[i][j] = k1[k];
                int m = k1[k] - 'a'; 
                
                if(k1[k] == 'i' || k1[k] == 'j')
                {
                    alphabets[9].second = false;
                    alphabets[8].second = false;
                }
                alphabets[m].second = false;
                k++;
            }
            else
            {
                if(r<26 && alphabets[r].second)
                {
                    key[i][j] = alphabets[r].first;
                    alphabets[r].second = false;
                    if(r==8)
                    {
                        alphabets[++r].second = false;
                    }
                }
                else
                {
                    j--; //When we do not put any char in key because it already has that char
                }
                r++;
            }
        }
    }
}

pair<int,int> search(char ch,char key[N][N])
{
    if(ch=='j')
        ch='i';
    pair<int,int> index;
    for(int i=0 ; i<N ; ++i)
        for(int j=0 ; j<N ; ++j)
        {
            if(key[i][j] == ch)
                index = make_pair(i,j);
        }
    return index;
}

string Encryption(char key[N][N] , string plainText)
{
    string cipherText="";
    pair<int,int> index1,index2;       
    for(int i=0 ; i<plainText.length() ; i+=2)
    {
        index1 = search(plainText[i],key);
        index2 = search(plainText[i+1],key);
        //same row
        if(index1.first==index2.first)
        {
            index1.second = (index1.second+1) % N;
            index2.second = (index2.second+1) % N;
            cipherText += key[index1.first][index1.second];
            cipherText += key[index2.first][index2.second];
        }
        //same column
        else if(index1.second==index2.second)
        {
            index1.first = (index1.first+1) % N;
            index2.first = (index2.first+1) % N;
            cipherText += key[index1.first][index1.second];
            cipherText += key[index2.first][index2.second];
        }
        //nothing same
        else
        {
            cipherText += key[index1.first][index2.second];
            cipherText += key[index2.first][index1.second];
        }
    }
    return cipherText;
}

string Decryption(char key[N][N], string cipherText)
{
    string plainText="";
    pair<int,int> index1,index2;       
    for(int i=0 ; i<cipherText.length() ; i+=2)
    {
        index1 = search(cipherText[i],key);
        index2 = search(cipherText[i+1],key);
        //same row
        if(index1.first==index2.first)
        {
            index1.second--;
            index2.second--;
            if(index1.second < 0)
                index1.second+=N;
            if(index2.second < 0)
                index2.second+=N;
            index2.second %=N;
            index1.second %=N;
            plainText += key[index1.first][index1.second];
            plainText += key[index2.first][index2.second];
        }
        //same column
        else if(index1.second==index2.second)
        {
            index1.first--;
            index2.first--;
            if(index1.first < 0)
                index1.first+=N;
            if(index2.first < 0)
                index2.first+=N;
            index2.first %=N;
            index1.first %=N;
            plainText += key[index1.first][index1.second];
            plainText += key[index2.first][index2.second];
        }
        //nothing same
        else
        {
            plainText += key[index1.first][index2.second];
            plainText += key[index2.first][index1.second];
        }
    }
    return plainText;
}

void show(char key[N][N])
{
    for(int i=0 ; i<N ; ++i)
    {
        for(int j=0; j<N ; ++j)
        {
            cout<<key[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    string k1,pt;
    cout<<"Enter Key Text: ";
    getline(cin,k1);
    cout<<"enter your msg: ";
    cin>>pt;
    char key[N][N];
    GenerateKey(k1,key);
    show(key);
    // string cipherText = Encryption(key,pt);
    // cout<<"Encrypted Text: "<<cipherText<<endl;
    // string decryptedText = Decryption(key , cipherText);
    // cout<<"Decrypted Text: "<<decryptedText<<endl;
    return 0;
}
