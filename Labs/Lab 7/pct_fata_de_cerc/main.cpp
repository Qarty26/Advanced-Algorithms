#include <iostream>
#include <vector>

using namespace std;

struct Punct {
    int x, y;
};

double determinant(Punct A, Punct B, Punct C, Punct P) {

    double a = A.x * A.x + A.y * A.y;
    double b = B.x * B.x + B.y * B.y;
    double c = C.x * C.x + C.y * C.y;
    double p = P.x * P.x + P.y * P.y;

    double det =
            (A.x - P.x) * (B.y - P.y) * (c - p)
            + (B.x - P.x) * (C.y - P.y) * (a - p)
            + (C.x - P.x) * (A.y - P.y) * (b - p)
            - (C.x - P.x) * (B.y - P.y) * (a - p)
            - (B.x - P.x) * (A.y - P.y) * (c - p)
            - (A.x - P.x) * (C.y - P.y) * (b - p);

    return det;
}


int main() {
    Punct A, B, C;
    int xi,yi;
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;

    int m;
    cin >> m;
    vector<Punct> points;

    for (int i = 0; i < m; ++i) {
        cin>>xi>>yi;
        points.push_back(Punct{xi,yi});
    }

    for (int i = 0; i < m; ++i) {
        double det = determinant(A, B, C, points[i]);

        if (det > 0) {
            cout << "INSIDE" << endl;
        } else if (det < 0) {
            cout << "OUTSIDE" << endl;
        } else {
            cout << "BOUNDARY" << endl;
        }
    }

    return 0;
}