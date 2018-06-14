#ifndef INTERSECAO_H_INCLUDED
#define INTERSECAO_H_INCLUDED

bool intersecao_AABB_AABB(glm::mat4 AABB1, glm::mat4 AABB2);
void Vertices_AABB(glm::mat4 AABB, glm::vec4 vertex_array[]);
bool intersecao_AABB_PONTO(glm::mat4 AABB, glm::vec4 ponto);


bool intersecao_AABB_AABB(glm::mat4 AABB1, glm::mat4 AABB2)
{

    //acha os vertices das box
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

    //encontra os x,y,z min e max de cada box

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


        //retorna se há intersecação
    return (minX1 <= maxX2 && maxX1 >= minX2) &&
         (minY1 <= maxY2 && maxY1 >= minY2) &&
         (minZ1 <= maxZ2 && maxZ1 >= minZ2);
}



bool intersecao_AABB_PONTO(glm::mat4 AABB, glm::vec4 ponto)
{

    //acha os vertices da box
    glm::vec4 vertex_array[8];
    Vertices_AABB(AABB,vertex_array);

    float minX = vertex_array[0].x;
    float minY = vertex_array[0].y;
    float minZ = vertex_array[0].z;

    float maxX = vertex_array[0].x;
    float maxY = vertex_array[0].y;
    float maxZ = vertex_array[0].z;

    //acha os x,y,z min e max da box
        for(int i = 1;i<8;i++)
    {
        if(vertex_array[i].x<minX)
            minX = vertex_array[i].x;
        if(vertex_array[i].y<minY)
            minY = vertex_array[i].y;
        if(vertex_array[i].z<minZ)
            minZ = vertex_array[i].z;


        if(vertex_array[i].x>maxX)
            maxX = vertex_array[i].x;
        if(vertex_array[i].y>maxY)
            maxY = vertex_array[i].y;
        if(vertex_array[i].z>maxZ)
            maxZ = vertex_array[i].z;
    }

    //adiciona uma margem pra nao entrar de fato
    minX-=0.2f;
    minY-=0.2f;
    minZ-=0.2f;
    maxX+=0.2f;
    maxY+=0.2f;
    maxZ+=0.2f;

    //retorna se ha intersecao
    return (minX <= ponto.x && maxX >= ponto.x) &&
         (minY <= ponto.y && maxY >= ponto.y) &&
         (minZ <= ponto.z && maxZ >= ponto.z);


}


//acha os vertices de uma box e guarda no array dado
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
