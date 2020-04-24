#include "models.hpp"

using namespace glm;

const double pie = 3.14159;


vec2 get_tex_sphere(vec4 v){
    return vec2( 0.5+atan2(v[1],v[0])/(2*pie), 0.5-asin(v[2])/pie);
}

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

mesh get_icosphere(int recursion_depth){

    mesh icosahedron;
    icosahedron.readObj("models/icosahedron.obj");

    for(int i=0;i<recursion_depth;i++){
        
        vector<face> temp_faces = icosahedron.faces;
        vector<vec4>& vertices = icosahedron.vertices;
        vector<vec2>& texture_coordinates = icosahedron.texture_coordinates;
        vector<vec3>& vertex_normals = icosahedron.vertex_normals;

        icosahedron.faces.clear();

        int vertex_index = vertices.size();

        for(auto f = temp_faces.begin(); f!= temp_faces.end();f++){

            vec4 v1 = vertices[f->v1], v2 = vertices[f->v2], v3 = vertices[f->v3];
            vec4 new_v1 = vec4(glm::normalize(vec3((v2+v3)*0.5f)), 1);
            vec4 new_v2 = vec4(glm::normalize(vec3((v3+v1)*0.5f)), 1);
            vec4 new_v3 = vec4(glm::normalize(vec3((v1+v2)*0.5f)), 1);
            
            vertices.push_back(vec4(vec3(new_v1),1));
            vertices.push_back(vec4(vec3(new_v2),1)); 
            vertices.push_back(vec4(vec3(new_v3),1)); 

            vertex_normals.push_back(vec3(new_v1));
            vertex_normals.push_back(vec3(new_v2));
            vertex_normals.push_back(vec3(new_v3)); 

            texture_coordinates.push_back(get_tex_sphere(new_v1));
            texture_coordinates.push_back(get_tex_sphere(new_v2));
            texture_coordinates.push_back(get_tex_sphere(new_v3));

            face f1,f2,f3,f4;

            f1.v1 = f1.vt1 = f1.vn1 = f->v1;
            f1.v2 = f1.vt2 = f1.vn2 = vertex_index + 2;
            f1.v3 = f1.vt3 = f1.vn3 = vertex_index + 1;

            f2.v1 = f2.vt1 = f2.vn1 = f->v2;
            f2.v2 = f2.vt2 = f2.vn2 = vertex_index;
            f2.v3 = f2.vt3 = f2.vn3 = vertex_index + 2;

            f3.v1 = f3.vt1 = f3.vn1 = f->v3;
            f3.v2 = f3.vt2 = f3.vn2 = vertex_index + 1;
            f3.v3 = f3.vt3 = f3.vn3 = vertex_index;

            f4.v1 = f4.vt1 = f4.vn1 = vertex_index;
            f4.v2 = f4.vt2 = f4.vn2 = vertex_index + 1;
            f4.v3 = f4.vt3 = f4.vn3 = vertex_index + 2;
            
            icosahedron.faces.push_back(f1);
            icosahedron.faces.push_back(f2);
            icosahedron.faces.push_back(f3);
            icosahedron.faces.push_back(f4);

            vertex_index+=3;

        }
    }


    icosahedron.mode = GL_TRIANGLES;
    icosahedron.triangle_strips = 3*icosahedron.faces.size();


    icosahedron.m_vertices->empty();
    icosahedron.m_colors->empty();
    icosahedron.m_uvs->empty();


    for(auto it = icosahedron.faces.begin(); it!=icosahedron.faces.end();++it){
        icosahedron.m_vertices->push_back(icosahedron.vertices[it->v1]);
        icosahedron.m_colors->push_back(icosahedron.vertices[it->v1]);
        icosahedron.m_uvs->push_back(icosahedron.texture_coordinates[it->vt1]);
        icosahedron.m_vertices->push_back(icosahedron.vertices[it->v2]);
        icosahedron.m_colors->push_back(icosahedron.vertices[it->v2]);
        icosahedron.m_uvs->push_back(icosahedron.texture_coordinates[it->vt2]);
        icosahedron.m_vertices->push_back(icosahedron.vertices[it->v3]);
        icosahedron.m_colors->push_back(icosahedron.vertices[it->v3]);
        icosahedron.m_uvs->push_back(icosahedron.texture_coordinates[it->vt3]);
    }

    return icosahedron;
}

void generate_icosahedron(){

    double x,y,z;
    double u,v;
    
    double theta, phi;

    mesh icosahedron;

    x = 0, y = 0, z = 1;
    u = 0.5, v = 1;

    icosahedron.vertices.push_back(vec4(x,y,z,1));
    icosahedron.vertex_normals.push_back(vec3(x,y,z));
    icosahedron.texture_coordinates.push_back(vec2(u,v));

    theta = atan(0.5);
    for(phi = 0; phi <2*pie; phi+= 2*pie/5){
        x = cos(theta) * cos(phi);
        y = cos(theta) * sin(phi);
        z = sin(theta);

        u = 0.5 - theta/pie;
        v = phi/(2*pie);

        icosahedron.vertices.push_back(vec4(x,y,z,1));
        icosahedron.vertex_normals.push_back(vec3(x,y,z));
        icosahedron.texture_coordinates.push_back(vec2(u,v));
    }

    theta = -atan(0.5);
    for(phi = 0; phi <2*pie; phi+= 2*pie/5){

        x = cos(theta) * cos(phi+pie/5);
        y = cos(theta) * sin(phi+pie/5);
        z = sin(theta);

        u = 0.5 - theta/pie;
        v = (phi+pie/5)/(2*pie);

        icosahedron.vertices.push_back(vec4(x,y,z,1));
        icosahedron.vertex_normals.push_back(vec3(x,y,z));
        icosahedron.texture_coordinates.push_back(vec2(u,v));
    }

    x = 0, y = 0, z = -1;
    u = 0.5, v = 0;

    icosahedron.vertices.push_back(vec4(x,y,z,1));
    icosahedron.vertex_normals.push_back(vec3(x,y,z));
    icosahedron.texture_coordinates.push_back(vec2(u,v));



    int v1,v2,v3,num_f;
    glm::vec3 normal;
    face f;

    //face 1
    num_f = 0;
    v1 = 0; v2 = 1; v3 = 2;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 2
    num_f = 1;
    v1 = 0; v2 = 2; v3 = 3;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 3
    num_f = 2;
    v1 = 0; v2 = 3; v3 = 4;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 4
    num_f = 3;
    v1 = 0; v2 = 4; v3 = 5;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 5
    num_f = 4;
    v1 = 0; v2 = 5; v3 = 1;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 6
    num_f = 5;
    v1 = 2; v2 = 1; v3 = 6;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 7
    num_f = 5;
    v1 = 3; v2 = 2; v3 = 7;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 8
    num_f = 7;
    v1 = 4; v2 = 3; v3 = 8;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 9
    num_f = 8;
    v1 = 5; v2 = 4; v3 = 9;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 10
    num_f = 9;
    v1 = 1; v2 = 5; v3 = 10;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 11
    num_f = 10;
    v1 = 1; v2 = 10; v3 = 6;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 12
    num_f = 11;
    v1 = 2; v2 = 6; v3 = 7;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 13
    num_f = 12;
    v1 = 3; v2 = 7; v3 = 8;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 14
    num_f = 13;
    v1 = 4; v2 = 8; v3 = 9;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 15
    num_f = 14;
    v1 = 5; v2 = 9; v3 = 10;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 16
    num_f = 15;
    v1 = 6; v2 = 10; v3 = 11;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);


    //face 17
    num_f = 16;
    v1 = 7; v2 = 6; v3 = 11;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 18
    num_f = 18;
    v1 = 8; v2 = 7; v3 = 11;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 19
    num_f = 18;
    v1 = 9; v2 = 8; v3 = 11;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    //face 20
    num_f = 19;
    v1 = 10; v2 = 9; v3 = 11;
    f.v1 = v1, f.v2 = v2, f.v3 = v3;
    f.vt1 = v1, f.vt2 = v2, f.vt3 = v3;
    f.vn1 = v1, f.vn2 = v2, f.vn3 = v3;
    icosahedron.faces.push_back(f);

    icosahedron.saveObj("models/icosahedron.obj");

}

