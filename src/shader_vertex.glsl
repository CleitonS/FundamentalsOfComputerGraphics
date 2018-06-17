#version 330 core

// Atributos de vértice recebidos como entrada ("in") pelo Vertex Shader.
// Veja a função BuildTrianglesAndAddToVirtualScene() em "main.cpp".
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;
uniform int object_id;
// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 cor_interpolada_pelo_rasterizador;

// Atributos de vértice que serão gerados como saída ("out") pelo Vertex Shader.
// ** Estes serão interpolados pelo rasterizador! ** gerando, assim, valores
// para cada fragmento, os quais serão recebidos como entrada pelo Fragment
// Shader. Veja o arquivo "shader_fragment.glsl".
out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;



#define MONSTER_GREEN 6
#define MONSTER_BLUE  7
#define MONSTER_RED	  8


void main()
{
    // A variável gl_Position define a posição final de cada vértice
    // OBRIGATORIAMENTE em "normalized device coordinates" (NDC), onde cada
    // coeficiente está entre -1 e 1.  (Veja slides 144 e 150 do documento
    // "Aula_09_Projecoes.pdf").
    //
    // O código em "main.cpp" define os vértices dos modelos em coordenadas
    // locais de cada modelo (array model_coefficients). Abaixo, utilizamos
    // operações de modelagem, definição da câmera, e projeção, para computar
    // as coordenadas finais em NDC (variável gl_Position). Após a execução
    // deste Vertex Shader, a placa de vídeo (GPU) fará a divisão por W. Veja
    // slide 189 do documento "Aula_09_Projecoes.pdf").

    gl_Position = projection * view * model * model_coefficients;

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(0.0,1.0,1.0,0.0));

    // Posição do vértice atual no sistema de coordenadas global (World).
    position_world = model * model_coefficients;

	position_model = model_coefficients;
    // Normal do vértice atual no sistema de coordenadas global (World).
    // Veja slide 94 do documento "Aula_07_Transformacoes_Geometricas_3D.pdf".
    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;
    // Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
    texcoords = texture_coefficients;

    vec3 Kd; // Refletância difusa
    vec3 Ka; // Refletância ambiente
	vec3 I;
	vec3 Ia;
	vec3 lambert_diffuse_term;
	vec3 ambient_term;
    Ka = vec3(0.1,0.1,0.1);
    I = vec3(1.0,1.0,1.0);    						      // Espectro da fonte de iluminação
    Ia = vec3(1.0,1.0,1.0);   						      // Espectro da luz ambiente
    Kd = vec3 (0.1, 0.1, 1.0);
    lambert_diffuse_term = Kd*I*(max(0,dot(normal,l)));       // Termo difuso utilizando a lei dos cossenos de Lambert
    ambient_term = Ka*Ia;     						      // Termo ambiente
    cor_interpolada_pelo_rasterizador = lambert_diffuse_term + ambient_term;


}
