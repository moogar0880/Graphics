/**
 * Color.h -- a class abstraction for gl color specification. This only uses
 *            the float version, but it could be extended if it ever proved
 *            useful to be more generic.
 *
 *            it support rgba
 *
 * @author R. Daniel Bergeron
 * @date   09/24/2012
 *
 * History:
 * 092412  For now this isn't anything more than a struct
 *
 */

#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
   Color();
   Color( const Color& c );
   Color( float red, float green, float blue, float alpha = 1.0f );

   float r, g, b, a;

protected:

};

#endif /* COLOR_H */
