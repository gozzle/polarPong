#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

#include "Engine.hpp"

int main (int argc, const char * argv[])
{
    
    Engine *engine = new Engine();
    
    bool success = engine->run();
    
    delete engine;

	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
