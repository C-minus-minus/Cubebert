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
        double lStar;
        double aStar;
        double bStar;
    };

    static CIELAB* rgb2cie(RGB* pixel);
    static RGB* subsample(RGB ***data, int initX, int initY, int subsampleWidth=64, int subsampleHeight=64);

private:
    static XYZ* rgb2xyz(RGB* pixel);
    static CIELAB* xyz2cielab(XYZ* datum, XYZ ref);
};

#endif // COLOR_MATH_H
