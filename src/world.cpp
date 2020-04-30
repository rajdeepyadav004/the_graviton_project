#include "world.hpp"
#include "xml-parser/pugixml.hpp"

using namespace std;


world::world(GLFWwindow* window ,string xml_scene_file){

    this->window = window;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml_scene_file.c_str());

    pugi::xml_node w = doc.child("world");
    cout<<"Loaded "<<w.attribute("name").value()<<endl;

    pugi::xml_node c = w.child("camera");

    this->camera1 = camera(
        glm::radians(stod(c.child("projection").attribute("fov").value())),
        stod(c.child("projection").attribute("aspect_ratio").value()),
        stod(c.child("projection").attribute("near_clip").value()),
        stod(c.child("projection").attribute("far_clip").value())
    );

    glm::vec3 position, lookat, up;
    position = glm::vec3(
        stod(c.child("position").attribute("x").value()),
        stod(c.child("position").attribute("y").value()),
        stod(c.child("position").attribute("z").value())
    );
    lookat = glm::vec3(
        stod(c.child("lookat").attribute("x").value()),
        stod(c.child("lookat").attribute("y").value()),
        stod(c.child("lookat").attribute("z").value())
    );
    up = glm::vec3(
        stod(c.child("up").attribute("x").value()),
        stod(c.child("up").attribute("y").value()),
        stod(c.child("up").attribute("z").value())
    );

    this->camera1.set_view_param(position, lookat, up);

    pugi::xml_node Objs = w.child("objects");

    for(pugi::xml_node obj=Objs.child("object"); obj; obj =  obj.next_sibling()){

        double mass = stod(obj.child("mass").attribute("m").value());
        double radius = stod(obj.child("radius").attribute("r").value());
        double px,py,pz;
        px = stod(obj.child("position").attribute("x").value());
        py = stod(obj.child("position").attribute("y").value());
        pz = stod(obj.child("position").attribute("z").value());

        double vx,vy,vz;
        vx = stod(obj.child("velocity").attribute("x").value());
        vy = stod(obj.child("velocity").attribute("y").value());
        vz = stod(obj.child("velocity").attribute("z").value());
        mesh mesh1;
        mesh1.readObj(obj.child("mesh").attribute("file").value());
        mesh1.set_texture(obj.child("texture").attribute("file").value());
        this->insert(rigidbody(mass,radius,{px,py,pz},{vx,vy,vz}), render_component(mesh1));
    }

}


world::world(GLFWwindow* arg_window, camera arg_camera){
    this->window = arg_window;
    this->camera1 = arg_camera;
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

    camera1.control(window);
    render_gl(m_render_comps, camera1);
}