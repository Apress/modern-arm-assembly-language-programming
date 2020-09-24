//-------------------------------------------------
//               ImagePng.h
//-------------------------------------------------

// The code in this module is a modified version of the code
// available on GitHub at https://gist.github.com/niw/5963798.
//
// Also check http://libpng.org/pub/png/libpng.html for more
// information about LIBPNG, especially known security issues.

#include <string>
#include <cstdio>
#include <cstdint>
#include "png.h"

class ImagePng
{
private:
    png_structp m_Png = NULL;
    png_infop m_PngInfo = NULL;
    FILE* m_Fp = NULL;
    png_bytep* m_RowPointers = NULL;

    int m_Width = 0;
    int m_Height = 0;
    png_byte m_ColorType = 0;
    png_byte m_BitDepth = 0;

    void AllocRowPointers(void)
    {
        if (m_RowPointers != NULL)
            throw std::runtime_error("ImagePng::AllocRowPointers - m_RowPointers not NULL");

        m_RowPointers = (png_bytep*)malloc(sizeof(png_bytep) * m_Height);

        for (int i = 0; i < m_Height; i++)
            m_RowPointers[i] = (png_byte*)malloc(png_get_rowbytes(m_Png, m_PngInfo));
    }

    void FreeRowPointers(bool dtor = false)
    {
        if (m_RowPointers == NULL)
        {
            if (dtor)
                return;
            else
                throw std::runtime_error("ImagePng::FreeRowPointers - m_RowPointers is NULL");
        }

        for (int i = 0; i < m_Height; i++)
            free(m_RowPointers[i]);

        free(m_RowPointers);
        m_RowPointers = NULL;
    }

public:
    ImagePng(void)
    {
    }

    ~ImagePng()
    {
        FreeRowPointers(true);
    };

    ImagePng(const ImagePng& im) = delete;
    ImagePng(ImagePng&& im) = delete;
    ImagePng& operator = (const ImagePng& im) = delete;
    ImagePng& operator = (ImagePng&& im) = delete;

    void LoadImage(const std::string& filename, uint8_t* pixel_buff, int pixel_buff_size, int* height, int* width)
    {
        //
        //
        //

        if ((m_Fp = fopen(filename.c_str(), "rb")) == NULL)
            throw std::runtime_error("ImagePng::LoadImage - fopen error");

        m_Png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!m_Png)
            throw std::runtime_error("ImagePng::LoadImage - png_create_read_struct error");

        m_PngInfo = png_create_info_struct(m_Png);

        if (!m_PngInfo)
            throw std::runtime_error("ImagePng::LoadImage - png_create_info_struct error");

        if (setjmp(png_jmpbuf(m_Png)))
            throw std::runtime_error("ImagePng::LoadImage - setjmp error");

        png_init_io(m_Png, m_Fp);
        png_read_info(m_Png, m_PngInfo);

        //
        //
        //

        m_Width = png_get_image_width(m_Png, m_PngInfo);
        m_Height = png_get_image_height(m_Png, m_PngInfo);
        m_ColorType = png_get_color_type(m_Png, m_PngInfo);
        m_BitDepth = png_get_bit_depth(m_Png, m_PngInfo);
        *height = m_Height;
        *width = m_Width;

        //
        // Convert image to RGBA format (8-bits per component) 
        //

        if (m_BitDepth == 16)
            png_set_strip_16(m_Png);

        if (m_ColorType == PNG_COLOR_TYPE_PALETTE)
            png_set_palette_to_rgb(m_Png);

        if (m_ColorType == PNG_COLOR_TYPE_GRAY_ALPHA && m_BitDepth < 8)
            png_set_expand_gray_1_2_4_to_8(m_Png);

        if (png_get_valid(m_Png, m_PngInfo, PNG_INFO_tRNS))
            png_set_tRNS_to_alpha(m_Png);

        if (m_ColorType == PNG_COLOR_TYPE_GRAY || m_ColorType == PNG_COLOR_TYPE_RGB || m_ColorType == PNG_COLOR_TYPE_PALETTE)
            png_set_filler(m_Png, 0xff, PNG_FILLER_AFTER);

        if (m_ColorType == PNG_COLOR_TYPE_GRAY || m_ColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
            png_set_gray_to_rgb(m_Png);

        png_read_update_info(m_Png, m_PngInfo);

        //
        // Make sure caller's pixel buffer is large enough
        //

        int bytes_per_pixel = 4;
        
        if (m_Height * m_Width * bytes_per_pixel >= pixel_buff_size)
            throw std::runtime_error("ImagePng::LoadImage - pixel_buff size error");

        //
        // Read image
        //

        AllocRowPointers();
        png_read_image(m_Png, m_RowPointers);

        //
        // Copy data to caller's pixel buffer
        //

        int k = 0;
        for (int i = 0; i < m_Height; i++)
        {
            png_bytep row_ptr = m_RowPointers[i];

            for (int j = 0; j < m_Width; j++)
            {
                png_bytep pixel_ptr = &row_ptr[j * 4];

                pixel_buff[k + 0] = pixel_ptr[0];
                pixel_buff[k + 1] = pixel_ptr[1];
                pixel_buff[k + 2] = pixel_ptr[2];
                pixel_buff[k + 3] = pixel_ptr[3];
                k += 4;
            }
        }

        //
        // Clean up
        //

        FreeRowPointers();

        fclose(m_Fp);
        png_destroy_read_struct(&m_Png, &m_PngInfo, NULL);
    }

    void SaveImage(const std::string& filename, const uint8_t* pixel_buff, int height, int width)
    {
        if ((m_Fp = fopen(filename.c_str(), "wb")) == NULL)
            throw std::runtime_error("ImagePng::SaveImage - fopen error");

        m_Png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!m_Png)
            throw std::runtime_error("ImagePng::SaveImage - png_create_write_struct error");

        m_PngInfo = png_create_info_struct(m_Png);

        if (!m_PngInfo)
            throw std::runtime_error("ImagePng::SaveImage - png_create_info_struct error");

        if (setjmp(png_jmpbuf(m_Png)))
            throw std::runtime_error("ImagePng::SaveImage - setjmp error");

        png_init_io(m_Png, m_Fp);

        //
        //
        //

        m_Width = width;
        m_Height = height;
        m_BitDepth = 8;
        m_ColorType = PNG_COLOR_TYPE_RGBA;

        png_set_IHDR(
            m_Png,
            m_PngInfo,
            m_Width,
            m_Height,
            m_BitDepth,
            m_ColorType,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);

        png_write_info(m_Png, m_PngInfo);

        //
        // Copy caller's pixel data to PNG buffers
        //

        AllocRowPointers();

        int k = 0;
        for (int i = 0; i < m_Height; i++)
        {
            png_bytep row_ptr = m_RowPointers[i];

            for (int j = 0; j < m_Width; j++)
            {
                png_bytep pixel_ptr = &row_ptr[j * 4];

                pixel_ptr[0] = pixel_buff[k + 0];
                pixel_ptr[1] = pixel_buff[k + 1];
                pixel_ptr[2] = pixel_buff[k + 2];
                pixel_ptr[3] = pixel_buff[k + 3];
                k += 4;
            }
        }

        //
        // Write PNG image
        //

        png_write_image(m_Png, m_RowPointers);
        png_write_end(m_Png, NULL);

        //
        // Clean up
        //

        FreeRowPointers();

        fclose(m_Fp);
        png_destroy_write_struct(&m_Png, &m_PngInfo);
    }
};
