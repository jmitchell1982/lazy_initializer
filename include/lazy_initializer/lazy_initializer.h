#pragma once

#include <optional>
#include <functional>
#include <exception>

namespace lazy_initialization
{
  class bad_attempt_to_initialize : public std::exception {
  public:
    [[nodiscard]] virtual const char* what() const noexcept override {
      return "Bad attempt to initialize";
    }
  };

  template<class T>
  class lazy_initializer
  {
  public:
    constexpr lazy_initializer() = default;
    constexpr lazy_initializer(const lazy_initializer<T>&) = default;
    constexpr lazy_initializer(lazy_initializer<T>&&) = default;
    constexpr lazy_initializer<T>& operator=(const lazy_initializer<T>&) = default;
    constexpr lazy_initializer<T>& operator=(lazy_initializer<T>&&) = default;
    ~lazy_initializer() = default;

    explicit constexpr lazy_initializer(std::function<T()> d) { initialize = d; }
    constexpr lazy_initializer(std::function<T()> d, T t) { value = t; initialize = d; }
    explicit constexpr lazy_initializer(T t) { value = t; }

    explicit operator T() const
    {
      if(!value.has_value())
      {
        if(!is_derived())
          const_cast<lazy_initializer*>(this)->derived_value = initialize();

        return derived_value.value();
      }
      return value.value();
    }

    lazy_initializer& operator=(T rhs) { value = rhs; return *this; }

    [[nodiscard]] bool has_value() const { return value.has_value(); }
    [[nodiscard]] bool is_derived() const { return derived_value.has_value(); }
    void reset() { value = std::nullopt; derived_value = std::nullopt; }

  private:
    std::optional<T> value;
    std::optional<T> derived_value;

    std::function<T()> initialize;
  };
}
