/**
 * Simple pass-through vertex shader; passes position on
 */

uniform mat4 projXmv;     // ProjectionMatrix * ModelViewMatrix
                          //   must be stored here by cpu program
attribute vec4 vPosition;

void main()
{
   gl_Position = projXmv  * vPosition;
}
