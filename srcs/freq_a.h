#ifndef XOR_DECODE_H
# define XOR_DECODE_H

#include "freqa_def.h"

//	hex_parsing.c
char		*remove_whitespace(char *str);
char		*reset_hex(char *str);
char		*ft_str_insert(char *str, char *to_insert, int step);
char		*hex_format(char *str, int type);
char		*byte_format(char *str);
//	inits.c
t_list		*init_head(t_data *d);
t_list		*start_list();
t_reader	*init_data_threads(t_data *data, char *str, int i, t_mtx **mutex);
//	routines.c
void		*counting_routine(void *ptr_data);
void		*sorting_routines(void *ptr_data);
void		*destroy_routine(void *ptr_data);
//	multi-threading
int			create_threads(t_data *data);
//	data_node_utils.c
int			add_data_node(t_list *last, char *str, int pos, int size_grams);
int			update_data_node(int id, t_data_node *data, int pos);
void		*extract_data_node(void *ptr_data, char type);
void		free_data_node(void *data);
void		free_data_head(void *ptr_data);
//	list_utils.c
char		**split_for_threads(t_data *data);
void		print_list(t_list **head, t_uint p);
void		destroy_list(t_list **head);
//
int			export_list(t_list **head);
int			config_file(t_data *data);
int			read_config(FILE *f, t_data *data, t_uint v);

#endif
