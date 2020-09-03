#include "Terrain.h"

#include <iostream>

#include <random>

Terrain::Terrain()
    : Model(Vector<3> {0, 0, 0})
{
    generate_terrain();
    load_buffer_data(vertices, texture_coords, indices);
}

Terrain::~Terrain()
{
}

void Terrain::generate_terrain()
{
    for (int i = -terrain_resolution / 2; i < terrain_resolution / 2 + 1; i++)
    {
        for (int j = -terrain_resolution / 2; j < terrain_resolution / 2 + 1; j++)
        {
            float r = 0;// ((float) rand() / RAND_MAX) / 2;
            vertices.push_back(terrain_size / terrain_resolution * i);
            vertices.push_back(r);
            vertices.push_back(terrain_size / terrain_resolution * j);

            texture_coords.push_back(static_cast<float>(i) / terrain_resolution);
            texture_coords.push_back(static_cast<float>(j) / terrain_resolution);
        }
    }

    int p = 0;
    for (int i = 0; i < terrain_resolution; i++)
    {
        for (int j = 0; j < terrain_resolution; j++)
        {
            int topLeft = i * (terrain_resolution + 1) + j;
            int topRight = topLeft + 1;
            int bottomLeft = (i + 1) * (terrain_resolution + 1) + j;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(topLeft);
            indices.push_back(bottomRight);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
        }
    }
}
