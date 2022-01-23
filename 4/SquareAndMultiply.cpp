#include <bits/stdc++.h>

using namespace std;

int squareAndMultiply(int a, int b, int n)
{
    cout<<"Bit Value\tSquare\tMultiply\n";
    int z = 1;
    bitset<16> b_(b); //convert to 16bit binary number
    string binary = b_.to_string();
    for (int i = 0; i < binary.length(); ++i)
    {
        cout<<binary[i]<<"\t"<<z<<"^2 mod "<<n<<" = ";
        z = (z * z) % n;
        cout<<z<<"\t";
        if (binary[i] == '1')
        {
            cout<<z<<"x"<<a<<" mod "<<n<<" = ";
            z = (z * a) % n;
            cout<<z;
        }
        else
        {
            cout<<"X";
        }
        cout<<endl;
    }
    return z;
}

int main()
{
    int a, b, n;
    cin >> a >> b >> n;
    int ans = squareAndMultiply(a, b, n);
    cout << "a^b mod n: " <<ans << endl;
    return 0;
}