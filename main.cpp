#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include "ConvexHull.h"
#include "AreaMapping.h"
#include "simulation.h"


int main(){
        srand(time(nullptr));
        std::vector<Point> points(100);
        for(int i =0; i<100; i++){
            coord_t x = rand() % 100 ;
            coord_t y = rand() % 100 ;
            Point p(x, y);
            points.operator[](i) = p;
        }
        std::vector<Point> out = convex_hull(points);
        Polygon area(out);
        MapArea mappa(area);

        std::fstream f;
        f.open("points.csv",  std::ios::out);
        f << "x"; ;
        f << ",";
        f << "y"; ;
        f << "\n";
        for (int i=0; i<out.size(); i++){
            f << out.operator[](i+1).x; ;
            f << ", ";
            f << out.operator[](i+1).y; ;
            f << "\n";
        }
            f << out.operator[](1).x; ;
            f << ", ";
            f << out.operator[](1).y; ;
            f << "\n";
        f.close();
        std::cout << area.tostring();

        Roomba roomba(mappa, 11);
        return 0;
    }
