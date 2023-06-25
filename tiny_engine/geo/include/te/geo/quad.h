#pragma once

#include <cglm/cglm.h>
#include <te/geo/triangle.h>


typedef struct te_quad {
    te_tri verts[2];
} te_quad;

te_quad rect_new(vec3 origin, float x_dimension, float y_dimension);

