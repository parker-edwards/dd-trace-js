#include "Histogram.hpp"

namespace datadog {
  Histogram::Histogram() {
    this->reset();
  }

  uint64_t Histogram::min() { return min_; }
  uint64_t Histogram::max() { return max_; }
  uint64_t Histogram::sum() { return sum_; }
  uint64_t Histogram::avg() { return count_ == 0 ? 0 : sum_ / count_; }
  uint64_t Histogram::count() { return count_; }
  uint64_t Histogram::percentile(double value) {
    return std::round(digest_->quantile(value));
  }

  void Histogram::reset() {
    min_ = 0;
    max_ = 0;
    sum_ = 0;
    count_ = 0;

    digest_ = digest_.make_shared(1000);
  }

  void Histogram::add(uint64_t value) {
    if (count_ == 0) {
      min_ = max_ = value;
    } else {
      min_ = (std::min)(min_, value);
      max_ = (std::max)(max_, value);
    }

    count_ += 1;
    sum_ += value;

    digest_->add(value);
  }
}
