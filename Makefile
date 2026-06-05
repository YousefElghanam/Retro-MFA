# ---------------------------------------------------------------------------- #
# Makefile template v 2.1										2026-01-08
# ---------------------------------------------------------------------------- #
# Features:
# - Multiple mode support (reg, asan, val)
# - Only one mode per invocation allowed						 __(°)<
# - Separate mandatory vs bonus part builds						 \_)_)
# - Easy to use: make run/runb/asan/asanb/val/valb				~~~~~~
# - Supports nested source subdirectories
# ---------------------------------------------------------------------------- #
#
#							PROJECT DATA INPUT
#
# ---------------------------------------------------------------------------- #

# Name of the executable
PROG_NAME		?= retromfa

# Makefile configuration
MK_DIR			:= conf/

include $(MK_DIR)sources.mk

# ---------------------------------------------------------------------------- #

# Compiler
CC				?= cc
# only other special flags that are not -W..., sanitizer or valgrind!
# can stay empty
CFLAGS_OTHER	?=
# standard libraries (NOT LIBFT!) go here: -lname -lname
LIBS			?= -lmlx -lXext -lX11
#

# to use libft set to 1 otherwise to 0
USE_LIBFT		?= 0
LFT_ROOT		:= lib/libft/
# ----------------------------------------------------------------------------
# arguments for executing the program in the various modes
RUN_ARGS_reg	?= MFA/white2.mfa
RUN_ARGS_asan	?= MFA/white2.mfa
RUN_ARGS_val	?= MFA/white2.mfa
# ----------------------------------------------------------------------------
VALGRIND_FLAGS	?=	--leak-check=full \
					--show-leak-kinds=all --errors-for-leak-kinds=all\
					--show-error-list=yes\
					--track-origins=yes

#	--errors-for-leak-kinds=all		
#	--show-error-list=yes			
#	--leak-check=full				
#	--show-leak-kinds=all			catch still reachable
#	--track-fds=yes					
#	--track-origins=yes				uninitialized reads, slow
#	--trace-children=yes			
#	--trace-children-skip=""		
#	--suppressions=					
#	--num-callers=20				longer stack traces
#	--quiet
#	--log-file=valgrind.log
#	--read-var-info=yes				slow
#	--tool=helgrind					threads data race 

# ----------------------------------------------------------------------------

include $(MK_DIR)colors.mk
include $(MK_DIR)control.mk
include $(MK_DIR)selection.mk
include $(MK_DIR)libft.mk
include $(MK_DIR)compile.mk
include $(MK_DIR)targets.mk
include $(MK_DIR)rules.mk
include $(MK_DIR)printing.mk