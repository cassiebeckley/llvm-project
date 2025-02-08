// RUN: %clang_cc1 -finclude-default-header -x hlsl -triple \
// RUN:   spirv-unknown-vulkan-compute %s -emit-llvm -disable-llvm-passes \
// RUN:   -o - | FileCheck %s --check-prefixes=CHECK,NO_HALF

// typedef vk::SpirvOpaqueType</* OpTypeArray */ 28, Texture2D, vk::integral_constant<uint, 4>> ArrayTex2D;
// typedef vk::SpirvOpaqueType</* OpTypeArray */ 28, RWBuffer<float>, vk::integral_constant<uint, 4>> ArrayBuffer;

// TODO: test vk::Literal

// TODO: if lowered resource type is opaque make sure that's okay.
// TODO: do we expect passing a resource type (RWBuffer or Texture2D or something) into a SpirvType to reference the struct or the handle? Struct most likely, so we'll need special handling for that in SemaTemplate (or maybe in the backend?)

// TODO: test that we get error for using SpirvOpaqueType and SpirvType with DirectX target

[numthreads(1, 1, 1)] void main()
{
    vk::SpirvOpaqueType</* OpTypeArray */ 28, RWBuffer<float>, vk::integral_constant<uint, 4>> buffers;
    RWBuffer<float> foo;
    // ArrayBuffer buffers;
    // TODO: puzzling
    // RWBuffer<float> b;

    // hlsl::vk::Foo<int> t;
    // __hlsl_spirv_t __attribute__((is_rov(21, 0, 0))) foo;
}
