#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include "state.h"



namespace stratego
{
class Game;

namespace utils
{

//class Observable;

class Observer
{
  public:
    virtual ~Observer() = default;
    /*
     * virtual void update() = 0
     * simple update, extended class must have reference to observable
    */
    /*
     * virtual void update(const Observable & source) = 0;
     * update with Observable in parametre… not usefull because is "difficult"
     * to cast Observable to child
    */
    //virtual void update(const Observable & source) = 0;
    virtual void update(const State state, Game & game) = 0;

    virtual void update(const std::string & property, const std::string & message, const Game & game) = 0;
};

} // end namespace utils
} // end namespace stratego

#endif // OBSERVER_H
