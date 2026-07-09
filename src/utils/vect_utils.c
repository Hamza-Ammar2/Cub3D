

#include "cub3d.h"


double    get_distance(t_vect start, t_vect end)
{
    double dx = (double)end.x - start.x;
    double dy = (double)end.y - start.y;
    return (sqrt(dx * dx + dy * dy));
}
