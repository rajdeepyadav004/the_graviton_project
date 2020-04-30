#include "rigidBody.hpp"

using namespace std;



rigidbody::rigidbody(){}

rigidbody::~rigidbody(){}

rigidbody::rigidbody(const rigidbody& rbd){
    this->m_mass = rbd.m_mass;
    this->m_radius = rbd.m_radius;
    this->m_position = rbd.m_position;
    this->m_velocity = rbd.m_velocity;
    this->m_force = rbd.m_force;
}

rigidbody::rigidbody(double arg_mass, double arg_radius, Row<double> arg_position, Row<double> arg_velocity){

    m_mass = arg_mass;
    m_radius = arg_radius;
    m_position = arg_position;
    m_velocity = arg_velocity;
    m_force = {0,0,0};

}

void rigidbody::add_force(Row<double> arg_force){
    m_force += arg_force;
}

void rigidbody::update(double delta_t){

    //Euler Update

    m_velocity += m_force * delta_t / m_mass; 
    m_position += m_velocity * delta_t;

    m_force = {0,0,0};
}

void rigidbody::print(){
    cout<<"\tRigidbody: "<<endl;
    cout<<"\t\tmass: "<<m_mass<<endl;
    cout<<"\t\tposition: "<<m_position<<endl;
    cout<<"\t\tvelocity: "<<m_velocity<<endl;
}

void simulate_gravity(vector<rigidbody>& rbds, int iterations){

    arma::Row<double> v1, v2; 
    double m1, m2, r1, r2, distance; 

    bool changed[rbds.size()][rbds.size()];
    for(int i=0;i<rbds.size();i++){
        for(int j=0;j<rbds.size();j++){
            changed[i][j] = false;
        }
    }

    for(int i=0;i<iterations;i++){
        for(int i=0;i<rbds.size();i++){
            for(int j=i+1;j<rbds.size();j++){

                arma::Row<double> force_on_j;
                rigidbody rbd_i = rbds[i];
                rigidbody rbd_j = rbds[j];

                m1 = rbd_i.m_mass;
                m2 = rbd_j.m_mass;
                r1 = rbd_i.m_radius;
                r2 = rbd_j.m_radius;

                arma::Row<double> jToi = rbd_i.m_position - rbd_j.m_position;

                distance = arma::norm(jToi);


                v1 = jToi*arma::dot(rbds[i].m_velocity, jToi)/pow(distance,2);
                v2 = jToi*arma::dot(rbds[j].m_velocity, jToi)/pow(distance,2);

                if(distance < r1 + r2 && !changed[i][j]){

                    changed[i][j] = true;
                    rbds[i].m_velocity += (m1*v1+m2*v2-m2*e*(v1-v2))/(m1+m2) -v1;
                    rbds[j].m_velocity +=  (m1*v1+m2*v2+m1*e*(v1-v2))/(m1+m2)-v2;
                }

                if(distance > r1+r2 && changed[i][j]){
                    changed[i][j] = false;
                }

                if(distance < 0.01)
                    continue;

                force_on_j = (G * m1 * m2 * (jToi)) / pow(distance,3) ;


                rbds[i].add_force( - force_on_j);
                rbds[j].add_force( force_on_j );

        
            }
        }

        for(auto it = rbds.begin();it!= rbds.end();it++){
            it->update(delta_time);
        }
    }
}