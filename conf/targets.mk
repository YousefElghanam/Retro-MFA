# ---------------------------------------------------------------------------- #
# Makefile template v 2.1										2026-01-08
# ---------------------------------------------------------------------------- #
#
#							   PROJECT BUILD TARGETS
#
# ---------------------------------------------------------------------------- #

all:		MODE := reg
all:		PART := man
all:		build

bonus:		MODE := reg
bonus:		PART := bon
bonus:		build

run:		MODE := reg
run:		PART := man
run:		build
	$(EXEC)

runb:		MODE := reg
runb:		PART := bon
runb:		build
	$(EXEC)

asan:		MODE := asan
asan:		PART := man
asan:		build
	$(EXEC)

asanb:		MODE := asan
asanb:		PART := bon
asanb:		build
	$(EXEC)

val:		MODE := val
val:		PART := man
val:		build
	$(EXEC_VALG)

valb:		MODE := val
valb:		PART := bon
valb:		build
	$(EXEC_VALG)

print:
	@printf "$(C_SAKURA_BLOSSOM)"
	@printf '%s\n' '---BUILDING---'
	@printf '%s\n' "$(PROG_NAME)"
	@printf '%s\n' '---SRC ROOT---'
	@printf '%s\n' "$(SRC_ROOT)"
	@printf '%s\n' '---SRC_MAN---'
	@printf '%s\n' "$(SRC_MAN)"
	@printf '%s\n' '---SRC_BON---'
	@printf '%s\n' "$(SRC_BON)"
	@printf '%s\n' '---OBJ_DIR---'
	@printf '%s\n' "$(OBJ_DIR)"
	@printf '%s\n' '---CFLAGS---'
	@printf '%s\n' "$(CFLAGS)"
	@printf '%s\n' '---CLIBS---'
	@printf '%s\n' "$(CLIBS)"
	@printf '$(C_RESET)'
	$(LFT_PRINT)

clean:
	@rm -rf build
	@printf "$(C_BAMBOO_GREEN)$(PROG_NAME) clean complete$(C_RESET)\n"
	$(LFT_CLEAN)

fclean:		clean
	@rm -rf bin $(PROG_NAME)
	@printf "$(C_BAMBOO_GREEN)$(PROG_NAME) fclean complete$(C_RESET)\n"
	$(LFT_FCLEAN)

re:		fclean all

# the second make call assures that MODE and PART change affect SRC and OBJ
# (make expands dependencies right away and does not adapt them on later change)
build: prt $(LFT_DEP)
	@printf "$(C_BAMBOO_GREEN)"
	@$(MAKE) $(BIN) MODE=$(MODE) PART=$(PART) --no-print-directory
	@printf "$(C_RESET)"
	@printf '\n'

prt: 
	$(PRT_BUILD)

# this target ensures that change in libft is detected
ifeq ($(USE_LIBFT),1)
libft:
	@$(MAKE) -C $(LFT_ROOT) MODE=$(MODE) --no-print-directory
else
libft:
	@printf "$(C_FUJI_WHITE) There is $(C_AUTUMN_RED)$(C_BOLD)no libft "
	@printf "$(C_RESET_BOLD)$(C_FUJI_WHITE)support enabled.$(C_RESET)\n"
endif

norm:
#	$(LFT_NORM)
	@norminette -R CheckForForbiddenHeader \
	$(addprefix $(SRC_ROOT), $(SRC_MAN) $(SRC_BON)) $(HEADER)

.PHONY:	all bonus clean fclean re \
		run runb asan asanb val valb \
		print build libft norm
