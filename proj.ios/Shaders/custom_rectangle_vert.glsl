#ifdef GL_ES
precision mediump float;
#endif

attribute   vec4    custom_a_position;

void main()
{
    gl_Position = CC_MVPMatrix * custom_a_position;
}


