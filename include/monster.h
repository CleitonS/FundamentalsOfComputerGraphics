#include <ctime>
#include <cstdlib>


extern GLint model_uniform;
extern struct Monster listMonster[MAX_MONSTER];
extern void DrawVirtualObject(char* object_name);
extern GLint object_id_uniform;
float randomPosition();
int randomIlumination();


struct Monster{
    glm::mat4 model;
    char * name;
    int typeIlumination;
	struct ObjModel *Obj;
	bool enable = false;
	float velocidade;
	int life = LIFE_MONSTER;
    public:
        Monster(){
            enable = false;
        }
        create(char *nameDesc, int typeIluminationIn, struct ObjModel* Object,float posIni){
             posIni = posIni;
            //printf("Pos Inic: %f", posIni);

            model = Matrix_Identity() *
                    Matrix_Translate(posIni,0.0f,-6.0f) *
					Matrix_Scale(0.2f, 0.2f, 0.2f);
			velocidade = 3.0f;
            Obj = Object;
            name = nameDesc;
            int numRrand = randomIlumination();
            if (numRrand == 0)
                typeIlumination = MONSTER_BLUE;
            else if (numRrand == 1)
                typeIlumination = MONSTER_GREEN;
            else
                typeIlumination = MONSTER_RED;
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
void createMonster(char *name, int typeIlumination, ObjModel *Obj,int i){
        if (listMonster[i].enable == false ){
                //printf("Criando\n");
			struct Monster newMonster;
			newMonster.create(name, typeIlumination,Obj,randomPosition() );
            listMonster[i] = newMonster;
            return;
    }
    printf("ERRO na criação de objeto tipo 'Monster'\n");
}

float randomPosition(){
    return ((rand())%4 - 2) + 0.1*((rand())%9) + 0.01*((rand())%9);
}

int randomIlumination(){
    return ((rand())%3); //número entre 0 e 2
}


void Destroi_monstro(int i)
{
    struct Monster monstro_NULL;

    listMonster[i].life--;
    if(listMonster[i].life<=0)
    {
        monstro_NULL.create("NULL",0,listMonster[i].Obj,20.0f);
        listMonster[i] = monstro_NULL;
    }
}


void RespawnMonsters()
{
    for(int i = 0; i<MAX_MONSTER;i++)
        if(listMonster[i].name == "NULL"){
                listMonster[i].enable = false;
            createMonster("cube", 1, listMonster[i].Obj,i);
            return;
        }
}
