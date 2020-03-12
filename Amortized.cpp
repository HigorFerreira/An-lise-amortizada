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
                    printPartial(vector[i], this->size, cost) :
                    void();
                }

                printResult((float)totalCost, (float)size, *this);
            }
    };

    class BinaryCounter{
        public:
            int size = 5;
            int *vector = new int[size];

            void iterate(std::function<void(int)> callback = 0){
                if(!callback) return;

                for (size_t i = 0; i < this->size; i++){
                    callback(this->vector[i]);
                }
            }

            void iterate(std::function<void(int, int)> callback = 0){
                if(!callback) return;

                for (size_t i = 0; i < this->size; i++){
                    callback(this->vector[i], i);
                }
            }

            void iterate(std::function<void(int, int, int*)> callback = 0){
                if(!callback) return;

                for (size_t i = 0; i < this->size; i++){
                    callback(this->vector[i], i, this->vector);
                }
            }

            BinaryCounter(){
                this->iterate([](int element, int index, int *vector){
                    vector[index] = 0;
                });
            }

            bool isBufferZero(){
                bool iszero = true;
                this->iterate([&](int element){
                    if(!element) iszero = false;
                });
                return iszero;
            }


    };
}

int main(){
    using Amortized::DinamicTable;
    using std::cout;
    using std::endl;
}