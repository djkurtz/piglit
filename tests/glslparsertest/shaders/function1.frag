// [config]
// expect_result: fail
// glsl_version: 1.10
// glsles_version: 1.00
//
// [end config]

void function(int i) 
{
    return i;  // void function cannot return a value
}

void main()
{
    int i;
    function(i);
}


