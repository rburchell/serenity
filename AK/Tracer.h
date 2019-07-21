#pragma once

#include <AK/Types.h>

namespace AK {

class DurationTracer {
public:
    DurationTracer(const char* category, const char* name, pid_t pid = current ? current->process().pid() : 0, pid_t tid = current ? current->tid() : 0)
        : m_start(now())
        , m_pid(pid)
        , m_tid(tid)
        , m_category(category)
        , m_name(name)
    {
    }

    ~DurationTracer()
    {
        trace(m_pid, m_tid, m_start, m_start - now(), m_category, m_name);
    }

    inline static void trace(pid_t pid, pid_t tid, u32 start, u32 dur, const char* category, const char* name)
    {
        if (dur != 0)
            dbgprintf("{\"pid\":%d,\"tid\":%d,\"ts\":%u,\"dur\":%u,\"ph\":\"X\",\"cat\":\"%s\",\"name\":\"%s\"},\n", pid, tid, start, dur * 1000 /* HZ */, category, name);
    }

private:
    inline static u32 now() 
    {
        return g_uptime;
    }

    u32 m_start = 0;
    pid_t m_pid = 0;
    pid_t m_tid = 0;
    const char* m_category { nullptr };
    const char* m_name { nullptr };
};

}

using AK::DurationTracer;
