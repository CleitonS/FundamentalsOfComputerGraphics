#ifndef BULLLETS_H_INCLUDED
#define BULLLETS_H_INCLUDED


#include <ctime>
#include <cstdlib>


extern GLint model_uniform;
extern struct Bullet listBullets[MAX_BULLETS];//guarda apena MAX_BULLETS de tiro, ap�s, come�a a reescrever;
extern void DrawVirtualObject(char* object_name);
extern GLint object_id_uniform;




struct Bullet{
    glm::mat4 model;
    char * name;
	struct ObjModel *Obj;
	float velocidade;
	glm::vec4 vec_direcao; //dire��o que a bullet segue
	glm::vec4 posIni;      //posicao que ela come�a
    public:

        create(char *nameDesc, glm::vec4 vec_dir,glm::vec4 posInicial,struct ObjModel* Object ){
            posIni = posInicial;
            model = Matrix_Identity() *
                    Matrix_Translate(posIni.x,posIni.y,posIni.z) *
					Matrix_Scale(0.01f, 0.01f, 0.01f);
			velocidade = 300.0f;
            vec_direcao = vec_dir;
            Obj = Object;
            name = nameDesc;

        }
		UpdatePosition(float interval){
			model = model * Matrix_Translate(vec_direcao.x*interval*velocidade,vec_direcao.y*interval*velocidade, vec_direcao.z*interval*velocidade);

		}
};

/*Com base na diferen�a de tempo entre execu��es do loop, atualiza a posi��o de todas as bullets*/
void UpdateAllBullets(float interval){

    for(int i= 0; i<MAX_BULLETS;i++)
    {
            listBullets[i].UpdatePosition(interval);


            glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(listBullets[i].model));
            glUniform1i(object_id_uniform, CUBE);
            DrawVirtualObject(listBullets[i].name);


    }


}

/*fun��o para criar um novo objeto*/
void createBullets(char *name, glm::vec4 vec_direcao,glm::vec4 posIni,struct ObjModel* Object, int i){


			struct Bullet newBullet;
			newBullet.create(name,vec_direcao,posIni,Object );
            listBullets[i] = newBullet;

            return;


    printf("ERRO na cria��o de objeto tipo 'Bullet'\n");
}






#endif // BULLLETS_H_INCLUDED
