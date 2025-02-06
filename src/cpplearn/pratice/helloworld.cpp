#include <iostream>
#include <ostream>
#include "color.h"
#include "funcs.h"
#include "program/linked_list.cpp"
#include "program/bin_search_tree.cpp"
#include "program/file_option.cpp"
#include "program/multi_thread_queue.cpp"

using namespace std;

// _Thread_local int e = 3; // thread duration
void myPrint(string color, string var);

int main(int argc, char* argv[]){
    myPrint(RED,"agrm pratice");
    argmPractice(argc, argv);

    myPrint(RED, "valvar function");
    int nums[argc-1];
    for(int i=argc-1; i>0; i--){
        nums[i-1] = (argv[i])[0] - '0';
    }
    varFuncPratice(1,nums);


    int index,len,len_g;
    string funcs_name[] = {
        "hello world","type practice","array pratice","func pratice","loop pratice","goto pratice","promotion pratice",
        "extern pratice","qualifiers pratice","inlineFunc pratice","c++ if pratice","struct pratice","union pratice",
        "bit options","typedef pratice","enum pratice","thread practice","mutex pratice","heap pratice","assertions pratice",
        "module pratice","reference pratice","range pratice","namespace pratice","class pratice","virtualFunc pratice",
        "friendFunc pratice","operator pratice","structBind pratice","lambda pratice","exception handle","template pratice",
        "smart ptr"
    };
    string program_name[] = {"linked list","bin smessageearch tree","file copy","multi_thread_queue"};
    void (*funcs_body[])() = {
        helloWorld,typePractice,arrayPractice,funcPractice,loopPractice,gotoPractice,promotionPra,durofobject,qualifiersPra,inlineFunc,c20ifPratice,
        structPratice,unionPratice,bitOption,typedefPratice,enumPratice,threadPractice,mutexPratice,heapPratice,assertionsPra,
        modulePratice,referPratice,rangePratice,namespacePra,classPratice,virtualFuncPra,friendFuncPratice,operatorPra,structBindPra,
        lambdaPratice,exceptionhandle,templatePra,templatePra
    };
    void (*prog_body[])() = {linkedList,binSearchTree,fileCopy,multi_thread_queue};
    len = sizeof(funcs_name) / sizeof(funcs_name[0]);
    len_g = sizeof(program_name) / sizeof(program_name[0]);
    myPrint(RED, "choose function");
    for (auto i = 0; i<len ; i++) {
        cout << i << ".\t" << funcs_name[i] << endl;
    }
    myPrint(PURPLE, "choose program");
    for (auto i = 0; i<len_g ; i++) {
        cout << len+i << ".\t" << program_name[i] << endl;
    }
    myPrint(RED, "user input");
    while (1) {
        cout << YELLOW << "input function index: ";
        cin >> index;
        if (index == -1) {
            break;
        }else if(index >= len){
            if (index%len >= len_g) {
                cout << "out of index!" << endl;
                continue;
            }else{
                myPrint(BLUE, program_name[index%len]);
                prog_body[index%len]();
            }
        }
        myPrint(BLUE, funcs_name[index]);
        funcs_body[index]();

    }
    return 0;
}

void myPrint(string color,string var){
    cout << color;
    for (int i = 0; i<9; i++){
        cout << "=";
    }
    cout << "\t" << var << "\t";
    for (int i = 0; i<9; i++){
        cout << "=";
    }
    cout << NONE << endl;
}
