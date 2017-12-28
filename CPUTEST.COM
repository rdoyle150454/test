$ write sys$output "Process          PID         Elapsed time CPU Time    Image name"
$!
$! Establish our context
$!
$
$       ctx = ""
$       if f$getsyi("cluster_member")
$       then
$         node = f$getsyi("nodename")
$         temp = f$context("process", ctx, "nodename", node, "EQL")     ! this node only
$       endif
$!
$       temp = f$context("process", ctx, "prcnam", P1, "EQL")     ! process names matching this
$!
$process_loop:
$       pid = f$pid(ctx)
$       if pid .eqs. "" then goto end_process_loop
$!
$! Now get process details from GETJPI
$!
$       our_cpu_time = f$getjpi(pid,"cputim")                           ! in 10 msec units
$       login_time = f$getjpi(pid,"logintim")                           ! process login time
$       curr_time = f$time()                                            ! time now
$       elapsed_time = f$delta_time(login_time, curr_time)              ! calculate elapsed time
$       our_prcnam = f$getjpi(pid,"prcnam")
$       our_image = f$getjpi(pid,"imagname")
$!       write sys$output f$fao("!15AS !8AS !AS !8UL !AS",-
 !               our_prcnam, pid, elapsed_time, our_cpu_time, our_image)
$ write sys$output f$fao("!8UL",-
                our_cpu_time)
$       goto process_loop
$end_process_loop:
$ exit