#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Vector.h"

class Font
{
private:
    struct Character;
public:
    Font();
    Font(std::string const& font_file_name);
    Font(std::string const& font_file_name, float font_size);
    ~Font();

    float get_space_length() const { return space_length; };
    Character get_character(int ascii) const;
    float get_character_width(int ascii) const;

private:

    void load_font(std::string const& font_file_name);
    std::map<std::string, float> get_line(std::istream& is) const;
    Character create_character(std::map<std::string, float> &, Vector<2> const&, float, float);

    //contains all the characters of the font
    std::map<int, Character> characters {};

    unsigned int texture_id {};

    float font_size {12};
    float space_length {0.05f};

    struct Character
    {
    public:
        //ascii id
        int id;

        //texture space
        float xTextureCoord {};
        float yTextureCoord {};
        float xMaxTextureCoord {};
        float yMaxTextureCoord {};

        //screen space
        float xOffset {};
        float yOffset {};
        float sizeX {};
        float sizeY {};
        float xAdvance {};
    };
};

class GUIText
{
public:

    GUIText();
    GUIText(std::string const& str, Vector<2> const& position);
    ~GUIText();

    void render() const;

private:
    class Character_Mesh;

    void create_mesh(std::string const& str, Font const&);

    Vector<2> position {};
    Font font;

    float const SPACE_LENGTH = 0.1f;

    class Word
    {
    public:
        Word(std::string const& str, Font const& font);
        ~Word();

        void create_mesh(Vector<2> const& current_position, Font const& font);

        std::string text {};
        float word_width;

        std::vector<Character_Mesh> character_meshes {};
    };

    class Character_Mesh
    {
    public:
        Character_Mesh(unsigned vao, unsigned vbo_vertices, unsigned vbo_texture, unsigned vbo_indices, unsigned vertex_count);
        ~Character_Mesh();

        unsigned vao;
        unsigned VBOvertices;
        unsigned VBOtexture;
        unsigned vertex_count;

    };

    std::vector<Word> words {};
};
