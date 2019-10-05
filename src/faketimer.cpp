#include<faketimer/faketimer.h>
#include<fakedb/fakedb.h>
#include<iostream>

using namespace std;

int RunSTA() {
    cout << "-----------------------------------" << endl;
    cout << "Inside Timer" << endl;
    cout << "Performing Static Timing Analysis .." << endl;
    cout << "Current netlist value: " << GetNetList() << endl;
    cout << "-----------------------------------" << endl;
    return GetNetList();
}