#include "../functions.h"
#define point pair<int,int>


int a,b,p;

point addP(int scalar,point p1,int a,int p)
{
    if(scalar==2)
    {
        int x1 = p1.first,y1=p1.second;
        int lamda = (((3*power(x1,2))+a)*multiplicativeInverse(2*y1,p)) % p;
        int x3 = doModP((power(lamda,2) - 2*x1), p);
        int y3 = doModP((lamda*(x1-x3)-y1),p);
        cout<<"x3: "<<x3<<" y3:"<<y3<<endl;
        return make_pair(x3,y3);
    }
}

vector<point> pointGeneration(int a,int b,int p)
{
    vector<point> points;
    for(int x=0; x<p ; ++x)
    {
        int w = (power(x,3) +(a*x) +b) % p;
        int rem = squareAndMultiply(w,((p-1)/2),p);
        if(rem == 1)
        {
            while(sqrt(w)*sqrt(w) != w)
                w+=p;
            points.push_back(make_pair(x,sqrt(w)));
            points.push_back((make_pair(x, doModP(-sqrt(w), p))));
        }
        //point on the curve
        else if(rem == 0)
            points.push_back(make_pair(x,0));
    }
    return points;
}

int main()
{
    cin>>a>>b>>p;
    vector<point> points = pointGeneration(a,b,p);
    //addP(2,make_pair(1,4),a,p);
    //printing points
    for(int i=0 ; i<points.size() ; ++i)
    {
        cout<<"("<<points[i].first<<","<<points[i].second<<")"<<endl;
    }
    return 0;
}