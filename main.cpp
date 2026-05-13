#include "CampusSystem.h"
#include "CampusExceptions.h"
#include <iostream>
using namespace std;

int main(){
    system("chcp 65001 > nul");
    try{
        CampusSystem campus;
        campus.run();
    }catch (const CampusException& e){
        cerr<<"[Fatal] File error: "<<e.what()<<endl;
        cerr<<"Please ensure the data files exist next to the executable.\n";
        return 1;
    }catch (const exception& e){
        cerr<<"[Fatal] Unexpected error: "<<e.what()<<endl;
        return 2;
    }catch (...){
        cerr<<"\n[Fatal] Unknown error occurred. Exiting.\n";
        return 3;
    }
    cout<<"\n[Goodbye] All data has been saved.\n";
    return 0;
}
