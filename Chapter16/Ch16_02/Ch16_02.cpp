//------------------------------------------------
//               Ch16_02.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <memory>
#include "Ch16_02.h"
#include "AlignedMem.h"

using namespace std;

void CrossProdAOS(Vector* c, const Vector* a, const Vector* b, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        c[i].X = a[i].Y * b[i].Z - a[i].Z * b[i].Y;
        c[i].Y = a[i].Z * b[i].X - a[i].X * b[i].Z;
        c[i].Z = a[i].X * b[i].Y - a[i].Y * b[i].X;
    }
}

void CrossProdSOA(VectorSoA& c, const VectorSoA& a, const VectorSoA& b, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        c.X[i] = a.Y[i] * b.Z[i] - a.Z[i] * b.Y[i];
        c.Y[i] = a.Z[i] * b.X[i] - a.X[i] * b.Z[i];
        c.Z[i] = a.X[i] * b.Y[i] - a.Y[i] * b.X[i];
    }
}

void CrossProd(void)
{
    const char nl = '\n';
    const char* sep = " | ";

    const size_t align = c_Align;
    const size_t num_vec = 18;

    unique_ptr<Vector> a_aos_up {new Vector[num_vec] };
    unique_ptr<Vector> b_aos_up {new Vector[num_vec] };
    unique_ptr<Vector> c1_aos_up {new Vector[num_vec] };
    unique_ptr<Vector> c2_aos_up {new Vector[num_vec] };
    Vector* a_aos = a_aos_up.get();
    Vector* b_aos = b_aos_up.get();
    Vector* c1_aos = c1_aos_up.get();
    Vector* c2_aos = c2_aos_up.get();

    AlignedArray<float> a_soa_x_aa(num_vec, align);
    AlignedArray<float> a_soa_y_aa(num_vec, align);
    AlignedArray<float> a_soa_z_aa(num_vec, align);
    AlignedArray<float> b_soa_x_aa(num_vec, align);
    AlignedArray<float> b_soa_y_aa(num_vec, align);
    AlignedArray<float> b_soa_z_aa(num_vec, align);
    AlignedArray<float> c1_soa_x_aa(num_vec, align);
    AlignedArray<float> c1_soa_y_aa(num_vec, align);
    AlignedArray<float> c1_soa_z_aa(num_vec, align);
    AlignedArray<float> c2_soa_x_aa(num_vec, align);
    AlignedArray<float> c2_soa_y_aa(num_vec, align);
    AlignedArray<float> c2_soa_z_aa(num_vec, align);

    VectorSoA a_soa, b_soa, c1_soa, c2_soa;
    a_soa.X = a_soa_x_aa.Data();
    a_soa.Y = a_soa_y_aa.Data();
    a_soa.Z = a_soa_z_aa.Data();
    b_soa.X = b_soa_x_aa.Data();
    b_soa.Y = b_soa_y_aa.Data();
    b_soa.Z = b_soa_z_aa.Data();
    c1_soa.X = c1_soa_x_aa.Data();
    c1_soa.Y = c1_soa_y_aa.Data();
    c1_soa.Z = c1_soa_z_aa.Data();
    c2_soa.X = c2_soa_x_aa.Data();
    c2_soa.Y = c2_soa_y_aa.Data();
    c2_soa.Z = c2_soa_z_aa.Data();

    InitVec(a_aos, b_aos, a_soa, b_soa, num_vec);

    CrossProdAOS(c1_aos, a_aos, b_aos, num_vec);
    CrossProdAOS_(c2_aos, a_aos, b_aos, num_vec);
    CrossProdSOA(c1_soa, a_soa, b_soa, num_vec);
    CrossProdSOA_(c2_soa, a_soa, b_soa, num_vec);

    bool compare_cp = CompareCP(c1_aos, c2_aos, c1_soa, c2_soa, num_vec);

    cout << "Results for CrossProd\n";
    cout << fixed << setprecision(1);

    for (size_t i = 0; i < num_vec; i++)
    {
        const unsigned int w = 7;
        cout << "Vector cross product #" << i << nl;

        cout << "  a:      ";
        cout << setw(w) << a_aos[i].X << sep;
        cout << setw(w) << a_aos[i].Y << sep;
        cout << setw(w) << a_aos[i].Z << "  ";

        cout << "  b: ";
        cout << setw(w) << b_aos[i].X << sep;
        cout << setw(w) << b_aos[i].Y << sep;
        cout << setw(w) << b_aos[i].Z << nl;

        if (compare_cp)
            cout << "  c:      ";
        else
            cout << "  c1_aos: ";

        cout << setw(w) << c1_aos[i].X << sep;
        cout << setw(w) << c1_aos[i].Y << sep;
        cout << setw(w) << c1_aos[i].Z << nl;

        if (!compare_cp)
        {
            cout << "  c2_aos: ";
            cout << setw(w) << c2_aos[i].X << sep;
            cout << setw(w) << c2_aos[i].Y << sep;
            cout << setw(w) << c2_aos[i].Z << nl;

            cout << "  c1_soa: ";
            cout << setw(w) << c1_soa.X[i] << sep;
            cout << setw(w) << c1_soa.Y[i] << sep;
            cout << setw(w) << c1_soa.Z[i] << nl;

            cout << "  c2_soa: ";
            cout << setw(w) << c2_soa.X[i] << sep;
            cout << setw(w) << c2_soa.Y[i] << sep;
            cout << setw(w) << c2_soa.Z[i] << nl;
        }
    }
}

int main()
{
    CrossProd();
    CrossProd_BM();
    return 0;
}
