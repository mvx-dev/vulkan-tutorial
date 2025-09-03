#pragma once

#include "lwlog/details/pattern/pattern.h"
#include "lwlog/level.h"
#include "lwlog/policy/flush_policy.h"
#include "lwlog/policy/threading_policy.h"
#include "lwlog/sinks/sink_interface.h"

namespace lwlog::sinks {
template <bool EnableAnsiColors, typename BufferLimits,
          typename ThreadingPolicy>
class sink : public interface::sink<BufferLimits> {
  private:
    using Mutex = typename ThreadingPolicy::mutex_t;
    using Lock = typename ThreadingPolicy::lock;

  public:
    sink();

  public:
    bool should_sink(level log_level) const override;
    void set_level_filter(level level_filter) override;
    void set_pattern(std::string_view pattern) override;
    void add_attribute(std::string_view flag,
                       details::attrib_value value) override;
    void add_attribute(std::string_view flag, details::attrib_value value,
                       const details::attrib_callback_t &fn) override;

  protected:
    mutable Mutex m_mtx;
    details::pattern<BufferLimits> m_pattern;
    level m_current_level{level::all};
    level m_level_filter{level::all};
};
} // namespace lwlog::sinks

#include "sink_impl.h"
