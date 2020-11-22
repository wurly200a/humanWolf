#include <string>

class GameMaster
{
private:
    void registerMember();
public:
    GameMaster(); // counstructor
    ~GameMaster(); // decounstructor
    void PrepareGame(void);
    void StartGame(void);
    void EndGame(void);
};
