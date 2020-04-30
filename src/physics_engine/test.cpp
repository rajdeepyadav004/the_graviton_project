#include <iostream>
#include "rigidBody.hpp"

int main(){

    vector<rigidbody> rbds;

    rbds.push_back(rigidbody(1000,{0,0,0},{0,0,0}));
    rbds.push_back(rigidbody(1,{5,0,0},{0,sqrt(G * 1000 / 5),0}));
    rbds.push_back(rigidbody(1,{0,5,0},{sqrt(G * 1000 / 5),0,0}));

    simulate_gravity(rbds, 10000);
    
    rbds[0].print();
    rbds[1].print();

    return 0;
};