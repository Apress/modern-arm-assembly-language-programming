//-------------------------------------------------
//               MatrixF64.h
//-------------------------------------------------

#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <cstring>
#include <stdexcept>
#include "AlignedMem.h"

class MatrixF64
{
    static const size_t c_Alignment = 16;

    size_t m_NumRows;
    size_t m_NumCols;
    size_t m_NumElements;
    size_t m_DataSize;
    double* m_Data;

    int m_OstreamW;
    std::string m_OstreamDelim;

    bool IsConforming(size_t num_rows, size_t num_cols) const
    {
        return m_NumRows == num_rows && m_NumCols == num_cols;
    }

    void Allocate(size_t num_rows, size_t num_cols)
    {
        m_NumRows = num_rows;
        m_NumCols = num_cols;
        m_NumElements = m_NumRows * m_NumCols;
        m_DataSize = m_NumElements * sizeof(double);

        if (m_NumElements == 0)
            m_Data = nullptr;
        else
            m_Data = (double*)AlignedMem::Allocate(m_DataSize, c_Alignment);

        SetOstream(10, "  ");
    }

    void Cleanup(void)
    {
        m_NumRows = m_NumCols = m_NumElements = m_DataSize = 0;
        m_Data = nullptr;
    }

    void Release(void)
    {
        if (m_Data != nullptr)
            AlignedMem::Release(m_Data);

        Cleanup();
    }

public:
    MatrixF64(void)
    {
        Allocate(0, 0);
    }

    MatrixF64(size_t num_rows, size_t num_cols)
    {
        Allocate(num_rows, num_cols);
        Fill(0);
    }

    MatrixF64(size_t num_rows, size_t num_cols, bool set_identity)
    {
        Allocate(num_rows, num_cols);
        Fill(0);

        if (set_identity && m_NumRows == m_NumCols)
        {
            for (size_t i = 0; i < num_rows; i++)
                m_Data[i * m_NumCols + i] = 1.0f;
        }
    }

    MatrixF64(const MatrixF64& mat)
    {
        Allocate(mat.m_NumRows, mat.m_NumCols);
        memcpy(m_Data, mat.m_Data, m_DataSize);
        SetOstream(mat.m_OstreamW, mat.m_OstreamDelim);
    }

    MatrixF64(MatrixF64&& mat)
    {
        m_NumRows = mat.m_NumRows;
        m_NumCols = mat.m_NumCols;
        m_NumElements = mat.m_NumElements;
        m_DataSize = mat.m_DataSize;
        m_Data = mat.m_Data;
        m_OstreamW = mat.m_OstreamW;
        m_OstreamDelim = m_OstreamDelim;

        mat.Cleanup();
    }

    ~MatrixF64()
    {
        Release();
    }

    MatrixF64& operator = (const MatrixF64& mat)
    {
        if (this != &mat)
        {
            if (!IsConforming(*this, mat))
            {
                Release();
                Allocate(mat.m_NumRows, mat.m_NumCols);
            }

            memcpy(m_Data, mat.m_Data, m_DataSize);
            SetOstream(mat.m_OstreamW, mat.m_OstreamDelim);
        }

        return *this;
    }

    MatrixF64& operator = (MatrixF64&& mat)
    {
        Release();

        m_NumRows = mat.m_NumRows;
        m_NumCols = mat.m_NumCols;
        m_NumElements = mat.m_NumElements;
        m_DataSize = mat.m_DataSize;
        m_Data = mat.m_Data;
        SetOstream(mat.m_OstreamW, mat.m_OstreamDelim);

        mat.Cleanup();
        return *this;
    }

    friend bool operator == (const MatrixF64& mat1, const MatrixF64& mat2)
    {
        if (!IsConforming(mat1, mat2))
            return false;

        return (memcmp(mat1.m_Data, mat2.m_Data, mat1.m_DataSize) == 0) ? true : false;
    }

    friend bool operator != (const MatrixF64& mat1, const MatrixF64& mat2)
    {
        if (!IsConforming(mat1, mat2))
            return false;

        return (memcmp(mat1.m_Data, mat2.m_Data, mat1.m_DataSize) != 0) ? true : false;
    }

    double* Data(void) { return m_Data; }
    const double* Data(void) const { return m_Data; }
    size_t GetNumRows(void) const { return m_NumRows; }
    size_t GetNumCols(void) const { return m_NumCols; }
    size_t GetNumElements(void) const { return m_NumElements; }
    bool IsSquare(void) const { return m_NumRows == m_NumCols; }

    friend MatrixF64 operator + (const MatrixF64& mat1, const MatrixF64& mat2)
    {
        if (!IsConforming(mat1, mat2))
            throw std::runtime_error("Non-conforming operands: operator +");

        MatrixF64 result(mat1.m_NumRows, mat1.m_NumCols);

        for (size_t i = 0; i < result.m_NumElements; i++)
            result.m_Data[i] = mat1.m_Data[i] + mat2.m_Data[i];

        return result;
    }

    friend MatrixF64 operator * (const MatrixF64& mat1, const MatrixF64& mat2)
    {
        if (mat1.m_NumCols != mat2.m_NumRows)
            throw std::runtime_error("Non-conforming operands: operator *");

        size_t m = mat1.m_NumCols;
        MatrixF64 result(mat1.m_NumRows, mat2.m_NumCols);

        for (size_t i = 0; i < result.m_NumRows; i++)
        {
            for (size_t j = 0; j < result.m_NumCols; j++)
            {
                double sum = 0;

                for (size_t k = 0; k < m; k++)
                {
                    double val = mat1.m_Data[i * mat1.m_NumCols + k] * mat2.m_Data[k * mat2.m_NumCols + j];
                    sum += val;
                }

                result.m_Data[i * result.m_NumCols + j] = sum;
            }
        }

        return result;
    }

    //
    // For some operations, static functions are used instead of overloaded
    // operators in order to avoid inaccurate benchmark performance comparisons.
    //

    static void Add(MatrixF64& result, const MatrixF64& mat1, const MatrixF64& mat2)
    {
        if (!IsConforming(result, mat1) || !IsConforming(mat1, mat2))
            throw std::runtime_error("Non-conforming operands: MatrixF64::Add");

        for (size_t i = 0; i < result.m_NumElements; i++)
            result.m_Data[i] = mat1.m_Data[i] + mat2.m_Data[i];
    }

    static void Mul(MatrixF64& result, const MatrixF64& mat1, const MatrixF64& mat2)
    {
        if (mat1.m_NumCols != mat2.m_NumRows)
            throw std::runtime_error("Non-conforming operands: MatrixF64::Mul");

        if (result.m_NumRows != mat1.m_NumRows || result.m_NumCols != mat2.m_NumCols)
            throw std::runtime_error("Invalid matrix size: MatrixF64::Mul");

        size_t m = mat1.m_NumCols;

        for (size_t i = 0; i < result.m_NumRows; i++)
        {
            for (size_t j = 0; j < result.m_NumCols; j++)
            {
                double sum = 0;

                for (size_t k = 0; k < m; k++)
                {
                    double val = mat1.m_Data[i * mat1.m_NumCols + k] * mat2.m_Data[k * mat2.m_NumCols + j];
                    sum += val;
                }

                result.m_Data[i * result.m_NumCols + j] = sum;
            }
        }
    }

    static void Mul4x4(MatrixF64& result, const MatrixF64& mat1, const MatrixF64& mat2)
    {
        const size_t nrows = 4;
        const size_t ncols = 4;
        const size_t m = 4;

        for (size_t i = 0; i < nrows; i++)
        {
            for (size_t j = 0; j < ncols; j++)
            {
                float sum = 0;

                for (size_t k = 0; k < m; k++)
                {
                    float val = mat1.m_Data[i * mat1.m_NumCols + k] * mat2.m_Data[k * mat2.m_NumCols + j];
                    sum += val;
                }

                result.m_Data[i * result.m_NumCols + j] = sum;
            }
        }
    }

    static void MulScalar(MatrixF64& result, const MatrixF64& mat, double val)
    {
        if (!IsConforming(result, mat))
            throw std::runtime_error("Non-conforming operands: MatrixF64::MulScalar");

        for (size_t i = 0; i < result.m_NumElements; i++)
            result.m_Data[i] = mat.m_Data[i] * val;
    }

    static void Transpose(MatrixF64& result, const MatrixF64& mat1)
    {
        if (result.m_NumRows != mat1.m_NumCols || result.m_NumCols != mat1.m_NumRows)
            throw std::runtime_error("Non-conforming operands: MatrixF64::Transpose");

        for (size_t i = 0; i < result.m_NumRows; i++)
        {
            for (size_t j = 0; j < result.m_NumCols; j++)
                result.m_Data[i * result.m_NumCols + j] = mat1.m_Data[j * mat1.m_NumCols + i];
        }
    }

    static bool IsConforming(const MatrixF64& mat1, const MatrixF64& mat2)
    {
        return mat1.m_NumRows == mat2.m_NumRows && mat1.m_NumCols == mat2.m_NumCols;
    }

    void Fill(double val)
    {
        for (size_t i = 0; i < m_NumElements; i++)
            m_Data[i] = val;
    }

    void FillRandomInt(unsigned int seed_val, int min_val, int max_val, bool exclude_zero)
    {
        std::uniform_int_distribution<> dist {min_val, max_val};
        std::mt19937 rng {seed_val};

        if (exclude_zero)
        {
            for (size_t i = 0; i < m_NumElements; i++)
            {
                int val;

                while ((val = dist(rng)) == 0)
                {
                }

                m_Data[i] = (double)val;
            }
        }
        else
        {
            for (size_t i = 0; i < m_NumElements; i++)
                m_Data[i] = (double)dist(rng);
        }
    }

    void RoundToZero(double epsilon)
    {
        for (size_t i = 0; i < m_NumElements; i++)
        {
            if (fabs(m_Data[i]) < epsilon)
                m_Data[i] = 0;
        }
    }

    void RoundToI(double epsilon)
    {
        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < m_NumCols; j++)
            {
                size_t k = i * m_NumCols + j;

                if (i != j)
                {
                    if (fabs(m_Data[k]) < epsilon)
                        m_Data[k] = 0;
                }
                else
                {
                    if (fabs(m_Data[k] - 1.0f) < epsilon)
                        m_Data[k] = 1.0f;
                }
            }
        }
    }

    void SetCol(size_t col, const double* vals)
    {
        if (col >= m_NumCols)
            throw std::runtime_error("Invalid column index: MatrixF64::SetCol()");

        for (size_t i = 0; i < m_NumRows; i++)
            m_Data[i * m_NumCols + col] = vals[i];
    }

    void SetRow(size_t row, const double* vals)
    {
        if (row >= m_NumRows)
            throw std::runtime_error("Invalid row index: MatrixF64::SetRow()");

        for (size_t j = 0; j < m_NumCols; j++)
            m_Data[row * m_NumCols + j] = vals[j];
    }

    void SetI(void)
    {
        if (!IsSquare())
            throw std::runtime_error("Square matrix required: MatrixF64::SetI()");

        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < m_NumCols; j++)
                m_Data[i * m_NumCols + j] = (i == j) ? 1.0f : 0.0f;
        }
    }

    void SetOstream(int w, const std::string& delim)
    {
        m_OstreamW = w;
        m_OstreamDelim = delim;
    }

    double Trace(void) const
    {
        if (!IsSquare())
            throw std::runtime_error("Square matrix required: MatrixF64::Trace()");

        double sum = 0;

        for (size_t i = 0; i < m_NumRows; i++)
            sum += m_Data[i * m_NumCols + i];

        return sum;
    }

    friend std::ostream& operator << (std::ostream& os, const MatrixF64& mat)
    {
        for (size_t i = 0; i < mat.m_NumRows; i++)
        {
            for (size_t j = 0; j < mat.m_NumCols; j++)
            {
                os << std::setw(mat.m_OstreamW) << mat.m_Data[i * mat.m_NumCols + j];

                if (j + 1 < mat.m_NumCols)
                    os << mat.m_OstreamDelim;
            }

            os << std::endl;
        }

        return os;
    }
};
