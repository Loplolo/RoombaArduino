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
        Roomba(MapArea& m, int d){
            mapArea = m;
            diameter = d;
        }
        Point Pathfinding(Point& b){

        }
        Point move(Point& b){
            b.x += position.x;
            b.y += position.y;
            Segment s = Segment(position, b);
            if(mapArea.validPoint(b, diameter)){
                position = b;
                //Trova i punti per muoversi intorno agli eventuali ostacoli
                //checka col segmento s gli ostacoli
                return b;
            }else{
                // Avvicinati al muro senza toccarlo
                // Runna un'altra scansione
                return {0,0};
            };
        }



};


#endif