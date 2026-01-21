#pragma once

#include <functional>
#include <vector>
#include <algorithm>
#include <memory>

template<typename... Args>
class MulticastDelegate {
public:
    using Callback = std::function<void(Args...)>;
    using Handle = size_t;

private:
    struct CallbackEntry {
        Handle Handle;
        Callback Callback;
    };

    std::vector<CallbackEntry> m_callbacks;
    Handle m_nextHandle = 0;

public:
    Handle Bind(Callback callback) {
        Handle handle = m_nextHandle++;
        m_callbacks.push_back({handle, std::move(callback)});
        return handle;
    }

    template <typename T>
    Handle Bind(T* instance, void (T::*method)(Args...)) {
        return Bind([instance, method](Args... args) {
            (instance->*method)(args...);
        });
    }

    template <typename T>
    Handle Bind(T* instance, void (T::*method)(Args...) const) {
        return Bind([instance, method](Args... args) {
            (instance->*method)(args...);
        });
    }

    template <typename T>
    Handle Bind(std::shared_ptr<T> instance, void (T::*method)(Args...)) {
        return Bind([instance, method](Args... args) {
            (instance.get()->*method)(args...);
        });
    }

    template <typename T>
    Handle Bind(std::shared_ptr<T> instance, void (T::*method)(Args...) const) {
        return Bind([instance, method](Args... args) {
            (instance.get()->*method)(args...);
        });
    }

    void Call(Args... args) {
        auto callbacksCopy = m_callbacks;
        for (auto& entry : callbacksCopy) {
            auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(),
                [&entry](const CallbackEntry& e) {
                    return e.handle == entry.handle;
                });
            
            if (it != m_callbacks.end()) {
                entry.callback(args...);
            }
        }
    }

    bool Unbind(Handle handle) {
        auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(),
            [handle](const CallbackEntry& entry) {
                return entry.handle == handle;
            });
        
        if (it != m_callbacks.end()) {
            m_callbacks.erase(it);
            return true;
        }
        return false;
    }

    void Clear() {
        m_callbacks.clear();
    }

    size_t Count() const {
        return m_callbacks.size();
    }

    bool IsEmpty() const {
        return m_callbacks.empty();
    }
};
