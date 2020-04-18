#include "world.hpp"

using namespace std;

world::world(){

}

world::~world(){

}

world::world(const world& world1){
    this->m_rbds = world1.m_rbds;
    this->m_render_comps = world1.m_render_comps;
}

void world::insert(rigidbody arg_rbd, render_component arg_render_comp){

    m_rbds.push_back(arg_rbd);
    m_render_comps.push_back(arg_render_comp);

}

void world::simulate(int iterations){

    simulate_gravity(m_rbds, iterations);
    for(int i=0;i<m_rbds.size();i++){

        arma::Row<double> position = m_rbds[i].m_position;
        m_render_comps[i].set_position( glm::vec3(position[0],position[1],position[2]));
    }

}

void world::render(){
    render_gl(m_render_comps);
}