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
    };
}

int main(){
    using Amortized::DinamicTable;
    using Amortized::BinaryCounter;
    using std::cout;
    using std::endl;
    
    DinamicTable table;

    table.printVector<5>({ 1, 2, 3, 4, 5 }, [](float cost, float qtt, DinamicTable tb){
        cout<<cost<<endl;
        cout<<qtt<<endl;
        cout<<cost/qtt<<endl;
        for (size_t i = 0; i < tb.size; i++){
            cout<<tb.table[i]<<" ";
        }
        cout<<endl;
        
    });
}