#pragma once

#include <functional>

namespace util
{
class StateKeeper
{
public:
    StateKeeper(const std::function<void()>& restoreFunction)
        : m_restoreFunction{restoreFunction}
    {
    }
    StateKeeper(const StateKeeper&) = delete;
    StateKeeper(StateKeeper&& old) : m_restoreFunction{old.m_restoreFunction}
    {
        old.m_restoreFunction = []()
        {
        };
    }
    ~StateKeeper() { m_restoreFunction(); }
private:
    std::function<void()> m_restoreFunction;
};
}
