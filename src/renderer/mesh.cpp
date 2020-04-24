
#include "mesh.hpp"
#include <fstream>
#include <string>


vector<string> split( string arg, char splitter){

    vector<string> res;
    string token;
    bool active = true;



    for(auto it=arg.begin(); it!= arg.end(); it++){

        if(*it == '#'){
            res.push_back("#");
            break;
        }


        if(*it == splitter){
            if(active){
                active = false;
                if(!token.empty())
                    res.push_back(token);
                token.clear();
            }
        }
        else{
            if(!active)
                active = true;
            token.push_back(*it);
        }
    }
    if(!token.empty())
        res.push_back(token);
    return res;
}

mesh::mesh(){
    m_vertices = new vector<vec4>;
    m_colors = new vector<vec4>;
    m_uvs = new vector<vec2>;
}

mesh::mesh(vector<vec4>* arg_vertices, vector<vec4>* arg_colors, vector<vec2>* arg_uvs, int arg_triangle_strips, GLenum arg_mode){
    this->m_vertices = arg_vertices;
    this->m_colors = arg_colors;
    this->m_uvs = arg_uvs;
    this->triangle_strips = arg_triangle_strips;
    this->mode = arg_mode;
};  

void mesh::set_texture(const char* arg_file){
    this->texture_file = arg_file;
}


void mesh::readObj(string filename){

    ifstream file(filename);
    string line;

    while(getline(file, line)){

        if(line.empty())
            continue;

        vector<string> splitted = split(line, ' ');

        if(splitted[0] == "#")
            continue;
        
        if(splitted[0] == "v"){
            vertices.push_back(vec4(stod(splitted[1]), stod(splitted[2]), stod(splitted[3]),1));
        }

        else if(splitted[0] == "vt"){
            texture_coordinates.push_back(vec2(stod(splitted[1]), stod(splitted[2])));
        }

        else if(splitted[0] == "vn"){
            vertex_normals.push_back(glm::normalize(vec3(stod(splitted[1]), stod(splitted[2]), stod(splitted[3]))));
        }

        else if(splitted[0] == "f"){

            face f;
            vector<string> first,second,third;
            first = split(splitted[1],'/');
            second = split(splitted[2],'/');
            third = split(splitted[3],'/');

            f.v1 = stoi(first[0]) - 1, f.vt1 = stoi(first[1]) - 1, f.vn1 = stoi(first[2]) - 1;
            f.v2 = stoi(second[0]) - 1, f.vt2 = stoi(second[1]) - 1, f.vn2 = stoi(second[2]) - 1;
            f.v3 = stoi(third[0]) - 1, f.vt3 = stoi(third[1]) - 1, f.vn3 = stoi(third[2]) - 1;
            faces.push_back(f);
        }

        else{
            cerr<<"error in parsing obj, not supported"<<endl;
        }
    }    

    file.close();

    this->mode = GL_TRIANGLES;
    this->triangle_strips = 3*faces.size();

    for(auto it = faces.begin(); it!=faces.end();++it){

        m_vertices->push_back(vertices[it->v1]);
        m_colors->push_back(vertices[it->v1]);
        m_uvs->push_back(texture_coordinates[it->vt1]);
        m_vertices->push_back(vertices[it->v2]);
        m_colors->push_back(vertices[it->v2]);
        m_uvs->push_back(texture_coordinates[it->vt2]);
        m_vertices->push_back(vertices[it->v3]);
        m_colors->push_back(vertices[it->v3]);
        m_uvs->push_back(texture_coordinates[it->vt3]);
    }

}

void mesh::saveObj(string filename){
    ofstream file(filename);

    file<<"# vertices"<<endl;
    for(auto it = vertices.begin(); it!=vertices.end(); it++){
        file<<"v"<<" "<<(*it)[0]<<" "<<(*it)[1]<<" "<<(*it)[2]<<endl;              
    }

    file<<endl<<"# texture coordinates"<<endl;
    for(auto it = texture_coordinates.begin(); it!=texture_coordinates.end(); it++){
        file<<"vt"<<" "<<(*it)[0]<<" "<<(*it)[1]<<endl;        
    }


    file<<endl<<"# vertex normals"<<endl;
    for(auto it = vertex_normals.begin(); it!=vertex_normals.end(); it++){
        file<<"vn"<<" "<<(*it)[0]<<" "<<(*it)[1]<<" "<<(*it)[2]<<endl;        
    }

    file<<endl<<"# faces"<<endl;
    for(auto it = faces.begin(); it != faces.end(); ++it){
        file << "f"<<" ";
        file<<it->v1+1<<"/"<<it->vt1+1<<"/"<<it->vn1+1<<" ";
        file<<it->v2+1<<"/"<<it->vt2+1<<"/"<<it->vn2+1<<" ";
        file<<it->v3+1<<"/"<<it->vt3+1<<"/"<<it->vn3+1<<endl;
    }
    
}