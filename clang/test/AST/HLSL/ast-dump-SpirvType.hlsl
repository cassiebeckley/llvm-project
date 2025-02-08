// RUN: %clang_cc1 -triple spirv-unknown-vulkan-compute -x hlsl -ast-dump -o - %s

typedef vk::SpirvOpaqueType<123, RWBuffer<float>, vk::integral_constant<uint, 4>> AType;
typedef vk::SpirvType<12, 2, 4, vk::integral_constant<uint64_t, 0x123456789>, float, vk::Literal<vk::integral_constant<uint, 456>>> BType;

// TODO: better diagnostics for SpirvType size and/or alignment being types instead of Exprs?

AType AValue;
BType BValue;

// TODO: uncomment this and fix error
// vk::SpirvOpaqueType<123, vk::Literal<vk::integral_constant<uint, 0x123456789>>> CType;