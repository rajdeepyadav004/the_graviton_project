
#define ARMA_ALLOW_FAKE_GCC
#include <iostream>
#include <armadillo>
#include <vector>
using namespace std;
using namespace arma;

const double G = 6.67 * 1e-11 ; 
const double e = 1;
const double delta_time = 1;

class rigidbody{

    double m_mass, m_radius;
    Row<double> m_velocity;
    Row<double> m_force;

public:
    Row<double> m_position;
    rigidbody();
    ~rigidbody();
    rigidbody(double arg_mass, double arg_radius, Row<double> arg_positions, Row<double> arg_velocity);
    rigidbody(const rigidbody& rbd);
    void add_force(Row<double> arg_force);
    void update(double delta_t);
    void print();

    friend void simulate_gravity(vector<rigidbody>& rbds, int iterations);
};

void simulate_gravity(vector<rigidbody>& rbds);