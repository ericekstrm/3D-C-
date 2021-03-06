#include "Skybox.h"

#include <algorithm>
#include <iostream>
#include "stb_image.h"

Skybox::Skybox()
{
    load_cube_map(grimmnight);
    load_buffer_data();
}

Skybox::~Skybox()
{
}

void Skybox::render() const
{
    glDisable(GL_DEPTH_TEST);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);

    glEnable(GL_DEPTH_TEST);
}

void Skybox::load_cube_map(std::vector<std::string> texture_files)
{
    glGenTextures(1, &cubemap_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);

    for (int i = 0; i < texture_files.size(); i++)
    {
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(false); // tell stb to not flip loaded texture's on the y-axis.
        unsigned char *data = stbi_load(texture_files[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else
        {
            std::cout << "Failed to load texture:" << texture_files[i] << std::endl;
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::load_buffer_data()
{
    load_VAO();

    load_vertices_VBO(vertices);
    load_cubemap_VBO(vertices);
    std::vector<int> i(vertices.size());
    std::generate(i.begin(), i.end(), [i = 0]() mutable {
        return i++;
    });
    load_indices_VBO(i);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Skybox::load_cubemap_VBO(std::vector<float> const & texture_coords)
{
    int texture_attrib_array = 1;
    glGenBuffers(1, &cubemap_id);
    glBindBuffer(GL_ARRAY_BUFFER, cubemap_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texture_coords.size(), &texture_coords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(texture_attrib_array, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
}