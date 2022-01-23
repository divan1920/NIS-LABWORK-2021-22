#include<bits/stdc++.h>
using namespace std;

int MultiplicativeInverse(int a,int b)
{
    int r1=max(a,b),r2=min(a,b),t1=0,t2=1;
    int q,r,t;
    while(r2>0)
    {
        q = r1/r2;
        t=t1-q*t2;
        r = r1 - q*r2;
        r1=r2;
        r2=r;
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
    int n=26,a=26,inverse;
    //cin>>n>>a;
    while(a!=0)
    {
        if((inverse = MultiplicativeInverse(a,n)) != -1)
            cout<<a<<" ";
        a--;
    }
    // if((inverse = MultiplicativeInverse(n,a)) != -1)
    // {
    //     cout<<"Multiplicative Inverse: "<<inverse<<endl;
    // }
    // else
    // {
    //     cout<<"Multiplicative Inverse not possible";
    // }
    return 0;
}