#include<iostream>
#include<functional>
#include<vector>


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
        std::vector<bool> *num = new std::vector<bool>;

        void iterate(std::function<void(bool element, int index, std::vector<bool> *vector)> callback){
            for (size_t i = 0; i < num->size(); i++){
                callback(num->at(i), i, this->num);
            }
            
        }

        bool isFull(){
            bool isFull = true;
            this->iterate([&](bool element, int index, std::vector<bool> *vt){
                isFull = element ? true : false;
            });
            return isFull;
        }

        int increment(){
            int cost = 0;

            if(num->size() == 0){
                num->push_back(true);
                return 1;
            }
            else{
                if(this->isFull()){
                    this->iterate([&](bool element, int index, std::vector<bool> *vt){
                        vt->at(index) = false;
                        cost++;
                    });
                    this->num->push_back(true);
                    cost++;
                    //Chamada recursiva
                    return cost;
                }
                else{
                    
                }
            }
        }
    };
}

int main(){
    using Amortized::DinamicTable;
    using Amortized::BinaryCounter;
    using std::cout;
    using std::endl;
}