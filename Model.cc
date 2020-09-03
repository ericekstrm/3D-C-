#include "Model.h"

#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <string>
#include <iostream>

#include "Loader.h"

Model::Model()
    : position {0, 0, 0}
{
    //TODO: load vertices and indices

    texture_id = load_texture("container.jpg");
    load_buffer_data(vertices, colors, indices);
}

Model::Model(Vector<3> const & position)
    : position {std::move(position)}
{
    texture_id = load_texture("container.jpg");
    load_buffer_data(vertices, colors, indices);
}

Model::~Model()
{
}

void Model::update(float delta_time)
{
}

void Model::render() const
{
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
}

Matrix4 const& Model::get_model_matrix() const
{
    Matrix4 t {translation_matrix(position[0], position[1], position[2])};
    Matrix4 s {scale_matrix(scale[0], scale[1], scale[2])};
    Matrix4 r {
        rotation_matrix(rotation[0], 1, 0, 0) * 
        rotation_matrix(rotation[1], 0, 1, 0) *
        rotation_matrix(rotation[2], 0, 0, 1)};

    return (t * r * s);
}

void Model::load_buffer_data(std::vector<float> const& vertices, 
                             std::vector<float> const& texture_coords,
                             std::vector<int> const& indices)
{
    load_VAO();

    load_vertices_VBO(vertices);
    load_textures_VBO(texture_coords);
    load_indices_VBO(indices);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::load_VAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void Model::load_vertices_VBO(std::vector<float> const& vertices)
{
    int vertices_attrib_array = 0;
    glGenBuffers(1, &VBOvertices);
    glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(vertices_attrib_array, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
}

void Model::load_textures_VBO(std::vector<float> const & texture_coords)
{
    int texture_attrib_array = 1;
    glGenBuffers(1, &VBOtextures);
    glBindBuffer(GL_ARRAY_BUFFER, VBOtextures);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texture_coords.size(), &texture_coords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(texture_attrib_array, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
}

void Model::load_indices_VBO(std::vector<int> const& indices)
{
    glGenBuffers(1, &VBOindices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), &indices[0], GL_STATIC_DRAW);
    indices_count = indices.size();
}