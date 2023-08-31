#ifndef SAMPLE_H
#define SAMPLE_H

#include <cstdint>
#include <string>
#include <vector>

namespace offline4
{
    class sample
    {
    private:
        std::vector<uint64_t> attributes;
        uint64_t classification;

    public:
        sample(const std::vector<uint64_t> &attributes, const uint64_t &classification);

        uint64_t get_attribute_value(const uint64_t &index) const;
        uint64_t get_attribute_count() const;
        uint64_t get_classification() const;
    };
}

#endif