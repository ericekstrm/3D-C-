#pragma once

#include <string>
#include "Raw_Model_Data.h"

unsigned load_texture(std::string const& file_name);

//==================================

Raw_Model_Data create_quad(float x, float y, float width, float height,
                           float x_tex, float y_tex, float max_x_tex, float max_y_tex);
Raw_Model_Data create_quad(float x, float y, float width, float height);