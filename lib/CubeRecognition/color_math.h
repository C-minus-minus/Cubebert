#ifndef COLOR_MATH_H
#define COLOR_MATH_H


// Class containing static functions and structs for converting RGB to CIE L*ab
class ColorMath {
public:
    struct RGB {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };

    struct XYZ {
        float X;
        float Y;
        float Z;
    };

    struct CIELAB {
        unsigned char lStar;
        unsigned long long aStar;
        unsigned long long bStar;
    };

    static CIELAB* rgb2CIE(RGB pixel);
    static RGB* subsample(unsigned char *data[][], int initX, int initY, size_t subsampleWidth=64, size_t subsampleHeight=64);

private:
    static XYZ* rgb2xyz(RGB pixel);
    static CIELAB* xyz2cielab(XYZ datum, XYZ ref);
};

#endif // COLOR_MATH_H
