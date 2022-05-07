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
            if(mapArea.validPoint(b, diameter)){
                position = b;
                return b;
            }else{
                //trovo un punto nel segmento s valido
                //trovo un punto sul segmento s la cui distanza dal segmento che interseca è almeno 11cm


                return Point(0,0);
            };
        }



};


#endif