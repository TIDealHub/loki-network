#ifndef LLARP_UTIL_FILE_LOGGER_HPP
#define LLARP_UTIL_FILE_LOGGER_HPP

#include <util/logging/logstream.hpp>

#include <util/thread/queue.hpp>
#include <util/time.hpp>

#include <deque>

namespace llarp
{
  /// flushable file based log stream
  struct FileLogStream : public ILogStream
  {
    using Work_t = std::function<void(void)>;

    FileLogStream(
        std::function<void(Work_t)> io, FILE* f, llarp_time_t flushInterval, bool closefile = true);

    ~FileLogStream() override;

    void
    PreLog(
        std::stringstream& out,
        LogLevel lvl,
        const char* fname,
        int lineno,
        const std::string& nodename) const override;

    void
    Print(LogLevel, const char*, const std::string& msg) override;

    void
    Tick(llarp_time_t now) override;

    void
    PostLog(std::stringstream&) const override{};

    void
    AppendLog(
        LogLevel lvl,
        const char* fname,
        int lineno,
        const std::string& nodename,
        const std::string msg) override;

    virtual void
    ImmediateFlush() override;

    using Lines_t = thread::Queue<std::string>;

   protected:
    Lines_t m_Lines;

   private:
    static void
    Flush(Lines_t* const, FILE* const);

    bool
    ShouldFlush(llarp_time_t now) const;

    void
    FlushLinesToDisk(llarp_time_t now);

    const std::function<void(Work_t)> m_Disk;
    FILE* const m_File;
    const llarp_time_t m_FlushInterval;
    llarp_time_t m_LastFlush = 0s;
    const bool m_Close;
  };
}  // namespace llarp

#endif
