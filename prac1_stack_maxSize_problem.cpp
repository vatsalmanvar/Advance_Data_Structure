#include<bits/stdc++.h>
using namespace std;

void printMessage(int capacity){
    cout<<"Threshold crossed. \nSo the stack size is now increased."<<endl;
    cout<<"New Stack Size: "<<capacity;
    return;
}

void _push(vector<int> &v, double &threshold, int &currSize, int &capacity){
    if(capacity*threshold <= currSize){
        capacity *= 2;
        printMessage(capacity);
        vector<int> temp(v.size());
        for(int i=0; i<v.size(); i++) temp[i] = v[i];
        v.resize(capacity, 0);
        for(int i=0; i<temp.size(); i++) v[i] = temp[i];
    }
    cout<<endl<<"-->";
    int x;
    cin>>x;
    v[currSize++] = x;
    return;
}

void _pop(vector<int> &v, int &currSize){
    if(currSize<=0){
        cout<<"!!! Underflow "<<endl;
        return;
    }
    v[--currSize] = 0;
    return;
}

int main(){
    int i, j, repeat = 1, choice;
    int initialSize, currSize=0, capacity;
    double threshold;

    cout << "Enter the initial size of the stack: ";
    cin >> initialSize;
    cout << "Enter the threshold (0<value<=1): ";
    cin >> threshold;

    capacity = initialSize;
    vector<int> v(capacity, 0);

    while(repeat){
        cout<<"Choose: 1) Push 2) Pop 3) Exit: ";
        cin >> choice;
        switch(choice){
            case 1:
                _push(v, threshold, currSize, capacity);
                break;
            
            case 2:
                _pop(v, currSize);
                break;
            
            case 3:
                repeat = 0;
                break;

            default:
                cout<<"Invalid Input!!!"<<endl;
                break;
        }
        if(repeat == 0) break;
        cout<<endl<<"-----------------------------------"<<endl;
        cout<<"capacity: "<<capacity<<" currSize: "<<currSize<<endl;
        for(int i=0; i<currSize; i++) cout<<v[i]<<" ";
        cout<<endl;
        cout<<endl<<"-----------------------------------"<<endl;
    }
    return 0;
}