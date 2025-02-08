; RUN: llc -verify-machineinstrs -O0 -mtriple=spirv-unknown-unknown %s -o - | FileCheck %s
; RUN: %if spirv-tools %{ llc -O0 -mtriple=spirv-unknown-unknown %s -o - -filetype=obj | spirv-val %}

target datalayout = "e-i64:64-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024-n8:16:32:64-G1"
target triple = "spirv-unknown-unknown"

; CHECK: [[uint_t:%[0-9]+]] = OpTypeInt 32 0
; CHECK: [[uint_ptr_t:%[0-9]+]] = OpTypePointer Function [[uint_t]]

%literal_false = type target("spirv.Literal", 0)
%literal_64 = type target("spirv.Literal", 64)

; TODO: double check if alignment can be 64 and size 32
%type1 = type target("spirv.Type", %literal_64, %literal_false, 21, 64, 64)

; CHECK: [[type1:%[0-9]+]] = !21 8 0
; CHECK: [[uint_3:%[0-9]+]] = OpConstant [[uint_t]] 3
; CHECK: [[type1_arr:%[0-9]+]] = OpTypeArray [[type1]] [[uint_3]]

; CHECK: [[globals_t:%[0-9]+]] = OpTypeStruct [[type1]] [[type1_arr]] [[type1]] [[type1_arr]] [[type1]] [[type1_arr]] [[uint_t]]
%align_t = type { <2 x i16>, <3 x i16> }

declare %align_t @getAlign()

; TODO: add checks for offset decorations

define void @main() #1 {
entry:
  ; CHECK: [[globals_ptr:%[0-9]+]] = OpVariable [[globals_ptr_t]] Function

  %ret = call %align_t @getAlign()
  ret void
}
