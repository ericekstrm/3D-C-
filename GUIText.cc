#include "GUIText.h"

#include "glad/glad.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Loader.h"

using namespace std;

Font::Font()
    : Font {"arial"}
{
}

Font::Font(std::string const & font_file_name)
{
    load_font(font_file_name);
}

Font::Font(std::string const & font_file_name, float font_size)
    : Font {font_file_name}
{
    font_size = font_size;
}

Font::~Font()
{
}

Font::Character Font::get_character(int ascii) const
{
    return characters.at(ascii);
}

float Font::get_character_width(int ascii) const
{
    return characters.at(ascii).xAdvance;
}

void Font::load_font(std::string const & font_name)
{
    ifstream in("fonts/" + font_name + ".fnt");

    auto first_line {get_line(in)};
    auto second_line {get_line(in)};
    auto third_line {get_line(in)};
    auto fourth_line {get_line(in)};

    map<string, float> header_data {first_line};
    header_data.insert(second_line.begin(), second_line.end());
    header_data.insert(third_line.begin(), third_line.end());
    header_data.insert(fourth_line.begin(), fourth_line.end());

    float default_font_size {header_data["size"]};
    Vector<2> font_image_size {header_data["scaleW"], header_data["scaleH"]};
    float base_line = header_data["base"] / font_image_size[1] * font_size / default_font_size;
    float char_count {header_data["count"]};

    for (int i = 0; i < char_count; i++)
    {
        auto current_line {get_line(in)};

        Character c {create_character(current_line, font_image_size, font_size / default_font_size, base_line)};
        if (c.id == 32)
        {
            space_length = c.xAdvance;
        }
        characters.insert(make_pair(c.id, c));
    }
    texture_id = load_texture("fonts/" + font_name + ".png");
}

map<std::string, float> Font::get_line(istream & is) const
{
    map<string, float> current_line {};

    string line;
    getline(is, line);
    stringstream ss (line);

    string part {};
    while (ss >> part)
    {
        size_t i {part.find("=")};
        if (i != string::npos)
        {
            try
            {
                current_line.insert(make_pair(part.substr(0, i), stoi(part.substr(i + 1))));
            }
            catch (const exception&)
            {
                current_line.insert(make_pair(part.substr(0, i), 0));
            }
        }
    }

    return current_line;
}

Font::Character Font::create_character(std::map<std::string, float> & current_line, Vector<2> const & font_image_size, float scale_factor, float base_line)
{
    //the ascii id of character
    int id = current_line["id"];

    //texture coordinates of the character. normalized to [1,-1]
    float xTex = current_line["x"] / font_image_size[0];
    float yTex = current_line["y"] / font_image_size[1];

    //the width of the box that should be extracted from the texture. also normalized.
    float tex_width = current_line["width"] / font_image_size[0];
    float tex_height = current_line["height"] / font_image_size[1];

    //the size of the quad in screen space
    float quadWidth = tex_width * scale_factor;
    float quadHeight = tex_height * scale_factor;

    //how much to offset the quad in screen space.
    float xOffset = current_line["xoffset"] / font_image_size[0] * scale_factor;
    float yOffset = base_line - quadHeight - current_line["yoffset"] / font_image_size[1] * scale_factor;

    //how much to advance the cursor to the next character
    float xAdvance = current_line["xadvance"] / font_image_size[0] * scale_factor;

    return Character {id, xTex, yTex, tex_width, tex_height, xOffset, yOffset, quadWidth, quadHeight, xAdvance};
}

GUIText::GUIText()
{
}

GUIText::GUIText(string const & str, Vector<2> const& position)
    : position {position}
{
}

GUIText::~GUIText()
{
}

void GUIText::render() const
{
}

void GUIText::create_mesh(string const & str, Font const& font)
{
    Vector<2> currentPosition {position[0], -position[1]};

    istringstream iss(str);
    transform(istream_iterator<string>(iss),
              istream_iterator<string>(),
              words.end(),
              [font] (string const& str) { return Word {str, font};});

    for (auto it = words.begin(); it != words.end(); it++)
    {
        it->create_mesh(currentPosition, font);
        currentPosition[0] += it->word_width + font.get_space_length();
    }
}

GUIText::Word::Word(std::string const & str, Font const & font)
    : text {str}
{
}

GUIText::Word::~Word()
{
}

void GUIText::Word::create_mesh(Vector<2> const& current_position, Font const& font)
{
    float internalCursor = 0;
    for (auto it = text.begin(); it != text.end(); it++)
    {
        int i {static_cast<int>(*it)};
        auto c {font.get_character(i)};
        
        Vector<2> position = {current_position[0] + internalCursor, current_position[1]};
        Raw_Model_Data data = create_quad(position[0] + c.xOffset, position[1] + c.yOffset, c.sizeX, c.sizeY,
                                       c.xTextureCoord, c.yTextureCoord, c.xMaxTextureCoord, c.yMaxTextureCoord);

        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //fix here!!
        //unsigned vbo_vertices {ModelLoader.loadVertexVBO(data.vertices)};
        //unsigned vbo_textures {ModelLoader.loadVertexVBO(data.textures)};
        //unsigned vbo_indices {ModelLoader.loadVertexVBO(data.indices)};

        glBindVertexArray(0);
        //character_meshes.push_back(Character_Mesh {vao, vbo_vertices, vbo_textures, vbo_indices, data.indices.size()});

        internalCursor += c.xAdvance;
    }
}

GUIText::Character_Mesh::Character_Mesh(unsigned vao, unsigned vbo_vertices, unsigned vbo_texture, unsigned vbo_indices, unsigned vertex_count)
    : vao {vao}, VBOvertices {vbo_vertices}, VBOtexture {vbo_texture}, vertex_count {vertex_count}
{
}

GUIText::Character_Mesh::~Character_Mesh()
{
    glDeleteBuffers(1, &VBOvertices);
    glDeleteBuffers(1, &VBOvertices);
    glDeleteVertexArrays(1, &vao);
}
