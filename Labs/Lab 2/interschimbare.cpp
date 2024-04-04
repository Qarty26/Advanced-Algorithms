#include <iostream>
#include <vector>

using namespace std;

int main() {

    int l;
    cin>>l;
    string c1,c2;
    cin>>c1>>c2;
    int twistIndex;
    cin>>twistIndex;

    for(int i=twistIndex; i<l;i++)
    {
        swap(c1[i],c2[i]);
    }

    cout<<c1<<endl<<c2;

    return 0;
}
