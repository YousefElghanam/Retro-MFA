# ---------------------------------------------------------------------------- #
# Makefile template v 2.1										2026-01-08
# ---------------------------------------------------------------------------- #
#
#							PROJECT BUILD RULES
#
# ---------------------------------------------------------------------------- #

# Linking
$(BIN): $(OBJ)
	@mkdir -p $(@D)
	@printf "$(C_WINTER_BLUE)"
	$(CC) $(CFLAGS) $(OBJ) $(CLIBS) -o $@
	@printf "$(C_RESET)"
	@if [ "$(MODE)" = "reg" ]; then cp $(BIN) .; fi

# Compiling (plus subdir creation)
$(OBJ_DIR)%.o: $(SRC_ROOT)%.c $(HEADER)
	@mkdir -p $(@D)
	@printf "$(C_SUMI_5)"
	$(CC) $(CFLAGS) $(CINCL) -c $< -o $@
	@printf "$(C_RESET)"

# Ensure libft exists (if enabled)
$(LFT_DIR)$(LFT_NAME): libft
