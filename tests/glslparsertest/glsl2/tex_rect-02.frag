// [config]
// expect_result: fail
// glsl_version: 1.10
// glsles_version: 1.00
//
// [end config]

/* FAIL */
#extension GL_ARB_texture_rectangle: disable

uniform sampler2DRect s;
