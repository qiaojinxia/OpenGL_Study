#ifdef GL_ES
precision mediump float;
#endif
varying vec4 V_Color;

void main()
{
    col+= mod(floor(uv.x)+floor(uv.y),2.0)
    gl_FragColor = V_Color;
}