#pragma once
const float box_in[] = {
    // Front face (Z = 1.0, Normals point inward along -Z)
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
     1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // Bottom-right
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // Top-right

    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // Bottom-left
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // Top-right
    -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // Top-left

    // Back face (Z = -1.0, Normals point inward along +Z)
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // Bottom-left
     1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // Bottom-right
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // Top-right

    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // Bottom-left
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // Top-right
    -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // Top-left

    // Left face (X = -1.0, Normals point inward along +X)
    -1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
    -1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Bottom-right
    -1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Top-right

    -1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
    -1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Top-right
    -1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // Top-left

    // Right face (X = 1.0, Normals point inward along -X)
     1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
     1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Bottom-right
     1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Top-right

     1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
     1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Top-right
     1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // Top-left

     // Top face (Y = 1.0, Normals point inward along -Y)
     -1.0f,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
      1.0f,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // Bottom-right
      1.0f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // Top-right

     -1.0f,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
      1.0f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // Top-right
     -1.0f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // Top-left

     // Bottom face (Y = -1.0, Normals point inward along +Y)
     -1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
      1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // Bottom-right
      1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // Top-right

     -1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
      1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // Top-right
     -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f // Top-left
};



const float box_out[] = {
    // Front face (Z = 1.0, Normals point outward along +Z)
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // Bottom-left
     1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // Bottom-right
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // Top-right

    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // Bottom-left
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // Top-right
    -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // Top-left

    // Back face (Z = -1.0, Normals point outward along -Z)
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // Bottom-left
     1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // Bottom-right
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // Top-right

    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // Bottom-left
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // Top-right
    -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // Top-left

    // Left face (X = -1.0, Normals point outward along -X)
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
    -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Bottom-right
    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Top-right

    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
    -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Top-right
    -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // Top-left

    // Right face (X = 1.0, Normals point outward along +X)
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
     1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Bottom-right
     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Top-right

     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
     1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // Top-right
     1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // Top-left

     // Top face (Y = 1.0, Normals point outward along +Y)
     -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
      1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // Bottom-right
      1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // Top-right

     -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
      1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // Top-right
     -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top-left

     // Bottom face (Y = -1.0, Normals point outward along -Y)
     -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
      1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // Bottom-right
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // Top-right

     -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // Bottom-left
      1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // Top-right
     -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f // Top-left
};
