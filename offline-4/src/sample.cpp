#include "sample.hpp"

offline4::sample::sample(const std::vector<uint64_t> &attributes, const uint64_t &classification)
{
    this->attributes = attributes;
    this->classification = classification;
}

uint64_t offline4::sample::get_attribute_value(const uint64_t &index) const
{
    return attributes[index];
}

uint64_t offline4::sample::get_attribute_count() const
{
    return attributes.size();
}

uint64_t offline4::sample::get_classification() const
{
    return classification;
}