#include <string>
#include <vector>


void it() {

    std::vector<std::string> strings{"one", "two", "three"};


    std::vector<std::string>::const_iterator it = strings.begin();



















    std::vector<std::string>::const_iterator it2 = strings.cbegin();













    std::vector<std::string>::iterator it3 = strings.begin();

}