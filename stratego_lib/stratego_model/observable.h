#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <set>
#include <string>
#include "observer.h"
#include "state.h"

namespace stratego
{
    namespace utils
    {

        class Observable
        {
            private:
                std::set<Observer *> _observers { };

            public:
                virtual ~Observable() = default;    // polymorphism

                inline void notify(const State state, Game & game) const;
                inline void notify(const std::string &property, const std::string& message, const Game & game) const;

                inline void addObserver(Observer *);
                inline void deleteObserver(Observer *);
        };

    // implements inline methods
    void Observable::addObserver(Observer * observer)
    {
        _observers.insert(observer);
    }

    void Observable::deleteObserver(Observer * observer)
    {
        _observers.erase(observer);
    }

    void Observable::notify(const State state, Game & game) const{
        for(auto observer: _observers){
            observer->update(state,game);
        }
    }

    void Observable::notify(const std::string &property, const std::string &message, const Game & game) const{
        for(auto observer: _observers){
            observer->update(property,message,game);
        }
    }


    } // end namespace utils
} // end namespace stratego

#endif // OBSERVABLE_H
