#include <iostream>

using namespace std;

class Element
{
    public:
        int i;
        int j;
        int x;
};

class SparseMatrix
{
    private:
        int m;
        int n;
        int num;
        Element *e;
    public:
        SparseMatrix(int m, int n, int num)
        {
            this->m = m;
            this->n = n;
            this->num = num;
            e = new Element[this->num];
        }

        ~SparseMatrix()
        {
            delete [] e;
        }

        SparseMatrix operator+(SparseMatrix &s);

        friend istream & operator>>(istream &is, SparseMatrix &s);
        friend ostream & operator<<(ostream &os, SparseMatrix &s);
};

SparseMatrix SparseMatrix::operator+(SparseMatrix &s)
{
    int i, j, k;

    if (m != s.m || n != s.n)
        return SparseMatrix(0, 0, 0);

    SparseMatrix *sum = new SparseMatrix(m, n, num + s.num);

    i = 0;
    j = 0;
    k = 0;
    while (i < num && j < s.num)
    {
        if (e[i].i < s.e[j].i)
            sum->e[k++] = e[i++];
        else if (e[i].i > s.e[j].i)
            sum->e[k++] = s.e[j++];
        else
        {
            if (e[i].j < s.e[j].j)
                sum->e[k++] = s.e[i++];
            else if (e[i].j > s.e[j].j)
                sum->e[k++] = s.e[j++];
            else 
            {
                sum->e[k] = e[i];
                sum->e[k++].x = e[i++].x + s.e[j++].x;
            }
        }
    }
    for (;i < s.num; i++) sum->e[k++] = e[i];
    for (;j < s.num; j++) sum->e[k++] = s.e[j];
    sum->num = k;

    return *sum;
}

istream & operator>>(istream &is, SparseMatrix &s)
{
    cout << "Enter non-zero elements" << endl;

    for (int i = 0; i < s.num; i++)
        cin >> s.e[i].i >> s.e[i].j >> s.e[i].x;

    return is;
}

ostream & operator<<(ostream &os, SparseMatrix &s)
{
    int k = 0;

    for (int i = 0; i < s.m; i++) {
        for (int j = 0; j < s.n; j++) {
            if (s.e[k].i == i && s.e[k].j == j)
                cout << s.e[k++].x << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }

    return os;
}


int main (int argc, char *argv[])
{

    SparseMatrix s1(5, 5, 5);
    SparseMatrix s2(5, 5, 5);

    cin >> s1;
    cin >> s2;

    SparseMatrix sum = s1 + s2;

    cout << "First Matrix" << endl << s1;
    cout << "Second Matrix" << endl << s2;
    cout << "Sum Matrix" << endl << sum;

    return 0;
}
