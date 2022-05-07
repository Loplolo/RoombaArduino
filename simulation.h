#ifndef ARDUINOROOMBA_SIMULATION_H
#define ARDUINOROOMBA_SIMULATION_H

#include "ConvexHull.h"
#include "AreaMapping.h"
class Roomba{

    private:
        int diameter;
        Point position = Point(0,0);
        MapArea mapArea;
    public:
        Roomba(MapArea m, int d){
            mapArea = m;
            diameter = d;
        }
        Point move(Point b){
            b.x += position.x;
            b.y += position.y;
            Segment s = Segment(position, b);
            if(mapArea.validPoint(b)){
                //Imposto l'output al punto dove si muove
                position = b;
                return b;
            }else{
                //trovo un punto nel segmento s valido -> implemento pathfinding
            };
        }



};


#endif