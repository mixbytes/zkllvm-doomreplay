; ModuleID = './z_main.c'
source_filename = "./z_main.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "assigner"

; Function Attrs: nounwind
define dso_local void @free(i8* noundef %0) local_unnamed_addr #0 {
  tail call void @llvm.assigner.free.p0i8(i8* %0)
  ret void
}

; Function Attrs: nounwind
declare void @llvm.assigner.free.p0i8(i8*) #1

; Function Attrs: nounwind allocsize(0)
define dso_local i8* @malloc(i64 noundef %0) local_unnamed_addr #2 {
  %2 = tail call i8* @llvm.assigner.malloc.p0i8(i64 %0)
  ret i8* %2
}

; Function Attrs: nounwind
declare i8* @llvm.assigner.malloc.p0i8(i64) #1

; Function Attrs: nounwind
define dso_local i32 @main(i32 noundef %0) local_unnamed_addr #0 {
  %2 = add nsw i32 %0, 10
  ret i32 %2
}

attributes #0 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #1 = { nounwind }
attributes #2 = { nounwind allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 16.0.0 (https://github.com/NilFoundation/zkllvm-circifier.git bf352a2e14522504a0c832f2b66f73268c95e621)"}
