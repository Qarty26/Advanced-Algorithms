#include <iostream>
#include <vector>
using namespace std;

int getPos(int x1, int y1, int x2, int y2, int x3, int y3)
{
    long long where = 1LL * (x2-x1) * (y3-y1) - 1LL* (y2 - y1) * (x3 - x1);

    if(where > 0)
        return 0;
    else if(where < 0)
        return 1;
    else return 2;
}

int main() {

    int n,x,y;
    vector<int> cont(3,0);
    vector<pair<int,int>> coords;
    cin>>n;

    for(int i=0 ; i<n;i++)
    {
        cin>>x>>y;
        coords.push_back({x,y});
    }
    coords.push_back(coords[0]);

    for(int i=2; i<coords.size(); i++)
    {
        int pos = getPos(coords[i-2].first,coords[i-2].second,
               coords[i-1].first,coords[i-1].second,
               coords[i].first,coords[i].second);
        cont[pos]++;
    }


    cout<<cont[0]<<" "<<cont[1]<<" "<<cont[2];

    return 0;
}
