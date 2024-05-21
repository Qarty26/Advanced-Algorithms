#include <iostream>
#include <cstring>

using namespace std;

string getPos(int x1, int y1, int x2, int y2, int x3, int y3)
{
    long long where = 1LL * (x2-x1) * (y3-y1) - 1LL* (y2 - y1) * (x3 - x1);

    if(where > 0)
        return "LEFT";
    else if(where < 0)
        return "RIGHT";
    else return "TOUCH";
}

int main() {

    int n, x1,x2,x3,y1,y2,y3;

    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>x1>>y1>>x2>>y2>>x3>>y3;
        cout<<getPos(x1,y1,x2,y2,x3,y3)<<endl;
    }
    return 0;
}
