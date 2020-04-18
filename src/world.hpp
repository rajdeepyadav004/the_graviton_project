#include <iostream>
#include "renderer/render_component.hpp"
#include "physics_engine/rigidBody.hpp"
#include "renderer/gl_util.hpp"

class world{

    vector<rigidbody> m_rbds;
    vector<render_component> m_render_comps;
    
public:
    world();
    ~world();
    world(const world& world1);
    void insert(rigidbody arg_rbd, render_component arg_render_comp);
    void simulate(int iterations);
    void render();
};