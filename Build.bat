@echo off

set INCLUDES=-I "include/" -I "include/GTAIV/" -I "gtac/include"
set SHARED_SOURCES=include/common.c
set SHARED_ARGS=-out-dir="build/" -ivscr=Encrypt %SHARED_SOURCES% -emit-asm -- %INCLUDES%
set SCCL="bin/SC-CL.exe"

del build\*.sca
del build\*.sco

%SCCL% -platform=PC -target=GTAIV -name=gtac gtac/gtac/main.c gtac/util/phone.c gtac/util/network_main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TLAD -name=gtac_e1 gtac/gtac/main.c gtac/util/phone.c gtac/util/network_main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TBOGT -name=gtac_e2 gtac/gtac/main.c gtac/util/phone.c gtac/util/network_main.c %SHARED_ARGS%

%SCCL% -platform=PC -target=GTAIV -name=gtac_network_main gtac/gtac_network_main/main.c gtac/util/network_main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TLAD -name=gtac_network_main_e1 gtac/gtac_network_main/main.c gtac/util/network_main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TBOGT -name=gtac_network_main_e2 gtac/gtac_network_main/main.c gtac/util/network_main.c %SHARED_ARGS%

%SCCL% -platform=PC -target=GTAIV -name=gtac_custom_net gtac/gtac_custom_net/main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TLAD -name=gtac_custom_net_e1 gtac/gtac_custom_net/main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TBOGT -name=gtac_custom_net_e2 gtac/gtac_custom_net/main.c %SHARED_ARGS%

%SCCL% -platform=PC -target=GTAIV -name=gtac_sandbox_net gtac/gtac_sandbox_net/main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TLAD -name=gtac_sandbox_net_e1 gtac/gtac_sandbox_net/main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TBOGT -name=gtac_sandbox_net_e2 gtac/gtac_sandbox_net/main.c %SHARED_ARGS%

%SCCL% -platform=PC -target=GTAIV -name=gtac_freeroam_sp gtac/gtac_freeroam_sp/main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TLAD -name=gtac_freeroam_sp_e1 gtac/gtac_freeroam_sp/main.c %SHARED_ARGS%
%SCCL% -platform=PC -target=GTAIV_TBOGT -name=gtac_freeroam_sp_e2 gtac/gtac_freeroam_sp/main.c %SHARED_ARGS%

pause
