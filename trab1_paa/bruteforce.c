#include "bruteforce.h"
#include <stdio.h>
#include <math.h>

double dist(Points p1, Points p2)
{
    return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

Points* bruteForceDist(Points* pts, int n)
{
    static Points pts_r[2] = {{pts[0].x, pts[0].y},{pts[1].x, pts[1].y}};
    double menor_dist = dist(pts_r[0], pts_r[1]);
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j<n;j++)
        {
            double dist_aux = dist(pts[i], pts[j]);
            //printf("%lf\t%lf\t%lf\t%lf\t%lf\n", pts[i].x, pts[i].y, pts[j].x,pts[j].y,dist_aux);
            if(menor_dist > dist_aux)
            {
                menor_dist = dist_aux;
                pts_r[0].x = pts[i].x;
                pts_r[0].y = pts[i].y;
                pts_r[1].x = pts[j].x;
                pts_r[1].y = pts[j].y;
            }
        }
    }
    return pts_r;
}