#version 330 core

#include "DEFINITIONS.h"

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da cor de cada vértice, definidas em "shader_vertex.glsl" e
// "main.cpp".
in vec4 position_world;
in vec4 normal;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;
/*
// Identificador que define qual objeto está sendo desenhado no momento
#define SPHERE 0
#define BUNNY  1
#define PLANE  2
*/

uniform int object_id;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec3 color;

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(1.0,1.0,0.5,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);
    //l = v;
    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l+2*n*(dot(n,l)); //vec4(0.0,0.0,0.0,0.0); // PREENCHA AQUI o vetor de reflexão especular ideal
    
	// Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;
	
    // Parâmetros que definem as propriedades espectrais da superfície
    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q; // Expoente especular para o modelo de iluminação de Phong

	if ( object_id == GROUND )
    {		
		//Textura
        float minx = bbox_min.x;
        float maxx = bbox_max.x;
        float miny = bbox_min.y;
        float maxy = bbox_max.y;
        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        U = (position_model.x - minx) / (maxx - minx);
        V = (position_model.y - minx) / (maxy - miny);	
		
		
		vec3 Kd0 = texture(TextureImage0, vec2(U,V)).rgb;
		float lambert = max(0,dot(n,l));
		color = Kd0 * (lambert + 0.01);
		color = pow(color, vec3(1.0,1.0,1.0)/2.2);
			
    }
	else if ( object_id == MONSTER_GREEN ||
			  object_id == MONSTER_BLUE  ||
			  object_id == MONSTER_RED	)
	{
        // Propriedades espectrais do monstro
        if(object_id == MONSTER_GREEN){
			Kd = vec3 (0.08, 0.4, 0.8);
		}
		
        if(object_id == MONSTER_BLUE){
			Kd = vec3 (0.08, 0.4, 0.8);
		}		
		
        if(object_id == MONSTER_RED){
			Kd = vec3 (0.08, 0.4, 0.8);
		}	

		
        Ks = vec3(0.8, 0.8, 0.8);
        Ka = vec3(0.04,0.2,0.4);
        q = 32.0;		
		

		vec3 I = vec3(1.0,1.0,1.0);    						      // Espectro da fonte de iluminação    
		vec3 Ia = vec3(0.2,0.2,0.2);   						      // Espectro da luz ambiente    
		vec3 lambert_diffuse_term = Kd*I*(max(0,dot(n,l)));       // Termo difuso utilizando a lei dos cossenos de Lambert
		vec3 ambient_term = Ka*Ia;     						      // Termo ambiente    
		vec3 phong_specular_term  = Ks*I*max(0,pow(dot(r,v) ,q)); // Termo especular utilizando o modelo de iluminação de Phong
		color = lambert_diffuse_term + ambient_term + phong_specular_term;
		
		// Correção gamma, considerando monitor sRGB.
		color = pow(color, vec3(1.0,1.0,1.0)/2.2);		
		
	}
    else // Objeto desconhecido = preto
    {
        Kd = vec3(0.0,0.0,0.0);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.0,0.0,0.0);
        q = 1.0;
		
		vec3 I = vec3(1.0,1.0,1.0);    						      // Espectro da fonte de iluminação    
		vec3 Ia = vec3(0.2,0.2,0.2);   						      // Espectro da luz ambiente    
		vec3 lambert_diffuse_term = Kd*I*(max(0,dot(n,l)));       // Termo difuso utilizando a lei dos cossenos de Lambert
		vec3 ambient_term = Ka*Ia;     						      // Termo ambiente    
		vec3 phong_specular_term  = Ks*I*max(0,pow(dot(r,v) ,q)); // Termo especular utilizando o modelo de iluminação de Phong
		color = lambert_diffuse_term + ambient_term + phong_specular_term;
		
		// Correção gamma, considerando monitor sRGB.
		color = pow(color, vec3(1.0,1.0,1.0)/2.2);		
		
    }
}
