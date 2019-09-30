# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 15:04:16 by ldevelle          #+#    #+#              #
#    Updated: 2019/09/30 14:10:01 by ldevelle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= lem-in

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined  -g3

DFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined -g3 -pedantic\
-O2 -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int\
-Werror-implicit-function-declaration -Wmain -Wparentheses -Wsequence-point\
-Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas\
-Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast\
-Wwrite-strings -Wconversion -Wsign-compare -Waggregate-return\
-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations\
-Wmissing-noreturn -Wformat -Wmissing-format-attribute\
-Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs\
-Winline -Wlong-long -Wunreachable-code


# CFLAGS = $(DFLAGS)
# CFLAGS =

##############################################################################
##############################################################################
##																			##
##									----									##
##									IFEQ									##
##									----									##
##																			##
##############################################################################
##############################################################################

SRCS_LI		=			main\
						init\
						init_links\
						init_rooms\
						init_data\
						data\
						ants\
						graph_simplifier\
						print\
						solve\
						path_quantity_estimate\
						new_algo\
						display_result\
						tools\
						link_data\
						get_param\
						hashtable\
						init_checking\
						init_parsing\
						buffer_function\
						algo_tools\
						algo_tools_2\
						algo_paths_tools\
						new_algo_function_content\
						hash_tools\
						display_spe_cases\
						louis_alg\
						louis_search\
						louis_room_check\
						louis_room_sort\
						louis_tools\
						louis_save_path\
						louis_data\
						visual_setup\
						creat_position

# SRCS_VS		=	visu-hex

SRC_PATH	= ./srcs

DIR_OBJ 	= ./objs/

##########################
##						##
##	   ARCHITECTURE		##
##						##
##########################

A_SRC 		= $(patsubst %,$(SRC_PATH)/%.c,$(SRCS_LI))
A_OBJ		= $(patsubst %,$(DIR_OBJ)%.o,$(SRCS_LI))

# B_OBJ		= $(patsubst %,$(DIR_OBJ)%.o,$(SRCS_VS))


OBJ 		= $(patsubst %,%.o,$(SRCS_LI))

LIB_DIR		= ./libft
HEAD		= head.h
HEAD_DIR	= ./includes
HEAD_PATH	= $(HEAD_DIR)/$(HEAD)

LIB			= $(LIB_DIR)/libft.a

##########################
##						##
##		  DEBUG			##
##						##
##########################

VALGRIND = valgrind --track-origins=yes --leak-check=full --show-leak-kinds=definite

##########################
##						##
##		 COLORS			##
##						##
##########################

UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
RED     = \e[31m
GREEN   = \e[32m
YELLOW  = \e[33m
BLUE	= \e[34m
MAGENTA	= \e[35m
CYAN	= \e[36m
END     = \e[0m
else
RED     = \x1b[31m
GREEN   = \x1b[32m
YELLOW  = \x1b[33m
BLUE	= \x1b[34m
MAGENTA	= \x1b[35m
CYAN	= \x1b[36m
END     = \x1b[0m
endif

COM_COLOR   = $(BLUE)
OBJ_COLOR   = $(CYAN)
OK_COLOR    = $(GREEN)
ERROR_COLOR = $(RED)
WARN_COLOR  = $(YELLOW)
NO_COLOR    = $(END)

OK_STRING    = [OK]
ERROR_STRING = [ERROR]
WARN_STRING  = [WARNING]
COM_STRING   = Compiling

MSG ?= Makefile automated push
nb ?= 10

ARG="$(MSG)"
MYST=$(shell ruby -e "puts (0..$(nb) - 1).to_a.shuffle.join(' ')")

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
	$(1) 2> $@.log; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
	elif [ -s $@.log ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
	else  \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

##############################################################################
##############################################################################
##																			##
##									-----									##
##									RULES									##
##									-----									##
##																			##
##############################################################################
##############################################################################

VISU = ./visu/visu.o
VISU_SOURCE = ./visu/visu.mm
VISU_HEADER = ./visu/visu.h
VISU_FRAMEWORK = -framework Foundation -framework AppKit -framework SceneKit

##########################
##						##
##		  BASIC			##
##						##
##########################

all :	$(NAME) auteur

$(NAME): $(VISU) $(LIB) Makefile $(A_OBJ) $(HEAD_PATH) $(VISU_HEADER)
		@$(call run_and_test, $(CC) $(CFLAGS) $(A_OBJ) $(LIB) -I./$(HEAD_DIR) -o $(NAME) -I$(VISU_HEADER) $(VISU_FRAMEWORK) $(VISU))

$(VISU): $(VISU_SOURCE) $(VISU_HEADER) Makefile
		clang -O0 -g -x objective-c $(VISU_SOURCE) -c -o $(VISU)

$(DIR_OBJ)%.o:$(SRC_PATH)/%.c $(HEAD_PATH) Makefile
		@$(call run_and_test, $(CC) $(CFLAGS) -o $@ -c $<)

$(LIB): FORCE
		@$(MAKE) -C $(LIB_DIR)

$(HEAD_PATH):
	@$(MAKE) -C $(LIB_DIR)

clean : libclean auteur
		@echo "\$(YELLOW)$(NAME) objs \$(END)\\thas been \$(GREEN)\\t\\t\\t  $@\$(END)"
		@echo "\$(YELLOW)$(VISU) objs \$(END)\\thas been \$(GREEN)\\t\\t  $@\$(END)"
		@rm -f $(A_OBJ) $(VISU)

fclean : libfclean clean auteur
		@echo "\$(YELLOW)$(NAME) \$(END)\\t\\thas been \$(GREEN)\\t\\t\\t  $@\$(END)"
		@echo "\$(YELLOW)$(VISU) \$(END)\\thas been \$(GREEN)\\t\\t\\t  $@\$(END)"
		@rm -rf $(NAME)
		@rm -rf stats

libclean :
			@$(MAKE) clean -C $(LIB_DIR)

libfclean : libclean
			@$(MAKE) fclean -C $(LIB_DIR)

auteur:
	@echo ldevelle > auteur
	@echo ythomas >> auteur

stat :	$(LIB)
		@$(CC) $(CFLAGS) ./srcs/show_stats.c $(LIB) -o stats
		@./stats $(nb)

re :	fclean all

git :
		@git add -A
		@git status
		git commit -am "$(MSG)"
		@git push

t	:	all
		./$(NAME) $(ARG)

last :	all
		@./$(NAME) $(shell cat tests/last)

unit_test :
			$(shell ./42_lem-in_tools/generator --big-superposition > ./maps/unit_test)
			$(shell cd 42_lem-in_tools ; bash ./checker.sh ../$(NAME) ../maps/unit_test | grep -e "maps" -e \\\[33m ; cd ..)
			$(shell ./$(NAME) ./maps/unit_test | grep "LOULOU ET YOYO POUR LA LIFE")

ten :
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test

hund :	all
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
tho :
		@echo "0%"
		@$(MAKE) hund
		@echo "10%"
		@$(MAKE) hund
		@echo "20%"
		@$(MAKE) hund
		@echo "30%"
		@$(MAKE) hund
		@echo "40%"
		@$(MAKE) hund
		@echo "50%"
		@$(MAKE) hund
		@echo "60%"
		@$(MAKE) hund
		@echo "70%"
		@$(MAKE) hund
		@echo "80%"
		@$(MAKE) hund
		@echo "90%"
		@$(MAKE) hund
		@echo "100%"
big :
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho


vt	:	all
		@ $(VALGRIND) ./$(NAME) $(ARG)

FORCE:

##########################
##						##
##		 .PHONY			##
##						##
##########################

.PHONY : clean fclean re all git libclean libfclean t vt c vc GENERATE ten hund\
tho stat cast last FORCE
