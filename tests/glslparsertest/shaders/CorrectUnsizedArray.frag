// [config]
// expect_result: pass
// glsles_expect_result: fail
// glsl_version: 1.10
// glsles_version: 1.00
//
// [end config]

int array[2];
varying vec4 gl_TexCoord[];
varying vec4 gl_TexCoord[2];

void main()
{
    {
        float array[];
        float array[2];
    }
    {
        vec2 array[];
        vec2 v = array[1];
        vec2 array[2];
    }
    int i = array[1];
}
