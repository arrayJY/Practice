/* simple static reflection for struct */
/* std=c++17 */
#pragma once
#include <tuple>
#include <string_view>

template <typename... T>
inline constexpr auto StructSchema(T &&... tuples)
{
    return std::make_tuple(std::forward<T>(tuples)...);
}

template <typename Struct, typename T>
inline constexpr auto StructField(T Struct::*mem, std::string_view name)
{
    return std::make_tuple(mem, name);
}

template <typename... T, typename Fn>
void ForEachTuple(std::tuple<T...> &&s, Fn &&fn)
{
    std::apply(fn, s);
}

template <typename Struct, typename Fn, typename... S>
void ForEachStruct(Struct &&value, std::tuple<S...> &schema, Fn &&fn)
{
    ForEachTuple(std::forward<std::tuple<S...>>(schema), [&value, &fn](auto &&... x) {
        (..., fn(std::get<1>(x), value.*std::get<0>(x)));
    });
}