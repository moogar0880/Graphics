/**
 * flat fragment shader
 * color comes from a uniform variable
 */

uniform vec4 rdbcolor;

void
main()
{
    gl_FragColor = rdbcolor;
    //gl_FragColor = vec4( 0, 1, 0, 1 );
}
