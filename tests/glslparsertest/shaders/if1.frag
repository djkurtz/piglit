// [config]
// expect_result: fail
// glsl_version: 1.10
// glsles_version: 1.00
//
// [end config]

void main()
{
    int i;
    if (i) // condition of if statement must be a boolean
        i++;
}
