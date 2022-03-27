#include "color_math.h"

#include <math.h>

ColorMath::CIELAB* ColorMath::rgb2CIE(RGB pixel) {
    XYZ ref;
    ref.X = 99.187;
    ref.Y = 100.00;
    ref.Z = 67.395;
    return xyz2cielab(*rgb2xyz(pixel), ref);
}

ColorMath::XYZ* ColorMath::rgb2xyz(RGB pixel) {
    double red = pixel.red / 255.0;
    double green = pixel.green / 255.0;
    double blue = pixel.blue / 255.0;

    if(red > 0.04045)
        red = pow((red + 0.055) / 1.055, 2.4);
    else
        red /= 12.92;

    if(green > 0.04045)
        green = pow((green + 0.055) / 1.055, 2.4);
    else
        green /= 12.92;

    if(blue > 0.04045)
        blue = pow((blue + 0.055) / 1.055, 2.4);
    else
        blue /= 12.92;

    red *= 100;
    green *= 100;
    blue *= 100;

    XYZ *datum = new XYZ;
    datum->X = red * 0.4124 + green * 0.3576 + blue * 0.1805;
    datum->Y = red * 0.2126 + green * 0.7152 + blue * 0.0722;
    datum->Z = red * 0.0193 + green * 0.1192 + blue * 0.9505;

    return datum;
}

ColorMath::CIELAB* ColorMath::xyz2cielab(XYZ datum, XYZ ref) {
    double x = datum.X / ref.X;
    double y = datum.Y / ref.Y;
    double z = datum.Z / ref.Z;

    if(x > 0.008856)
        x = pow(x, 0.33);
    else
        x = (7.787 * x) + (16 / 116);

    if(y > 0.008856)
        y = pow(y, 0.33);
    else
        y = (7.787 * y) + (16 / 116);

    if (z > 0.008856)
        z = pow(z, 0.33);
    else
        z = (7.787 * z) + (16 / 116);

    CIELAB *cielab = new CIELAB;
    cielab->lStar = (116 * y) - 16;
    cielab->aStar = 500 * (x - y);
    cielab->bStar = 200 * (y - z);

    return cielab;
}