#include <iostream>

using namespace std;

class Search{
public:
    static bool sequential(int* array, int numElem, int element){
        for (int i = 0; i < numElem; i++){
            if (*(array+i) == element){
                cout<<"The element ("<<*(array+i)<<") is in array["<<i<<"]\n";
                return true;
            }
        }
        cout<<"The element ("<<element<<") is not in array\n";
        return false;
    }

    static bool binary(int* array, int numElem, int element){
        int top = numElem-1, bottom = 0, half;
        while (bottom <= top){
            half = (bottom+top)/2;
            if (*(array+half) == element){
                cout<<"Element found ("<<*(array+half)<<") in array["<<half<<"]\n";
                return true;
            }
            if (element > *(array+half)){
                bottom = half+1;
            }
            else if (element < *(array+half)){
                top = half-1;
            }
        }
        cout<<"Element not found ("<<element<<") in array\n";
        return false;
    }
};

int main (){
    int nums, num;
    cout<<"Arrays' positions => ";
    cin>>nums;

    int* array = new int[nums]; 

    for (int i = 0; i < nums; i++){
        cout<<"Array position ["<<i<<"] => ";
        cin>>*(array+i);
    }

    cout<<"What's number do you want to look for? => ";
    cin>>num;

    Search::sequential(array, nums, num);
    Search::binary(array, nums, num);

    return 0;
}