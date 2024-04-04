#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
using namespace std;

int binaryToDecimal(string binaryStr) {
    int decimal = 0;
    int power = 0;

    for (int i = binaryStr.length() - 1; i >= 0; i--) {
        if (binaryStr[i] == '1') {
            decimal += pow(2, power);
        }
        power++;
    }

    return decimal;
}

int main() {

    int a,b,p,m;
    cin>>a>>b>>p>>m;
    string op;
    int l = ceil(log2((b-a) * pow(10,p)));
    double d = (b-a)/(pow(2,l));

    for(int i=0; i<m;i++)
    {
        cin>>op;
        if(op=="TO")
        {
            double x;
            cin>>x;
            int d_multiplicator = 0;
            while(true)
            {
                if(a + d*d_multiplicator <= x && x < a + d*(d_multiplicator+1))
                    break;
                else d_multiplicator++;


            }
            bitset<sizeof(int) * 8> binary(d_multiplicator);
            cout << binary.to_string().substr(sizeof(int) * 8 - l) << endl;
        }
        else if(op == "FROM")
        {
            string num;
            cin>>num;
            int nr = binaryToDecimal(num);
            double final = a+nr*d;
            cout<<final<<endl;
        }
    }

    return 0;
}
