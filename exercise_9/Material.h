#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"


class Material
{
public:
    static void getMaterial(ShaderProgram* sh, int materialID);
    static int getMaterialCount();



};

