// pair.h
// Copyright (c) 2020, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

namespace krt
{
	template <typename T, typename U>
	struct pair
	{
		constexpr pair() { }

		template <typename T_, typename U_>
		constexpr pair(T_&& f, U_&& s) : first(static_cast<T_&&>(f)), second(static_cast<U_&&>(s)) { }
		constexpr pair(const T& f, const U& s) : first(f), second(s) { }

		constexpr pair(pair&& p) = default;
		constexpr pair(const pair& p) = default;

		constexpr pair& operator= (pair&& other) = default;
		constexpr pair& operator= (const pair& other) = default;

		constexpr bool operator== (const pair& other) const
		{
			return this->first == other.first && this->second == other.second;
		}

		constexpr bool operator!= (const pair& other) const { return !(*this == other); }

		constexpr const T& fst() const { return this->first; }
		constexpr const U& snd() const { return this->second; }

		constexpr T& fst() { return this->first; }
		constexpr U& snd() { return this->second; }

		T first;
		U second;
	};
}
