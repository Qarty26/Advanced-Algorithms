#include <iostream>
#include <vector>

using namespace std;

vector<pair<int,int>> slice(const vector<pair<int,int>>& vec, int start, int end) {
    vector<pair<int,int>> result;
    for (int i = start; i <= end; ++i) {
        result.push_back(vec[i]);
    }
    return result;
}

bool X_Monotone(vector<pair<int,int>> points)
{
    int minn = 0, maxx = 0;
    for(int i=0; i<points.size(); i++)
    {
        if(points[i].first < points[minn].first)
            minn=i;

        if(points[i].first > points[maxx].first)
            maxx=i;
    }

    vector<pair<int,int>> leftBrench, rightBrench;

    if(minn < maxx)
    {
        for(int i=minn; i<=maxx; i++)
            rightBrench.push_back(points[i]);

        for(int i=minn; i>=0; i--)
            leftBrench.push_back(points[i]);

        for(int i=points.size()-1; i>=maxx; i--)
            leftBrench.push_back(points[i]);


//        cout<<"left"<<endl;
//        for(auto x: leftBrench)
//            cout<<x.first<<" "<<x.second<<endl;
//
//
//        cout<<"right"<<endl;
//        for(auto x: rightBrench)
//            cout<<x.first<<" "<<x.second<<endl;
    }
    else
    {
        for(int i=minn; i>=maxx; i--)
            rightBrench.push_back(points[i]);

        for(int i = minn; i<points.size(); i++)
            leftBrench.push_back(points[i]);

        for(int i=0; i<=maxx; i++)
            leftBrench.push_back(points[i]);
    }

    for(int i=0; i<leftBrench.size()-1;i++)
        if(leftBrench[i].first > leftBrench[i+1].first)
            return false;

    for(int i=0; i<rightBrench.size()-1;i++)
        if(rightBrench[i].first > rightBrench[i+1].first)
            return false;


    return true;
}

bool Y_Monotone(vector<pair<int,int>> points)
{
    int minn = 0, maxx = 0;
    for(int i=0; i<points.size(); i++)
    {
        if(points[i].second < points[minn].second)
            minn=i;

        if(points[i].second > points[maxx].second)
            maxx=i;
    }

    vector<pair<int,int>> leftBrench, rightBrench;

    if(minn < maxx)
    {
        for(int i=minn; i<=maxx; i++)
            rightBrench.push_back(points[i]);

        for(int i=minn; i>=0; i--)
            leftBrench.push_back(points[i]);

        for(int i=points.size()-1; i>=maxx; i--)
            leftBrench.push_back(points[i]);

    }
    else
    {
        for(int i=minn; i>=maxx; i--)
            rightBrench.push_back(points[i]);

        for(int i = minn; i<points.size(); i++)
            leftBrench.push_back(points[i]);

        for(int i=0; i<=maxx; i++)
            leftBrench.push_back(points[i]);
    }

    for(int i=0; i<leftBrench.size()-1;i++)
        if(leftBrench[i].second > leftBrench[i+1].second)
            return false;

    for(int i=0; i<rightBrench.size()-1;i++)
        if(rightBrench[i].second > rightBrench[i+1].second)
            return false;

    return true;
}


int main() {

    int n,x,y;
    vector<pair<int,int>> points;
    cin>>n;

    for(int i=0; i<n; i++)
    {
        cin>>x>>y;
        points.push_back({x,y});
    }

    if(X_Monotone(points))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    if(Y_Monotone(points))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    return 0;
}
