#ifndef OBJECTS_H
#define OBJECTS_H

#include"Draw.h"


static Draw column("columnVertex.glsl", "columnFragment.glsl", "columnGeometry.glsl"),
line("columnVertex.glsl", "lineFragment.glsl"),
grid("columnVertex.glsl","lineFragment.glsl","columnGeometry.glsl"),
point("columnVertex.glsl", "lineFragment.glsl","pointGeometry.glsl");

 static float points[] = {
	-0.5f,0.5f,
	0.5f,0.5f,
	0.5f,-0.5f,
	-0.5f,-0.5f
};





#endif // 
