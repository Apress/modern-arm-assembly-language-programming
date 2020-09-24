//------------------------------------------------
//               Ch16_02_BM.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <memory>
#include "Ch16_02.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"
#include "OS.h"

using namespace std;

void CrossProd_BM(void)
{
    cout << "\nRunning benchmark function CrossProd_BM - please wait\n";

    const size_t align = c_Align;
    const size_t num_vec = 1000000;

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

    const size_t num_it = 500;
    const size_t num_alg = 4;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        CrossProdAOS(c1_aos, a_aos, b_aos, num_vec);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        CrossProdAOS_(c2_aos, a_aos, b_aos, num_vec);
        bmtt.Stop(i, 1);

        bmtt.Start(i, 2);
        CrossProdSOA(c1_soa, a_soa, b_soa, num_vec);
        bmtt.Stop(i, 2);

        bmtt.Start(i, 3);
        CrossProdSOA_(c2_soa, a_soa, b_soa, num_vec);
        bmtt.Stop(i, 3);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch16_02_CrossProd_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
