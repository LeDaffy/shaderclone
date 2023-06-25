#include <te/geo/triangle.h>


void tri_new(vec3 vert1, vec3 vert2, vec3 vert3, te_tri* out)
{
    (*out)[0][0] = vert1[0];
    (*out)[0][1] = vert1[1];
    (*out)[0][2] = vert1[2];


    (*out)[1][0] = vert2[0];
    (*out)[1][1] = vert2[1];
    (*out)[1][2] = vert2[2];


    (*out)[2][0] = vert3[0];
    (*out)[2][1] = vert3[1];
    (*out)[2][2] = vert3[2];
}
