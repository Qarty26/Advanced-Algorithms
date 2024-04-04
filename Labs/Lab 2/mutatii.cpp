#include <iostream>
#include <string>

using namespace std;

int main() {

    int nrCrom, nrMut,index;
    string sirCrom;
    cin>>nrCrom>>nrMut>>sirCrom;
    for(int i=0;i<nrMut;i++)
    {
        cin>>index;
        sirCrom[index] = (((sirCrom[index] - '0') + 1) % 2)+'0';
    }

    cout<<sirCrom;

    return 0;
}
