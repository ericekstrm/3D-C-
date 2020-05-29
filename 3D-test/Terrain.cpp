#include "Terrain.h"

#include <iostream>

Terrain::Terrain()
    : Model(Vector<3> {0, 0, 0})
{
    load_buffer_data(vertices, colors, indices);
}

Terrain::~Terrain()
{
}
