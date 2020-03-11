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
                            std::function<void(int, int, DinamicTable&)> printResult, 
                            std::function<void(int, int, int)> printPartial = nullptr){

                DinamicTable table;

                int totalCost = 0;

                for (size_t i = 0; i < count; i++){
                    int cost;
                    cost = table.insert(vector[i]);
                    totalCost += cost;

                    printPartial && printPartial(vector[i], table.size, cost);
                }

                printResult(totalCost, size, table);
            }
    };
}

/*
template<std::size_t N>
int floats(const float(&r)[N]){
    std::cout << N << ":";
    for(size_t i = 0; i < N; i++)
        std::cout << " " << r[i];
    std::cout << std::endl;
    return 0;
}*/


int main(){
    using Amortized::DinamicTable;
    using std::cout;
    using std::endl;
}