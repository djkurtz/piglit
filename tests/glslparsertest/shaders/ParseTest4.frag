// [config]
// expect_result: fail
// glsl_version: 1.10
// glsles_version: 1.00
//
// [end config]

void main()
{
    const vec4 v = vec2(2.0, 3.0);
    gl_FragColor = v;
}
