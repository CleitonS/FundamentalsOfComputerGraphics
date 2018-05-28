#include <ctime>
#include <cstdlib>


extern GLint model_uniform;
extern struct Monster listMonster[MAX_MONSTER];
extern void DrawVirtualObject(char* object_name);
extern GLint object_id_uniform;
float randomNumber();



struct Monster{
    glm::mat4 model;
    char * name;
    int typeIlumination;
	struct ObjModel *Obj;
	bool enable = false;
	float velocidade;
    public:
        Monster(){
            enable = false;
        }
        create(char *nameDesc, int typeIluminationIn, struct ObjModel* Object){
            float posIni = randomNumber();
            printf("Pos Inic: %f", posIni);

            model = Matrix_Identity() *
                    Matrix_Translate(posIni,0.0f,-6.0f) *
					Matrix_Scale(0.2f, 0.2f, 0.2f);
			velocidade = 3.0f;
            Obj = Object;
            name = nameDesc;
            typeIlumination = typeIluminationIn;
            enable = true;
        }
		UpdatePosition(float interval){
			model = model * Matrix_Translate(0.0f,0.0f, interval * velocidade);

		}
};

/*Com base na diferença de tempo entre execuções do loop, atualiza a posição do
monstro na tela*/
void UpdateAllMonsters(float interval){
    for (int i = 0; i< MAX_MONSTER; i++){
        if(listMonster[i].enable == true){
            glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(listMonster[i].model));
            glUniform1i(object_id_uniform, listMonster[i].typeIlumination);
            DrawVirtualObject(listMonster[i].name);
            listMonster[i].UpdatePosition(interval);
        }
    }
}

/*função para criar um novo objeto*/
void createMonster(char *name, int typeIlumination, ObjModel *Obj){
    for(int i = 0; i< MAX_MONSTER; i++){
        if (listMonster[i].enable == false ){
                printf("Criando\n");
			struct Monster newMonster;
			newMonster.create(name, typeIlumination,Obj );
            listMonster[i] = newMonster;
            return;
        }
    }
    printf("ERRO na criação de objeto tipo 'Monster'\n");
}

float randomNumber(){
    return ((rand())%4 - 2) + 0.1*((rand())%9) + 0.01*((rand())%9);
}

