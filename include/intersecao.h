#ifndef INTERSECAO_H_INCLUDED
#define INTERSECAO_H_INCLUDED

bool intersecao_AABB_AABB(glm::mat4 AABB1, glm::mat4 AABB2);
void Vertices_AABB(glm::mat4 AABB, glm::vec4 vertex_array[]);


bool intersecao_AABB_AABB(glm::mat4 AABB1, glm::mat4 AABB2)
{
    //pegar o menor x,y,z de cada e fazer
    /* (a.minX <= b.maxX && a.maxX >= b.minX) &&
         (a.minY <= b.maxY && a.maxY >= b.minY) &&
         (a.minZ <= b.maxZ && a.maxZ >= b.minZ)
    */
    //acha os vertices de cada box
    glm::vec4 vertex_array_1[8];
    Vertices_AABB(AABB1,vertex_array_1);
    glm::vec4 vertex_array_2[8];
    Vertices_AABB(AABB2,vertex_array_2);
    float minX1 = vertex_array_1[0].x;
    float minY1 = vertex_array_1[0].y;
    float minZ1 = vertex_array_1[0].z;
    float minX2 = vertex_array_2[0].x;
    float minY2 = vertex_array_2[0].y;
    float minZ2 = vertex_array_2[0].z;

    float maxX1 = vertex_array_1[0].x;
    float maxY1 = vertex_array_1[0].y;
    float maxZ1 = vertex_array_1[0].z;
    float maxX2 = vertex_array_2[0].x;
    float maxY2 = vertex_array_2[0].y;
    float maxZ2 = vertex_array_2[0].z;

    for(int i = 1;i<8;i++)
    {
        if(vertex_array_1[i].x<minX1)
            minX1 = vertex_array_1[i].x;
        if(vertex_array_1[i].y<minY1)
            minY1 = vertex_array_1[i].y;
        if(vertex_array_1[i].z<minZ1)
            minZ1 = vertex_array_1[i].z;

        if(vertex_array_2[i].x<minX2)
            minX2 = vertex_array_2[i].x;
        if(vertex_array_2[i].y<minY2)
            minY2 = vertex_array_2[i].y;
        if(vertex_array_2[i].z<minZ2)
            minZ2 = vertex_array_2[i].z;


        if(vertex_array_1[i].x>maxX1)
            maxX1 = vertex_array_1[i].x;
        if(vertex_array_1[i].y>maxY1)
            maxY1 = vertex_array_1[i].y;
        if(vertex_array_1[i].z>maxZ1)
            maxZ1 = vertex_array_1[i].z;

        if(vertex_array_2[i].x>maxX2)
            maxX2 = vertex_array_2[i].x;
        if(vertex_array_2[i].y>maxY2)
            maxY2 = vertex_array_2[i].y;
        if(vertex_array_2[i].z>maxZ2)
            maxZ2 = vertex_array_2[i].z;
    }

    return (minX1 <= maxX2 && maxX1 >= minX2) &&
         (minY1 <= maxY2 && maxY1 >= minY2) &&
         (minZ1 <= maxZ2 && maxZ1 >= minZ2);
}
void Vertices_AABB(glm::mat4 AABB, glm::vec4 vertex_array[])
{

    glm::vec4  vertice= glm::vec4(-1.0f,-1.0f,-1.0f,1.0f);
     vertex_array[0] = AABB*vertice;

     vertice= glm::vec4(-1.0f,-1.0f,1.0f,1.0f);
     vertex_array[1] = AABB*vertice;

      vertice= glm::vec4(-1.0f,1.0f,-1.0f,1.0f);
     vertex_array[2] = AABB*vertice;

      vertice= glm::vec4(-1.0f,1.0f,1.0f,1.0f);
     vertex_array[3] = AABB*vertice;

     vertice= glm::vec4(1.0f,-1.0f,-1.0f,1.0f);
     vertex_array[4] = AABB*vertice;

     vertice= glm::vec4(1.0f,-1.0f,1.0f,1.0f);
     vertex_array[5] = AABB*vertice;

     vertice= glm::vec4(1.0f,1.0f,-1.0f,1.0f);
     vertex_array[6] = AABB*vertice;

      vertice= glm::vec4(1.0f,1.0f,1.0f,1.0f);
     vertex_array[7] = AABB*vertice;






}

#endif // INTERSECAO_H_INCLUDED
