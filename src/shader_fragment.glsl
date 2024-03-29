#version 330 core



// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da cor de cada vértice, definidas em "shader_vertex.glsl" e
// "main.cpp".
in vec4 position_world;
in vec4 normal;
in vec4 position_model;
in vec3 cor_interpolada_pelo_rasterizador;

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
uniform sampler2D TextureImage3;
uniform sampler2D TextureImage4;
uniform sampler2D TextureImage5;
uniform sampler2D TextureImage6;
uniform sampler2D TextureImage7;
uniform sampler2D TextureImage8;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;



// Identificador que define qual objeto está sendo desenhado no momento
#define SPHERE  0
#define BUNNY   1
#define PLANE   2
#define CUBE    3
#define BASIC   3
#define BACK    4
#define GROUND  5
#define X		9
#define WALL    11
#define CASTLE  12
#define FALLWALL 13
#define CASTLEFALL 14


#define MONSTER_GREEN 6
#define MONSTER_BLUE  7
#define MONSTER_RED	  8

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
    vec4 l = normalize(vec4(0.0,1.0,1.0,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l+2*n*(dot(n,l));

	// Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    // Parâmetros que definem as propriedades espectrais da superfície
    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q; // Expoente especular para o modelo de iluminação de Phong
	vec3 I;
	vec3 Ia;
	vec3 lambert_diffuse_term;
	vec3 ambient_term;
	vec3 phong_specular_term;
	vec3 texturaOBJ = vec3(0.0,0.0,0.0);

	if ( object_id == GROUND )
    {

        U = texcoords.x;
        V = texcoords.y;
		color = texture(TextureImage0, vec2(U,V)).rgb;

    }
	else if ( object_id == BACK )
    {

        U = texcoords.x;
        V = texcoords.y;
		color = texture(TextureImage1, vec2(U,V)).rgb;

    }
	else if ( object_id == WALL )
    {

        U = texcoords.x;
        V = texcoords.y;
		color = texture(TextureImage5, vec2(U,V)).rgb;

    }
	else if ( object_id == FALLWALL )
    {

        U = texcoords.x;
        V = texcoords.y;
		color = texture(TextureImage7, vec2(U,V)).rgb;

    }
	else if ( object_id == CASTLE )
    {

        U = texcoords.x;
        V = texcoords.y;
		color = texture(TextureImage6, vec2(U,V)).rgb;

    }
	else if ( object_id == CASTLEFALL )
    {

        U = texcoords.x;
        V = texcoords.y;
		color = texture(TextureImage8, vec2(U,V)).rgb;

    }
	else if ( object_id == MONSTER_GREEN ||
			  object_id == MONSTER_BLUE  ||
			  object_id == MONSTER_RED	)
	{
        Ka = vec3(0.1,0.1,0.1);
		I = vec3(1.0,1.0,1.0);    						      // Espectro da fonte de iluminação
		Ia = vec3(1.0,1.0,1.0);   						      // Espectro da luz ambiente

        // Propriedades espectrais do monstro
        if(object_id == MONSTER_GREEN){
        //projecao planar...
        float minx = bbox_min.x;
        float maxx = bbox_max.x;
        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        U = (position_model.x - minx) / (maxx - minx);
        V = (position_model.y - minx) / (maxy - miny);

        //Projecao em todas as faces.
		//	U = texcoords.x;
		//	V = texcoords.y;
			color = texture(TextureImage3, vec2(U,V)).rgb;

		}

        if(object_id == MONSTER_BLUE){
                /*
			Kd = vec3 (0.1, 0.1, 1.0);
            lambert_diffuse_term = Kd*I*(max(0,dot(n,l)));       // Termo difuso utilizando a lei dos cossenos de Lambert
            ambient_term = Ka*Ia;     						      // Termo ambiente
            color = lambert_diffuse_term + ambient_term;
*/
            // Correção gamma, considerando monitor sRGB.
            //color = pow(color, vec3(1.0,1.0,1.0)/2.2);
            color = cor_interpolada_pelo_rasterizador;
		}

        if(object_id == MONSTER_RED){
			Kd = vec3 (1.0, 0.1, 0.1);
			Ks = vec3(0.8, 0.8, 0.8);
			q = 64.0;
            lambert_diffuse_term = Kd*I*(max(0,dot(n,l)));       // Termo difuso utilizando a lei dos cossenos de Lambert
            ambient_term = Ka*Ia;     						      // Termo ambiente
            phong_specular_term  = Ks*I*max(0,pow(dot(r,v) ,q)); // Termo especular utilizando o modelo de iluminação de Phong
            color = lambert_diffuse_term + ambient_term + phong_specular_term;
            // Correção gamma, considerando monitor sRGB.
            color = pow(color, vec3(1.0,1.0,1.0)/2.2);

		}



	}
    else // Objeto desconhecido = preto
    {
		color = vec3(0.0,0.0,0.0);

    }
}
