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

                printResult(totalCost, size, *this);
            }
    };

    class BinaryCounter{
        public:

            size_t size = 512;
            char *buffer = new char[size];

            BinaryCounter(){
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

            /*
            void print(int qtt = -1){
                size_t iterations = qtt < 0 ? this->size - 1 : this->size - qtt - 1;
                for (size_t i = 511; i > -1; i--){
                    std::cout<<this->buffer[i];
                }
            }
            */

    };
}

int main(){
    using Amortized::DinamicTable;
    using Amortized::BinaryCounter;
    using std::cout;
    using std::endl;

    BinaryCounter counter;
}