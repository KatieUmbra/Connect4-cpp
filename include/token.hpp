#pragma once

#include <pch.hpp>
#include <string_view>
namespace c4
{
	enum class token
	{
		X,
		O
	};

	auto translate_token(token) -> std::string_view;
}
