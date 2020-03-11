#include<iostream>
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
    };
}

int main(){
    using Amortized::DinamicTable;
    using std::cout;
    using std::endl;

    DinamicTable table;
    int cost, element;

    element = 32;
    cost = table.insert(element);
    cout<<"Elemento: "<<element<<"     Tamanho: "<<table.size<<"     Custo: "<<cost<<endl;

    element = 2;
    cost = table.insert(element);
    cout<<"Elemento: "<<element<<"     Tamanho: "<<table.size<<"     Custo: "<<cost<<endl;

    element = 3;
    cost = table.insert(element);
    cout<<"Elemento: "<<element<<"     Tamanho: "<<table.size<<"     Custo: "<<cost<<endl;

    element = 4;
    cost = table.insert(element);
    cout<<"Elemento: "<<element<<"     Tamanho: "<<table.size<<"     Custo: "<<cost<<endl;

    element = 5;
    cost = table.insert(element);
    cout<<"Elemento: "<<element<<"     Tamanho: "<<table.size<<"     Custo: "<<cost<<endl;

    element = 6;
    cost = table.insert(element);
    cout<<"Elemento: "<<element<<"     Tamanho: "<<table.size<<"     Custo: "<<cost<<endl;
}