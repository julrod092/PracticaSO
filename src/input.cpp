#include "yaml-cpp/yaml.h"
#include <string>
#include "input.h"
#include <vector>

using namespace std;
using namespace YAML;

//Clase que parsea el documento YAML

Input::Input(string idTest, string file, vector<string> cadenas){  
  this->idTest = idTest;
  this->file = file;
  this->cadenas = cadenas;
}

//Metodo que que guarda en un vector los datos que lee del documento YAML

vector<Input>& Input::getInputs(string file){
  vector<Input> *inputs = new vector<Input>();
  Node nodo = LoadFile(file);
  for(int i = 0 ; nodo[i] ; i++){
    if(nodo[i]["Test"] && nodo[i]["Input"] && nodo[i]["File"]){
      vector<string> cadenas;
      for(int j = 0 ; nodo[i]["Input"][j] ; j++){
	cadenas.push_back(nodo[i]["Input"][j].as<string>());
      }
      Input input(nodo[i]["Test"].as<string>(),nodo[i]["File"].as<string>(),cadenas);
      inputs->push_back(input);
    }
  }
  if(inputs->size()==0){
    cerr << "No se puede encontrar el file o hay un error en el formato";
  }
  return *inputs;
}

string Input::getIdTest (){
  return idTest;
}

string Input::getFile (){
  return file;
}

vector<string> Input::getCadenas(){
  return cadenas;
}
