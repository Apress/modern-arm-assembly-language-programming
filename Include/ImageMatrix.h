//-------------------------------------------------
//               ImageMatrix.h
//-------------------------------------------------

#pragma once
#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstring>
#include "OS.h"
#include "Misc.h"
#include "ImageMisc.h"
#include "ImagePng.h"

class ImageMatrix
{
    static const size_t c_PixelBufferAlignment = 16;
    static const int c_PngTempBufferSize = 2048 * 2048 * sizeof(RGB32);     // h * w * sizeof(RGB32)

    int m_Height = 0;
    int m_Width = 0;
    int m_NumPixels = 0;
    int m_BytesPerPixel = 0;
    int m_PixelBufferSize = 0;
    void* m_PixelBuffer = nullptr;
    PixelType m_PixelType = PixelType::Undefined;

    void AllocatePixelBuffer(int height, int width, PixelType pixel_type)
    {
        if (pixel_type == PixelType::Gray8)
            m_BytesPerPixel = 1;
        else if (pixel_type == PixelType::Rgb32)
            m_BytesPerPixel = sizeof(RGB32);
        else
            throw std::runtime_error("AllocatePixelBuffer() - Invalid type");

        m_Height = height;
        m_Width = width;
        m_NumPixels = m_Height * m_Width; 
        m_PixelBufferSize = m_NumPixels * m_BytesPerPixel;
        m_PixelType = pixel_type;
        m_PixelBuffer = OS::AlignedMalloc(m_PixelBufferSize, c_PixelBufferAlignment);
    };

public:
    int GetHeight() const                           { return m_Height; }
    int GetWidth() const                            { return m_Width; }
    int GetNumPixels() const                        { return m_Height * m_Width; }
    int GetBytesPerPixel() const                    { return m_BytesPerPixel; }
    int GetPixelBufferSize() const                  { return m_PixelBufferSize; }
    PixelType GetPixelType() const                  { return m_PixelType; }
    template <typename T> T* GetPixelBuffer(void)   { return (T*)m_PixelBuffer; }

    ImageMatrix(void) = delete;
    ImageMatrix(const ImageMatrix& im) = delete;
    ImageMatrix(ImageMatrix&& im) = delete;
    ImageMatrix& operator = (const ImageMatrix& im) = delete;
    ImageMatrix& operator = (ImageMatrix&& im) = delete;

    ImageMatrix(const std::string& filename, PixelType pixel_type, Channel channel = Channel::None)
    {
        if (Misc::IsExt(filename, "png"))
        {
            if (pixel_type != PixelType::Gray8 && pixel_type != PixelType::Rgb32)
                throw std::runtime_error("ImageMatrix::ImageMatrix(const char* filename) - unsupported PixelType");

            if (pixel_type == PixelType::Gray8 && channel == Channel::None)
                throw std::runtime_error("ImageMatrix::ImageMatrix(const char* filename) - invalid 'channel'");

            int height, width;
            ImagePng im_png;

            // TODO:
            // Update ImagePng to eliminate need for large temporary buffer.
            // ImagePng::LoadImage currently throws an exception if c_PngTempBufferSize
            // is too small.

            const int pb_png_size = c_PngTempBufferSize;
            uint8_t* pb_png = new uint8_t[pb_png_size];

            im_png.LoadImage(filename, pb_png, pb_png_size, &height, &width);
            AllocatePixelBuffer(height, width, pixel_type);

            if (pixel_type == PixelType::Gray8)
            {
                uint8_t* pb_des = GetPixelBuffer<uint8_t>();

                for (int i = 0; i < m_NumPixels; i++)
                    pb_des[i] = pb_png[i * 4 + (int)channel];
            }
            else
            {
                memcpy(m_PixelBuffer, pb_png, m_PixelBufferSize);
            }

            delete[] pb_png;
        }
        else
            throw std::runtime_error("ImageMatrix::ImageMatrix(const char* filename) - unsupported image file type");
    }

    ImageMatrix(int height, int width, PixelType pixel_type)
    {
        AllocatePixelBuffer(height, width, pixel_type);
    }

    ~ImageMatrix(void)
    {
        OS::AlignedFree(m_PixelBuffer);
    }

    void SaveToPngFile(const std::string& filename)
    {
        ImagePng im_png;

        if (m_PixelType == PixelType::Gray8)
        {
            uint8_t* pb_png = new uint8_t[m_NumPixels * 4];
            uint8_t* pb_src = GetPixelBuffer<uint8_t>();

            for (int i = 0; i < m_NumPixels; i++)
            {
                pb_png[i * 4 + 0] = pb_src[i];
                pb_png[i * 4 + 1] = pb_src[i];
                pb_png[i * 4 + 2] = pb_src[i];
                pb_png[i * 4 + 3] = 0xff;
            }

            im_png.SaveImage(filename, pb_png, m_Height, m_Width);
            delete[] pb_png;
        }
        else if (m_PixelType == PixelType::Rgb32)
        {
            im_png.SaveImage(filename, (uint8_t*)m_PixelBuffer, m_Height, m_Width);
        }
        else
            throw std::runtime_error("ImageMatrix::SaveToPngFile(const char* filename) - unsupported PixelType");
    }

    void AllocRgbArrays(uint8_t** r, uint8_t** g, uint8_t** b, unsigned int alignment)
    {
        if (m_PixelType != PixelType::Rgb32)
            throw std::runtime_error("ImageMatrix::AllocRgbArrays(size_t alignment) - Invalid 'm_PixelType'");

        *r = (uint8_t*)OS::AlignedMalloc(m_NumPixels * sizeof(uint8_t), alignment);
        *g = (uint8_t*)OS::AlignedMalloc(m_NumPixels * sizeof(uint8_t), alignment);
        *b = (uint8_t*)OS::AlignedMalloc(m_NumPixels * sizeof(uint8_t), alignment);
    }

    void FreeRgbArrays(uint8_t* r, uint8_t* g, uint8_t* b)
    {
        if (m_PixelType != PixelType::Rgb32)
            throw std::runtime_error("ImageMatrix::FreeRgbArrays(size_t alignment) - Invalid 'm_PixelType'");

        OS::AlignedFree(r);
        OS::AlignedFree(g);
        OS::AlignedFree(b);
    }

    void GetRgbPixelData(uint8_t* r, uint8_t* g, uint8_t* b)
    {
        if (m_PixelType != PixelType::Rgb32)
            throw std::runtime_error("ImageMatrix::GetRgbPixelData(Uint8* r, Uint8* g, Uint8* b) - Invalid 'm_PixelType'");

        RGB32* pb = (RGB32*)m_PixelBuffer;

        for (int i = 0; i < m_NumPixels; i++, pb++)
        {
            *r++ = pb->m_R;
            *g++ = pb->m_G;
            *b++ = pb->m_B;
        }
    }

    void SetRgbPixelData(const uint8_t* r, const uint8_t* g, const uint8_t* b)
    {
        if (m_PixelType != PixelType::Rgb32)
            throw std::runtime_error("ImageMatrix::SetRgbPixelData(const Uint8* r, const Uint8* g, const Uint8* b) - Invalid 'm_PixelType'");

        RGB32* pb = (RGB32*)m_PixelBuffer;

        for (int i = 0; i < m_NumPixels; i++, pb++)
        {
            pb->m_R = *r++;
            pb->m_G = *g++;
            pb->m_B = *b++;
        }
    }
};
