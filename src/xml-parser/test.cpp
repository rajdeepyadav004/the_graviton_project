#include "pugixml.hpp"
#include <iostream>
#include "a.hpp"


using namespace std;
int main(){

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("scene.xml");

    cout << "Load Result: "<< result.description()<<", mesh name: ";
    cout << doc.child("world").attribute("name").value() << endl; 
    pugi::xml_node world = doc.child("world");
    cout<<world.attribute("name").value()<<endl ;

    pugi::xml_node objects = world.child("objects");
    
    for(pugi::xml_node object = objects.child("object"); object; object = object.next_sibling()){

        cout<<object.attribute("name").value()<<endl;

    }
    

    cout<<stod("1.4 ")<<endl;

    x++;
    cout<<x;

    return 0;
}
