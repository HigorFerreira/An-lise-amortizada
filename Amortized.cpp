#include<iostream>
#include<string>
#include<functional>


namespace Amortized {

    class DinamicTable{
        public:
            int size = 1;
            int pointer = 0;
            int *table = new int[size];

            void iterate(std::function<void(int, int)> callback, bool all = false){
                int iterations = all ? size : pointer+1;
                for (size_t i = 0; i < iterations; i++){
                    callback(table[i], (int)i);
                }                
            }
            
        public:
            int insert(int value){
                if(pointer == size){
                    size = size*2;
                    int *newTable = new int[size];

                    iterate([&](int element, int index){
                        newTable[index] = element;
                    });

                    newTable[pointer] = value;
                    int cost = pointer + 1;
                    pointer++;
                    
                    delete []table;
                    table = newTable;

                    return cost;
                }
                else{
                    table[pointer] = value;
                    pointer++;
                    return 1;
                }
            }

            template<std::size_t size>
            void printVector(const int(&vector)[size], 
                            std::function<void(int, int, DinamicTable&)> printResult, 
                            std::function<void(int, int, int, DinamicTable&)> printPartial = 0){

                this->size = 1;
                this->pointer = 0;
                delete []this->table;
                this->table = new int[this->size];

                int totalCost = 0;

                for (size_t i = 0; i < size; i++){
                    int cost;
                    cost = this->insert(vector[i]);
                    totalCost += cost;

                    printPartial ?
                    printPartial(vector[i], this->size, cost, *this) :
                    void();
                }

                printResult(totalCost, size, *this);
            }
    };

    class BinaryCounter{
        public:

            size_t size;
            char *buffer;

            BinaryCounter(size_t size = 0){
                this->size = size ? size : 512;
                this->buffer = new char[this->size];
                for (size_t i = 0; i < this->size; i++){
                    this->buffer[i] = '0';
                }
            }            

        public:
            unsigned int increment(){
                unsigned int cost = 0, i = 0;

                while( i < this->size && this->buffer[i] == '1' ){
                    this->buffer[i] = '0';
                    cost++;
                    i++;
                }
                if( i < this->size ){
                    this->buffer[i] = '1';
                    cost++;
                }

                return cost;
            }
    };
}

int main(){
    using Amortized::DinamicTable;
    using Amortized::BinaryCounter;
    using std::cout;
    using std::endl;

    /**
     * ESTE TRABALHO SE REFERE � TABELA DIN�MICA
     * Alunos:
     *      - Higor Ferreira Alves Santos
     *      - La�s Pereira Felipe
     * 
     * O que ser� desenvolvido
     *      - 1.	A aula de hoje � dedicada a implementa��o do algoritmo TABELAS DIN�MICAS, desenvolvido em sala.
     *      - 2.	Este algoritmo dever� ser implementado em C++ pelos alunos, portanto n�o haver� aula te�rica.
     *      - 3.	O aluno dever� executar este algoritmo para estimar o custo amortizado, conforme mostrado em sala com 10 (dez inser��es).
     *      - 4.	Dever�o ser executados para 10 inser��es e mostrado o custo de cada execu��o, imprimindo a tabela e os valores do custo, a cada inser��o.
     *      - 5.	Ao final, o custo amortizado, custo m�dio, dever� ser calculado.
     * */

    DinamicTable table;

    table.printVector<10>({ 55, 10, 20, 12, 15, 24, 15, 18, 18, 10 },
        [](int totalCost, int tableSize, DinamicTable table){
            cout<<"\nCUSTO AMORTIZADO: "<<(double)totalCost/tableSize<<endl<<endl;
        },
        [](int insertedElement, int size, int cost, DinamicTable table){
            cout<<"ELEMENTO INSERIDO: "<<insertedElement<<"    =====   CUSTO: "<<cost<<"   [ ";
            for (size_t i = 0; i < size; i++){
                cout<<table.table[i]<<", ";
            }
            cout<<"]\n";
        }
    );
}