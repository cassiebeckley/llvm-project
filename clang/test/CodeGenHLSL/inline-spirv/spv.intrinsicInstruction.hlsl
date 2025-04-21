// RUN: %clang_cc1 -triple spirv-pc-vulkan-compute -emit-llvm -disable-llvm-passes -o - %s | FileCheck %s --enable-var-scope

// CHECK: declare spir_func noundef i64 @_Z9ReadClockj(i32 noundef) #[[#ClockAttr:]]
[[vk::ext_instruction(/* OpReadClockKHR */ 5056)]]
long ReadClock(unsigned int scope);

// CHECK: declare spir_func noundef nofpclass(nan inf) float @_Z7spv_sinf(float noundef nofpclass(nan inf)) #[[#SinAttr:]]
[[vk::ext_instruction(/* Sin*/ 13, "GLSL.std.450")]]
float spv_sin(float v);

// CHECK: declare spir_func void @_Z7spv_nopv() #[[#NopAttr:]]
[[vk::ext_instruction(/* OpNop */ 0)]]
void spv_nop();

[numthreads(1,1,1)]
void main() {
  long clock = ReadClock(1);
  float f = spv_sin(0.0);
  spv_nop();
}

// CHECK: attributes #[[#ClockAttr]]
// CHECK-SAME: "spv.ext_instruction"="5056,"

// CHECK: attributes #[[#SinAttr]]
// CHECK-SAME: "spv.ext_instruction"="13,GLSL.std.450"

// CHECK: attributes #[[#NopAttr]]
// CHECK-SAME: "spv.ext_instruction"="0"
