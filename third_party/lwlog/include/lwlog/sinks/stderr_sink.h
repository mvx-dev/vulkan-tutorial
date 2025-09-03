#pragma once

#include "lwlog/details/stream_writer.h"
#include "lwlog/sinks/sink.h"

namespace lwlog::sinks {
template <typename BufferLimits, typename FlushPolicy, typename ThreadingPolicy>
class stderr_sink : public sink<true, BufferLimits, ThreadingPolicy>,
                    private details::stream_writer<FlushPolicy> {
  private:
    using sink_t = sink<true, BufferLimits, ThreadingPolicy>;

  public:
    stderr_sink();
    void sink_it(const details::record<BufferLimits> &record) override;
};

template <typename BufferLimits, typename FlushPolicy, typename ThreadingPolicy>
stderr_sink<BufferLimits, FlushPolicy, ThreadingPolicy>::stderr_sink()
    : details::stream_writer<FlushPolicy>(stderr) {}

template <typename BufferLimits, typename FlushPolicy, typename ThreadingPolicy>
void stderr_sink<BufferLimits, FlushPolicy, ThreadingPolicy>::sink_it(
    const details::record<BufferLimits> &record) {
    sink_t::m_current_level = record.log_level;
    details::stream_writer<FlushPolicy>::write(
        sink_t::m_pattern.compile(record));
    sink_t::m_pattern.reset_pattern();
}
} // namespace lwlog::sinks
