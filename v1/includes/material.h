#include "config.h"

class Material {
    public:
        Material(char* filename);
        ~Material();
        void use(int unit);
    private:
        unsigned int texture;
};