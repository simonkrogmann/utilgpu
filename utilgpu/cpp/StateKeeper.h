#pragma once

#include <functional>

namespace util
{
class StateKeeper
{
public:
    StateKeeper(const std::function<void()>& restoreFunction);
    StateKeeper(const StateKeeper&) = delete;
    StateKeeper(StateKeeper&& old);
    ~StateKeeper();

private:
    std::function<void()> m_restoreFunction;
};
}  // namespace util
