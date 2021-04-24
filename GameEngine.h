#include "LinkedList.h"

class GameEngine{

public:
    GameEngine();
    GameEngine(GameEngine& other);
    ~GameEngine();
private:
    LinkedList bag;
    
};
