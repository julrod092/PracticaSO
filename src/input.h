#include <string>
#include <vector>

//Se define una estructura de metodos del programa

class Input{

  public:
  Input(std::string idTest, std::string file, std::vector<std::string> cadenas);
  static std::vector<Input>& getInputs (std::string yaml);
  std::string getIdTest();
  std::string getFile();
  std::vector<std::string> getCadenas();

  private:
  std::string idTest;
  std::string file;
  std::vector<std::string> cadenas;
};
