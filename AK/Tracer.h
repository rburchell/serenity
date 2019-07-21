#pragma once

#include <AK/Types.h>
#include <Kernel/UnixTypes.h>
#include <Kernel/Process.h>

namespace AK {

class DurationTracer {
public:
    inline DurationTracer(const char* category, const char* name, pid_t pid = current ? current->process().pid() : 0, pid_t tid = current ? current->tid() : 0)
        : m_start(now())
        , m_pid(pid)
        , m_tid(tid)
        , m_category(category)
        , m_name(name)
    {
    }

    inline ~DurationTracer()
    {
        trace(m_pid, m_tid, m_start, now() - m_start, m_category, m_name);
    }

    inline static void trace(pid_t pid, pid_t tid, u32 start, u32 dur, const char* category, const char* name)
    {
        if (dur != 0)
            dbgprintf("{\"pid\":%d,\"tid\":%d,\"ts\":%u,\"dur\":%u,\"ph\":\"X\",\"cat\":\"%s\",\"name\":\"%s\"},\n", pid, tid, start * 1000 /* HZ */, dur * 1000 /* HZ */, category, name);
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

namespace NestedTracer {
    inline void start_trace(const char* category, const char* name, u32 start, pid_t pid = current ? current->process().pid() : 0, pid_t tid = current ? current->tid() : 0)
    {
        dbgprintf("{\"pid\":%d,\"tid\":%d,\"ts\":%u,\"ph\":\"B\",\"cat\":\"%s\",\"name\":\"%s\"},\n", pid, tid, start * 1000 /* HZ */, category, name);
    }
    inline void end_trace(const char* category, const char* name, u32 start, pid_t pid = current ? current->process().pid() : 0, pid_t tid = current ? current->tid() : 0)
    {
        dbgprintf("{\"pid\":%d,\"tid\":%d,\"ts\":%u,\"ph\":\"E\",\"cat\":\"%s\",\"name\":\"%s\"},\n", pid, tid, start * 1000 /* HZ */, category, name);
    }
}

namespace CounterTracer {
    inline void trace_counter(const char* category, const char* name, u32 start, u32 value, pid_t pid = current ? current->process().pid() : 0)
    {
        dbgprintf("{\"pid\":%d,\"ts\":%u,\"ph\":\"C\",\"name\":\"%s\",\"id\":%u,\"args\":{\"%s\":%u}},\n", pid, start * 1000 /* hz */, category, 0, name, value);
    }
}

#if 0
class Tracer {
public:
    Tracer() {
        Syscall::SC_trace_begin_params param;
        param.category = "malloc";
        param.category_length = 6;
        param.name = "1";
        param.name_length = 1;
        int rc = syscall(SC_trace_begin, &param);
        ASSERT(rc == 0);
    }
    ~Tracer() {
        Syscall::SC_trace_end_params param;
        param.category = "malloc";
        param.category_length = 6;
        param.name = "1";
        param.name_length = 1;
        int rc = syscall(SC_trace_end, &param);
        ASSERT(rc == 0);
    }
};
#endif

}

using AK::DurationTracer;
