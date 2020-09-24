#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Celula{
    public:
    Celula* esq;
    Celula* dir;
    int elemento;
    
    Celula(int elemento){
        this->elemento = elemento;
    }
    
};

class FilaCircular{
    public:
    Celula* primeiro;
    Celula* ultimo;
    int tamanho;
    
    FilaCircular(){
        primeiro = nullptr;
        ultimo = nullptr;
        tamanho = 0;
    } 

    void inserir(int elemento){
        if(tamanho == 0){
            ultimo = new Celula(elemento);
            primeiro = ultimo;  // quando tam == 1 primeiro e ultimo são iguais
            tamanho++; // att o tamanho
        }
        else{
            Celula * temp = ultimo;
            ultimo = new Celula(elemento);
            ultimo->dir = primeiro; // fecha o circulo novamente
            primeiro->esq = ultimo; //

            //agora ligar o antigo ultimo(temp) ao novo ultimo
            temp -> dir = ultimo;
            ultimo -> esq = temp;
            tamanho++;   
        }
        
    }

    int remover(Celula* ponteiro){
        int elemento_removido = -1;
        if(tamanho != 0){
            elemento_removido = ponteiro->elemento;
            Celula* temp1 = ponteiro->esq; //vamos tirar o elemento ponteiro do circulo
            Celula* temp2 = ponteiro->dir; // e ligar o da esq e dir, um ao outro
            temp1->dir = temp2;
            temp2->esq = temp1;
            //feito
            delete(ponteiro);
                
            tamanho--;
        }
        return elemento_removido;
    }
    
};

class Cassino{
    private:
    Celula* funcionario1;
    Celula* funcionario2;
    FilaCircular partida;
    int N, k, m;
    
    public:
    Cassino(int N, int k, int m){
        this->N = N ;
        this->k = k;
        this->m = m;
        partida = FilaCircular();

        for(int i = 1; i <= N; i++ )
            partida.inserir(i);
        
    }
    
    void partida_cassino(){
        stringstream saida;
        funcionario1 = partida.primeiro; // partindo do primeiro apostador
        funcionario2 = partida.ultimo;   // partindo do ultimo

        while(partida.tamanho >= 1){
            for(int i = 0; i < k-1; i++)
                funcionario1 = funcionario1->dir; // movendo o funcionario ate o apostador
            for(int i = 0; i < m-1; i++)          // (horario)
                funcionario2 = funcionario2->esq;// movendo o funcionario ate o apostador
                                                  // (anti-horario)

            if(funcionario1->elemento == funcionario2->elemento){
                // participante recebe um brinde exclusivo
                Celula * proximo_participante1 = funcionario1->dir; // antes de remover salvar o prox do funcionario
                funcionario2 = funcionario2->esq;

                int apostador_removido = partida.remover(funcionario1);

                funcionario1 = proximo_participante1;
                
                saida << "  " << apostador_removido << "," ;
            }
            else{
                Celula * proximo_participante1 = funcionario1->dir; // antes de remover salvar o prox do funcionario
                Celula * proximo_participante2 = funcionario2->esq;

                if(funcionario1->elemento == funcionario2->esq->elemento){ // prevenindo erro
                    proximo_participante2 = proximo_participante2->esq;
                }
                if(funcionario2->elemento == funcionario1->dir->elemento){ // prevenindo erro
                   proximo_participante1 = proximo_participante1->dir;
                }
                int apostador_removido1 = partida.remover(funcionario1);
                funcionario1 = proximo_participante1;
                int apostador_removido2 = partida.remover(funcionario2);
                funcionario2 = proximo_participante2;
                
               
                
                saida << "  " << apostador_removido1 ;
                saida << "  " << apostador_removido2 << ",";

            }
        }
        string result = saida.str().replace(saida.str().length()-1, 1 , "\n");
        cout << result;
    }


};



int main(){
    int N, k, m;
    cin >> N >> k >> m;

    while( N && k && m ){
        Cassino partida = Cassino(N, k, m);
        partida.partida_cassino();
        cin >> N >> k >> m;
    }
    return 0;
}

