#include <iostream>

using namespace std;

class DiagonalMatrix
{
    private:
        int *A;
        int n;
    public:
        DiagonalMatrix(int n)
        {
            this->n = n;
            A = new int[n];
        }

        ~DiagonalMatrix()
        {
            delete []A;
        }

        void setVal(int i, int j, int val);
        int getVal(int i, int j);
        void display(void);
        int getDimension(void) { return n;}
};

void DiagonalMatrix::setVal(int i, int j, int x) {
    if (i == j)
        A[i - 1] = x;
}

int DiagonalMatrix::getVal(int i, int j) {
    if (i == j)
        return A[i - 1];

    return 0;
}

void DiagonalMatrix::display(void) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                cout << A[i - 1] << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    int d;
    int x;

    cout << "Enter dimension\r\n";
    cin >> d;

    DiagonalMatrix dm(d);

    cout << "Enter all elements\r\n";
    for (int i = 1; i <= d; i++) {
        for (int j = 1; j <= d; j++) {
            cin >> x;
            dm.setVal(i, j, x);
        }
    }

    dm.display();

    return 0;
}
