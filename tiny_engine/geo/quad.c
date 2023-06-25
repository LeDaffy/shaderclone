#include <te/geo/quad.h>


te_quad rect_new(vec3 origin, float x_dimension, float y_dimension)
{
   return (te_quad){
       .verts = {
       origin[0] - x_dimension/2, origin[1] - y_dimension/2, 0.0f,
       origin[0] + x_dimension/2, origin[1] - y_dimension/2, 0.0f,
       origin[0] + x_dimension/2, origin[1] + y_dimension/2, 0.0f,

       origin[0] + x_dimension/2, origin[1] + y_dimension/2, 0.0f,
       origin[0] - x_dimension/2, origin[1] + y_dimension/2, 0.0f,
       origin[0] - x_dimension/2, origin[1] - y_dimension/2, 0.0f,}
   };
}
