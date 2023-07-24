#pragma once

#include <pch.hpp>
namespace c4
{
	enum class token
	{
		X,
		O
	};

	auto translate_token(token) -> std::string;
}
