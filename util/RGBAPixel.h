/*
 * This file's base code was obtained from my data structures and algorithms course
 * and changes have been made to support the functionlity for this project.
 */

#ifndef _RGBAPIXEL_H_
#define _RGBAPIXEL_H_

#include <iostream>
#include <sstream>

namespace util {
  class RGBAPixel {
  public:
    unsigned char r; /* < red component of pixel, [0,255] */
    unsigned char g; /* < green component of pixel, [0,255] */
    unsigned char b; /* < blue component of pixel, [0,255] */
    double a; /* < Alpha of the pixel, [0, 1] */

    /*
     * Constructs a default RGBAPixel.
     *
     * A default pixel is black.
     * Opaque implies that the alpha component of the pixel is 1.0.
     * Lower alpha values are (semi-)transparent.
     */
    RGBAPixel();

    /*
     * Constructs an opaque RGBAPixel with the given red, green,
     * and green values.
     *
     * @param red value for the new pixel, in [0, 255].
     * @param green value for the new pixel, [0, 255].
     * @param blue value for the new pixel, [0, 255].
     */
    RGBAPixel(int red, int green, int blue);

    /*
     * Constructs an opaque RGBAPixel with the given red, green,
     * and green values.
     *
     * @param red value for the new pixel, in [0, 255].
     * @param green value for the new pixel, [0, 255].
     * @param blue value for the new pixel, [0, 255].
     * @param alpha Alpha value for the new pixel, [0, 1].
     */
    RGBAPixel(int red, int green, int blue, double alpha);

    RGBAPixel & operator=(RGBAPixel const & other);
    bool operator== (RGBAPixel const & other) const ;
    bool operator!= (RGBAPixel const & other) const ;
    bool operator<  (RGBAPixel const & other) const ;
  };

  /*
   * Stream operator that allows pixels to be written to standard streams
   * (like cout).
   *
   * @param out Stream to write to.
   * @param pixel Pixel to write to the stream.
   */
  std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel);
  std::stringstream & operator<<(std::stringstream & out, RGBAPixel const & pixel);
}

#endif