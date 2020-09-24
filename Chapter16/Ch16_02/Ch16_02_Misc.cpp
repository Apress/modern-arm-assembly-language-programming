//------------------------------------------------
//               Ch16_02_Misc.cpp
//------------------------------------------------

#include <iostream>
#include <random>
#include <cmath>
#include "Ch16_02.h"

using namespace std;

void InitVec(Vector* a_aos, Vector* b_aos, VectorSoA& a_soa, VectorSoA& b_soa, size_t n)
{
    uniform_int_distribution<> ui_dist {1, 100};
    mt19937 rng {103};

    for (size_t i = 0; i < n; i++)
    {
        float a_x = (float)ui_dist(rng);
        float a_y = (float)ui_dist(rng);
        float a_z = (float)ui_dist(rng);
        float b_x = (float)ui_dist(rng);
        float b_y = (float)ui_dist(rng);
        float b_z = (float)ui_dist(rng);

        a_aos[i].X = a_soa.X[i] = a_x;
        a_aos[i].Y = a_soa.Y[i] = a_y;
        a_aos[i].Z = a_soa.Z[i] = a_z;

        b_aos[i].X = b_soa.X[i] = b_x;
        b_aos[i].Y = b_soa.Y[i] = b_y;
        b_aos[i].Z = b_soa.Z[i] = b_z;
    }
}

bool CompareCP(Vector* c1_aos, Vector* c2_aos, VectorSoA& c1_soa, VectorSoA& c2_soa, size_t n)
{
    const float eps = 1.0e-9;

    for (size_t i = 0; i < n; i++)
    {
        // AOS verification
        if (fabs(c1_aos[i].X - c2_aos[i].X) > eps)
            return false;

        if (fabs(c1_aos[i].Y - c2_aos[i].Y) > eps)
            return false;

        if (fabs(c1_aos[i].Z - c2_aos[i].Z) > eps)
            return false;
        
        // SOA verification
        if (fabs(c1_soa.X[i] - c2_soa.X[i]) > eps)
            return false;

        if (fabs(c1_soa.Y[i] - c2_soa.Y[i]) > eps)
            return false;

        if (fabs(c1_soa.Z[i] - c2_soa.Z[i]) > eps)
            return false;

        // AOS/SOA verification
        if (fabs(c2_aos[i].X - c1_soa.X[i]) > eps)
            return false;

        if (fabs(c2_aos[i].Y - c2_soa.Y[i]) > eps)
            return false;

        if (fabs(c2_aos[i].Z - c2_soa.Z[i]) > eps)
            return false;
    }

    return true;
}
