#include "Loader.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <iostream>
#include <vector>

using namespace std;

//loads a texture into openGL and returns the texture id.
unsigned load_texture(std::string const & file_name)
{
    // load and create a texture 
    unsigned texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //ändra dessa för att ta bort flimmer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else
    {
        std::cout << "Failed to load texture:" << file_name << std::endl;
    }
    stbi_image_free(data);

    return texture_id;
}

Raw_Model_Data create_quad(float x, float y, float width, float height, float x_tex, float y_tex, float max_x_tex, float max_y_tex)
{
    vector<float> vertices {
        x, y, 0,
        x + width, y, 0,
        x, y + height, 0,
        x + width, y + height, 0
    };
    vector<float> textures {
        x_tex, max_y_tex,
        max_x_tex, max_y_tex,
        x_tex, y_tex,
        max_x_tex, y_tex
    };

    //add data that is specific to that vao
    vector<int> indices {0, 1, 2, 1, 2, 3};

    return Raw_Model_Data {vertices, textures, indices};
}

Raw_Model_Data create_quad(float x, float y, float width, float height)
{
    return create_quad(x, y, width, height, 0, 0, 1, 1);
}
