#include "observable.h"
#include "observer.h"
#include <string>

namespace stratego
{
namespace utils
{

void Observable::notify(
    const std::string & propertyName) const
{
    for (auto * observer : _observers) {
        observer->update(propertyName);
    }
}

}
}
