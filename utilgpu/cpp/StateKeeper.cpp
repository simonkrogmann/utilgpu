#include "StateKeeper.h"

#include <functional>

namespace util
{
StateKeeper::StateKeeper(const std::function<void()>& restoreFunction)
    : m_restoreFunction{restoreFunction}
{
}
StateKeeper::StateKeeper(StateKeeper&& old)
    : m_restoreFunction{old.m_restoreFunction}
{
    old.m_restoreFunction = []()
    {
    };
}
StateKeeper::~StateKeeper()
{
    m_restoreFunction();
}
}
