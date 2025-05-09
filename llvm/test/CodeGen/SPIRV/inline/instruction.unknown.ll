; RUN: llc -verify-machineinstrs -O0 -mtriple=spirv-vulkan-compute %s -o - | FileCheck %s
; RUN: %if spirv-tools %{ llc -O0 -mtriple=spirv-vulkan-compute %s -o - -filetype=obj | spirv-val %}

; CHECK: %[[#glsl_std_450:]] = OpExtInstImport "GLSL.std.450"

; CHECK: OpName %[[#a:]] "a"

; CHECK: %[[#ulong:]] = OpTypeInt 64 0
; CHECK: %[[#uint:]] = OpTypeInt 32 0

; CHECK: %[[#uint_1:]] = OpConstant %[[#uint]] 1

define void @main() #0 {
entry:
; CHECK: OpExtInst %[[#ulong]] %[[#glsl_std_450]] !123456 %[[#uint_1]]
; TODO: is arbitrary integer syntax actually needed? or can the instruction just be an integer literal?
  %a = call i64 @Something(i32 1)
  ret void
}

declare i64 @Something(i32) #1

attributes #1 = { "spv.ext_instruction"="123456,GLSL.std.450" }

; TODO: test unknown ext inst set
