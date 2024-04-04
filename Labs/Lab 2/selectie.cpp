#include <iostream>
#include<vector>
using namespace std;



int main() {

    vector<pair<double,double>> XRes;
    XRes.push_back({0,0});
    int a,b,c,n;
    double x,sum=0;
    cin>>a>>b>>c;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        double x = rand();
        double res = a * x * x + b * x + c;
        XRes.push_back({x,res});
    }

    for(auto x: XRes)
        sum+=x.second;

    double sum_part = 0;
    cout<<sum_part/sum<<endl;

    for(int i = 1; i<XRes.size();i++)
    {
        sum_part+=XRes[i].second;
        cout<<sum_part/sum<<endl;
    }
    return 0;
}
