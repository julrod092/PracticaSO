#include "input.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <ext/stdio_filebuf.h>
#include <yaml-cpp/yaml.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;


int main (int argc,char *argv[]){
  vector<Input> inputs = Input::getInputs(argv[1]);
  //Metodo de YAML para mapear los resultados
  YAML::Emitter out;
  out<<YAML::BeginMap<<YAML::Key<<"Results"<<YAML::BeginSeq;
  for(int i = 0 ; i < inputs.size() ; i++){
    // Se crean las tuberias para comunicar el proceso hijo con el padre
    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);
    //Llamada al sistema para crear un proceso hijo
    pid_t hijo = fork();
    if (hijo  == 0){
      //Cambio de entrada y salida estandar por las salidas y entradas de la tuberias creada
      dup2(pipe1[0], 0);
      dup2(pipe2[1], 1);
      close(pipe1[1]);
      close(pipe2[0]);
      int err=0;
      //llamada al sistema que ejecuta el sysctrl
      execlp("sysctrl", "sysctrl","-n",inputs[0].getFile().c_str(),NULL);
    }
    close(pipe1[0]);
    close(pipe2[1]);
    __gnu_cxx::stdio_filebuf<char> outfilebuf(pipe1[1], std::ios::out);
    ostream *sout = new ostream(&outfilebuf);
    for(int j = 0 ; j < inputs[i].getCadenas().size() ; j++){
      //Comando que ejecuta el analisis de cada una de las cadenas almacenadas
      string arg = "{cmd: send, msg : " + inputs[i].getCadenas()[j]+ "}";
      char *aux = new char[arg.length()+1];
      strcpy(aux,arg.c_str());
      *sout<<aux<<endl;
    }
    close(pipe1[1]);
    int status;
    string result="";
    waitpid(hijo,&status,0);
    //Si el hijo no termina normalmente saca error
    if(!WIFEXITED(status)){
      return 0;
    }
    //Se guarda elresultado arrojado por el hijo
    FILE* file = fdopen(pipe2[0],"r");
    while(true){
      char *buffer = new char[50];
      int a = fread(buffer,sizeof(char),50,file);
      buffer[a]='\0';
      result += buffer;
      if(a!=50){
	break;
      }
    }
    //Se mapea y se imprime el resultado arrojado
    YAML::Node node = YAML::Load(result);
    int check = 0;
    for(int k = 0; node[k];k++){
      if(node[k]["reject"]){
	out<<YAML::BeginMap<<YAML::Key<<"Test"<<YAML::Value<<inputs[i].getIdTest();
	out<<YAML::Key<<"Result"<<YAML::Value<<"Fail"<<YAML::EndMap;
	check = 1; 
	break;
      }
    }
    if(check == 0 && node[0]){
      out<<YAML::BeginMap<<YAML::Key<<"Test"<<YAML::Value<<inputs[i].getIdTest();
      out<<YAML::Key<<"Result"<<YAML::Value<<"Pass"<<YAML::EndMap;
    }else if(!node[0]){
      return 0;
    }
  } 
  out<<YAML::EndSeq<<YAML::EndMap;
  cout<<out.c_str()<<endl;
  return 0;
}
