// [config]
// expect_result: fail
// glsl_version: 1.10
// glsles_version: 1.00
//
// [end config]

void main()
{
    float f1,f2,f3;
    f3 = f1 > f2;  // f1 > f2 result in a bool that cannot be assigned to a float
}
