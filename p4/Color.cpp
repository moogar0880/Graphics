/**
 * Color.cpp -- a class abstraction for gl color specification. This only uses
 *            the float version, but it could be extended if it ever proved
 *            useful to be more generic.
 *
 *            it supports rgb and rgba
 *
 * @author R. Daniel Bergeron
 * @date   09/24/2012
 *
 * History:
 * 09/24/12  For now this is little more than a struct
 * 09/24/13  added set method to change an existing color
 */

#include "Color.h"

//------------- simple constructors -----------------------
Color::Color()
{
    r = g = b = 0.0f;
    a = 1.0f;
}
Color::Color( float red, float green, float blue, float alpha )
{
    // Should check that values are in the range [0,1]
    r = red;
    g = green;
    b = blue;
    a = alpha;
}
//------------------ set ----------------------------
void Color::set( float red, float green, float blue, float alpha )
{
    // Should check that values are in the range [0,1]
    r = red;
    g = green;
    b = blue;
    a = alpha;
}
//------------- copy constructor -----------------------
/**
 * Not really needed since this is default behavior
 */
Color::Color( const Color& col )
{
    r = col.r;
    g = col.g;
    b = col.b;
    a = col.a;
}
