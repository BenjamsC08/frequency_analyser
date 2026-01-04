#include "freq_a.h"
#include "freqa_def.h"
#include "libft.h"

char *get_big_string(void) {
    t_uint cap = 256, used = 0;
    char *s = malloc(cap);
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        if (used + 1 >= cap) {
            cap *= 2;
            s = realloc(s, cap);
        }
        s[used++] = c;
    }
    s[used] = '\0';
    return s;
}

t_data	*init_data(t_data *data, char *s)
{
	char *str;

	data->text = NULL;
	if (!s)
	{
		ft_dprintf(1, "Put your string\n");
		str = get_big_string();
	}
	else
		str = s;
	if (data->bytes)
	{
		if (!data->hex)
			data->text = hex_format(str, ONE_LINE);
		if (!data->text)
			data->text = byte_format(str);
		free(str);
		data->nb_trigrams = (ft_strlen(data->text) >> 1) - 2;
		return (NULL);									//Breakpoint
	}
	else
	{
		data->text = str;
		data->nb_trigrams = ft_strlen(data->text) - 2;
	}
	if (!data->text)
		return (NULL);
	data->char_by_thread = CHAR_MIN_BY_THREADS;
	data->nb_threads = 1;
	return (data);
}

int	compare_node_crescent(void *left, void *right)
{
	t_data_node *l_node = (t_data_node *)left;
	t_data_node *r_node = (t_data_node *)right;

	if (l_node->count != r_node->count)
		return (l_node->count - r_node->count);
	return (ft_strcmp(r_node->trigram, l_node->trigram));
}

int	compare_node_decrescent(void *left, void *right)
{
	t_data_node *l_node = (t_data_node *)left;
	t_data_node *r_node = (t_data_node *)right;

	if (l_node->count != r_node->count)
		return (r_node->count - l_node->count);
	return (ft_strcmp(r_node->trigram, l_node->trigram));
}


int rmv_empty_node(void *content, void *ref, size_t size)
{
	(void)ref;
	(void)size;
	t_data_node *node = (t_data_node *)content;

	if (node->count == 0)
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	t_data data;
	t_list *head = NULL;
	char *str = NULL;

	if (argc == 2)
	{
		if (!ft_strncmp("-r", argv[1], 2))
			remove("config");
		else 
		{
			int fd = open(argv[1], O_RDONLY);
			if (fd != -1)
			{
				char *get;
				get = get_next_line(fd);
				str = ft_strdup(get);
				while (get)
				{
					free(get);
					get = get_next_line(fd);
					if (get)
						str = ft_strfjoin(str, get);
				}
			}
		}
	}
	if (!config_file(&data))
		return (1);
	if (!init_data(&data, str))
		return (1);
	head = init_head(&data);
	if (!head)
		return (free(data.text), 1);
	data.head = &head;
	(*(data.head))->next = start_list(&data);
	data.list = &((*(data.head))->next);
	if (!data.list)
		return free(data.text), destroy_list(&head), 1;
	if (!create_threads(&data))
		return free(data.text), destroy_list(&head), 1;
	ft_lstremove_if(data.list, 0, &rmv_empty_node, &free_data_node);
	if (!data.config)
		*data.list = lst_merge_sort(*data.list, &compare_node_crescent);
	else
		*data.list = lst_merge_sort(*data.list, &compare_node_decrescent);

	if (!data.config)
		print_list(data.head, data.disp_pos);
	else
		export_list(data.head);
	destroy_list(data.head);
	free(data.text);
	return (0);
}
