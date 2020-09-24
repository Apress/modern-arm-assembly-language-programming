//------------------------------------------------
//               Ch16_02.h
//------------------------------------------------

#pragma once

// Simple vector structure
typedef struct
{
    float X;        // X component
    float Y;        // Y component
    float Z;        // Z component
} Vector;

// Vector structure of arrays
typedef struct
{
    float* X;       // X components
    float* Y;       // Y components
    float* Z;       // Z components
} VectorSoA;

const size_t c_Align = 16;

// Ch16_02.cpp
void CrossProdAOS(Vector* c, const Vector* a, const Vector* b, size_t n);
void CrossProdSOA(VectorSoA& c, const VectorSoA& a, const VectorSoA& b, size_t n);

// Ch16_02_.asm
extern "C" void CrossProdAOS_(Vector* c, const Vector* a, const Vector* b, size_t n);
extern "C" void CrossProdSOA_(VectorSoA& c, const VectorSoA& a, const VectorSoA& b,
    size_t n);

// Ch16_02_BM.cpp
extern void CrossProd_BM(void);

// Ch16_02_Misc.cpp
void InitVec(Vector* a_aos, Vector* b_aos, VectorSoA& a_soa, VectorSoA& b_soa, size_t n);
bool CompareCP(Vector* c1_aos, Vector* c2_aos, VectorSoA& c1_soa, VectorSoA& c2_soa,
    size_t n);
