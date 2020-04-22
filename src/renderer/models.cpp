#include "models.hpp"

using namespace glm;

const double pie = 3.14159;


double restrain(double u){
    if(u < 0)
        return 0;
    if(u > 1)
        return 1;
    else return u;


}

vec4 sphere_color_transform(vec4 vertex){

    glm::vec3 axis = glm::normalize(glm::cross(vec3(0,0,1), vec3(1,1,1)));
    float angle = acos( glm::dot(glm::normalize(vec3(0,0,1)),glm::normalize(vec3(1,1,1))));

    return ((glm::rotate(glm::mat4(1.f),angle*-1.f, axis) * vertex )+vec4(1,1,1,1))*0.5f;
}


mesh get_cube(){

    vector<vec4> vertices = {
        vec4(1.f, 1.f, 1.f,1.f),
        vec4(-1.f, 1.f, 1.f,1.f),
        vec4(1.f, 1.f, -1.f,1.f),
        vec4(-1.f, 1.f, -1.f,1.f),
        vec4(1.f, -1.f, 1.f,1.f),
        vec4(-1.f, -1.f, 1.f,1.f),
        vec4(-1.f, -1.f, -1.f,1.f),
        vec4(1.f, -1.f, -1.f,1.f),
    };

    vector<vec4> colors = {
        vec4(1.f, 1.f, 1.f,1.f),
        vec4(0.f, 1.f, 1.f,1.f),
        vec4(1.f, 1.f, 0.f,1.f),
        vec4(0.f, 1.f, 0.f,1.f),
        vec4(1.f, 0.f, 1.f,1.f),
        vec4(0.f, 0.f, 1.f,1.f),
        vec4(0.f, 0.f, 0.f,1.f),
        vec4(1.f, 0.f, 0.f,1.f),
    };

    

    vector<vec4> * cube_vertices = new vector<vec4>;
    vector<vec4>* cube_colors = new vector<vec4>;

    vector<vec2>* cube_uvs = new vector<vec2>;

    *cube_vertices = {
        vertices[3],
        vertices[2],
        vertices[6],
        vertices[7],
        vertices[4],
        vertices[2],
        vertices[0],
        vertices[3],
        vertices[1],
        vertices[6],
        vertices[5],
        vertices[4],
        vertices[1],
        vertices[0],
    };

    *cube_colors = {
        colors[3],
        colors[2],
        colors[6],
        colors[7],
        colors[4],
        colors[2],
        colors[0],
        colors[3],
        colors[1],
        colors[6],
        colors[5],
        colors[4],
        colors[1],
        colors[0],
    };

    for(auto it = cube_vertices->begin(); it!= cube_vertices->end();++it){
        double x = (*it)[0], y = (*it)[1], z = (*it)[2];
        double u = restrain(0.5 + atan2(z,x) / (2*pie));
        double v = restrain(0.5 - asin(y) / pie);
        cube_uvs->push_back(vec2(u,v));
    }

    return mesh(cube_vertices, cube_colors, cube_uvs, 14, GL_TRIANGLE_STRIP);
}

// mesh get_sexy_sphere(int tesselation){

//     double step_lat = pie / (2*tesselation), step_lon = pie / tesselation;
//     vector<vec4> *sphere_vertices = new vector<vec4>, *sphere_colors = new vector<vec4>;

//     vector<vector<vec4>> vertices;

//     for(double theta = -pie/2; theta<=pie/2; theta+=step_lat){
//         vector<vec4> temp;
//         for(double phi = 0; phi<2*pie; phi += step_lon){

//             double x,y,z;

//             x = cos(theta)*cos(phi);
//             y = cos(theta)*sin(phi);
//             z = sin(theta)*sin(phi);

//             sphere_vertices->push_back(vec4(x,y,z,1));
//             sphere_colors->push_back((vec4(x,y,z,1)+vec4(1,1,1,1))*0.5f);
//         }
//     }    



//     // return mesh(sphere_vertices, sphere_colors, sphere_vertices->size(), GL_TRIANGLE_STRIP);
//     return mesh(sphere_vertices, sphere_colors, sphere_vertices->size(), GL_TRIANGLES);

// }

mesh get_sphere(int tesselation){

    double step_lat = pie / (2*tesselation), step_lon = pie / tesselation;
    vector<vec4> *sphere_vertices = new vector<vec4>, *sphere_colors = new vector<vec4>;
    vector<vec2> *sphere_uvs = new vector<vec2>;

    vector<vector<vec4>> vertices;
    vector<vector<vec2>> textures;

    for(double theta = -pie/2; theta<=pie/2; theta+=step_lat){
        vector<vec4> temp1;
        vector<vec2> temp2;
        for(double phi = 0; phi<2*pie; phi += step_lon){

            double x,y,z;

            x = cos(theta)*cos(phi);
            y = cos(theta)*sin(phi);
            z = sin(theta);

            temp1.push_back(vec4(x,y,z,1));
            
            double u = 0.5 + atan2(z,x) / (2*pie);
            double v = 0.5 - asin(y) / pie;

            // u = phi / (2*pie);
            // v = 0.5 + theta / (pie);


            temp2.push_back(vec2(u,v));
        }

        vertices.push_back(temp1);
        textures.push_back(temp2);
    }    


    int num_lat = vertices.size() - 1;
    int num_lon = vertices[0].size();
    for(int lat = 0; lat < num_lat; lat++){
        for(int lon = 0; lon<num_lon; lon++){
            sphere_vertices->push_back(vertices[lat][lon]);
            sphere_vertices->push_back(vertices[lat+1][lon]);
            sphere_uvs->push_back(textures[lat][lon]);
            sphere_uvs->push_back(textures[lat+1][lon]);
            sphere_colors->push_back(sphere_color_transform(vertices[lat][lon]));
            sphere_colors->push_back(sphere_color_transform(vertices[lat+1][lon]));

        }
    }

    for(int lon=0;lon<num_lon;lon++){
        sphere_vertices->push_back(vertices[num_lat-1][lon]);
        sphere_vertices->push_back(vec4(0,0,1,1));
        sphere_uvs->push_back(textures[num_lat-1][lon]);
        sphere_uvs->push_back(vec2(lon/num_lon,0));
        sphere_colors->push_back(sphere_color_transform(vertices[num_lat-1][lon]));
        sphere_colors->push_back(sphere_color_transform(vec4(0,0,1,1)));
    }

    return mesh(sphere_vertices, sphere_colors, sphere_uvs,sphere_vertices->size(), GL_TRIANGLE_STRIP);

}
