// [config]
// expect_result: pass
// glsl_version: 1.10
// glsles_version: 1.00
//
// [end config]

const float FloatConst1 = 3.0 * 8.0, floatConst2 = 4.0;
const bool BoolConst1 = true && true || false;
const bool BoolConst2 = false || !false && false;

void main (void)
{
    float float1 = 4.0, float2 = floatConst2;
    int int_1 = int(FloatConst1);
    vec4 vec4_1;
    vec3 vec3_1;
//  unsigned int unsigned_int_1;
    bool bool4, bool5;

    bool4 = bool5;
    //float1 = bool5;
    //bool5 = float1;

    bool4 = 4.0 > 5.0;
    bool4 = !(3.2 != 0.0);
    bool4 = bool(float1);
    bool4 = bool(int_1);
    float1 = float(bool4);
    float1 = float(int_1);
    int_1 = int(float1);
    int_1 = int(bool4); 

    {
        int a, b, c;
        
        a = b;
        b = c;
        {
            int b, c, d;

            b = c;
            c = d;
            {
                int a, d, e;
                
                a = d;
                d = e;
            }
            {
                int a, b, c;
                a = b;
                b = c;
            }
        }
        a = b;
        b = c;
    }

    {
        float f1, f2;
        vec3 v31, v32;

        max(f1, f2);
        max(v31, v32);

        vec4 v4 = vec4(3.0);
        vec3 v3 = -vec3(2.0, 1.0, 3.0);
        mat2 m2 = mat2(3.0, 4.0, 6.0, 3.0);
        //mat4 m4 = mat4(1.0, m2, v3, v4, m2);
    }

    if (BoolConst1)
        ++vec3_1;
    else
        --vec3_1;

    if (BoolConst2)
        ++vec3_1;
    else
        --vec3_1;

    if (BoolConst1 || BoolConst2)
        ++vec3_1;
    else
        --vec3_1;

    if (BoolConst2 && BoolConst1)
        ++vec3_1;
    else
        --vec3_1;

    if (FloatConst1 != 0.0)
        --int_1;
    else
        ++int_1;

    if (0 != 0)
        ++int_1;
    else
        --int_1;

    bool4 = BoolConst1 && ! (int_1 != 0) && ! BoolConst1  && ! (FloatConst1 != 0.0) && (FloatConst1 != 0.0) && (float1 != 0.0);
    
    float1 = 5 != 0 ? float1 : float(int_1);
    float1 = 0 != 0 ? float1 : float(int_1);

    if (float1 != float1)
        ++int_1;
    else
        --int_1;

    float1 = float1 != float1 ? float1 : float(int_1);

    --int_1;
    ++float1;
    (vec4_1.x)--;
    vec3_1++;

	if (int_1 != 4)
		discard;

    float1 = 4.0 + 6.0;
    int ii,jj,kk;
    float ff;
    ii = jj, kk, ff;
    
    vec4_1 = vec4_1 + 2.0;
    ivec4 iv;
    iv = iv + 2;
    gl_FragColor = vec4(float1+float1, float1, float1, float(int_1));
}
