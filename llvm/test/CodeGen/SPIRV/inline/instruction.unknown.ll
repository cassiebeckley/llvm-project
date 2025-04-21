; RUN: llc -verify-machineinstrs -O0 -mtriple=spirv-unknown-unknown %s -o - | FileCheck %s

; CHECK: %[[#glsl_std_450:]] = OpExtInstImport "GLSL.std.450"

; CHECK: OpName %[[#clock:]] "clock"

; CHECK: %[[#ulong:]] = OpTypeInt 64 0
; CHECK: %[[#uint:]] = OpTypeInt 32 0

; CHECK: %[[#uint_1:]] = OpConstant %[[#uint]] 1

; TODO: replace this with some contrived tests

define void @main() #0 {
entry:
; CHECK: OpExtInst %[[#ulong]] %[[#glsl_std_450]] !123456 %[[#uint_1]]
  %clock = call i64 @Something(i32 1)
  ret void
}

declare i64 @Something(i32) #1

attributes #1 = { "spv.ext_instruction"="123456,GLSL.std.450" }

; TODO: test unknown ext inst set
