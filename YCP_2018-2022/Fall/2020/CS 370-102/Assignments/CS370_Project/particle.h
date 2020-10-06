//
// Created by lqlas on 10/4/2020.
//
#include "vmath.h"
#include "vgl.h"

#ifndef HOUSE_PARTICLE_H
#define HOUSE_PARTICLE_H

#endif //HOUSE_PARTICLE_H

struct Particle {
    vmath::vec2 Position, Velocity;
    vmath::vec4 Color;
    GLfloat Life;

    Particle()
            : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};