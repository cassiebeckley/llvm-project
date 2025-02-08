//===----- hlsl.h - HLSL definitions --------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _HLSL_H_
#define _HLSL_H_

#if defined(__clang__)
// Don't warn about any of the DXC compatibility warnings in the clang-only
// headers since these will never be used with DXC anyways.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Whlsl-dxc-compatability"
#endif

#include "hlsl/hlsl_basic_types.h"
#include "hlsl/hlsl_intrinsics.h"

// TODO: put this in a new file
// TODO: maybe check for spirv flag if exists?
namespace hlsl {
namespace vk {
// template <class T> using Foo = __hlsl_spirv_t;
// typedef Foo
template <typename T, T v> struct integral_constant {
  static constexpr T value = v;
};

template <typename T> struct Literal {};

template <uint Opcode, uint Size, uint Alignment, typename... Operands>
using SpirvType = __hlsl_spirv_type<Opcode, Size, Alignment, Operands...>;

template <uint Opcode, typename... Operands>
using SpirvOpaqueType = __hlsl_spirv_type<Opcode, 0, 0, Operands...>;
} // namespace vk
} // namespace hlsl

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif //_HLSL_H_
