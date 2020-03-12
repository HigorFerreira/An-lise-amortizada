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

            template<std::size_t size>
            void printVector(const int(&vector)[size], 
                            std::function<void(float, float, DinamicTable&)> printResult, 
                            std::function<void(int, int, int)> printPartial = 0){

                DinamicTable table;

                int totalCost = 0;

                for (size_t i = 0; i < size; i++){
                    int cost;
                    cost = table.insert(vector[i]);
                    totalCost += cost;

                    printPartial ?
                    printPartial(vector[i], table.size, cost) :
                    void();
                }

                printResult((float)totalCost, (float)size, table);
            }
    };
}

int main(){
    using Amortized::DinamicTable;
    using std::cout;
    using std::endl;

    DinamicTable table;

    table.printVector<6>({ 31, 5, 4, 3, 2, 1 }, [&](float custo, float elementos, DinamicTable tb){
        cout<<custo<<endl;
        cout<<elementos<<endl;
        cout<<custo/elementos<<endl;
    }, [&](int elemnt, int tableSize, int cost){
        cout<<"Elemento "<<elemnt<<" Tamanho da tabela "<<tableSize<<" Custo "<<cost<<endl;
    });
}