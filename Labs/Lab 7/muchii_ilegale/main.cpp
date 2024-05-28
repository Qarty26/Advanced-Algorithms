#include <iostream>
#include <vector>

using namespace std;

struct Punct {
    int x, y;
};

double determinant(Punct A, Punct B, Punct C, Punct P) {

    double det = (-1) * 5 * (
            (B.x - A.x) * (C.y - A.y) * (P.x * P.x + P.y * P.y - A.x * A.x - A.y * A.y) +
            (C.x - A.x) * (P.y - A.y) * (B.x * B.x + B.y * B.y - A.x * A.x - A.y * A.y) +
            (P.x - A.x) * (B.y - A.y) * (C.x * C.x + C.y * C.y - A.x * A.x - A.y * A.y) -
            (C.x - A.x) * (B.y - A.y) * (P.x * P.x + P.y * P.y - A.x * A.x - A.y * A.y) -
            (B.x - A.x) * (P.y - A.y) * (C.x * C.x + C.y * C.y - A.x * A.x - A.y * A.y) -
            (P.x - A.x) * (C.y - A.y) * (B.x * B.x + B.y * B.y - A.x * A.x - A.y * A.y)
    );

    return det;
}
int main() {


    Punct A,B,C,D;
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;

    cout<<"AC: ";
    if(determinant(A,B,C,D) > 0)
        cout<<"ILLEGAL"<<endl;
    else cout<<"LEGAL"<<endl;


    cout<<"BD: ";
    if(determinant(B,C,D,A) > 0)
        cout<<"ILLEGAL"<<endl;
    else cout<<"LEGAL"<<endl;

    return 0;
}
