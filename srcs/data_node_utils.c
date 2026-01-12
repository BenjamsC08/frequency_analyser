#include "libft.h"
#include "freq_a.h"

int	add_data_node(t_list *last, char *str, int pos, int size_grams)
{
	t_data_node	*data;
	t_list		*new;

	data = ft_calloc(1, sizeof(t_data_node));
	if (!data)
		return (0);
	data->trigram = ft_strndup(str, size_grams);
	if (!data->trigram)
		return (free_data_node(data), 0);
	data->count = 1;
	data->pos = ft_calloc(1, sizeof(int));
	if (!data->pos)
		return (free_data_node(data), 0);
	data->pos[0] = pos;
	data->sorted = FALSE;
	data->mtx_node = ft_calloc(1, sizeof(t_mtx));
	if (!data->mtx_node)
		return (free_data_node(data), 0);
	if (pthread_mutex_init(data->mtx_node, NULL) != 0)
		return (free(data->mtx_node), free_data_node(data), 0);
	new = ft_lstnew(data);
	if (!new)
		free_data_node(data);
	ft_lstadd_back(&last, new);
	return (1);
}

int	update_data_node(int id, t_data_node *data, int pos)
{
	int	*new_pos;
	int	i;

	data->count++;
	new_pos = ft_calloc((data->count + 1), sizeof(int));
	if (!new_pos)
		return (0);
	i = -1;
	while (++i < (data->count - 1))
		new_pos[i] = data->pos[i];
	if (id == 0)
		new_pos[i] = pos;
	else
		new_pos[i] = pos;
	free(data->pos);
	data->pos = new_pos;
	return (1);
}

void	*extract_data_node(void *ptr_data, char type)
{
	t_data_node	*data;

	data = (t_data_node *)ptr_data;
	if (type == TRIGRAM)
		return (data->trigram);
	if (type == POS)
		return (data->pos);
	if (type == MTX)
		return (data->mtx_node);
	if (type == COUNT)
		return (&data->count);
	if (type == SORTED)
		return (&data->sorted);
	return (NULL);
}

void	free_data_node(void *ptr_data)
{
	t_data_node	*data;

	data = (t_data_node *)ptr_data;
	if (!data)
		return ;
	if (data->trigram)
		free(data->trigram);
	if (data->pos)
		free(data->pos);
	if (data->mtx_node)
	{
		pthread_mutex_destroy(data->mtx_node);
		free(data->mtx_node);
		data->mtx_node = NULL;
	}
	free(data);
}

void	free_data_head(void *ptr_data)
{
	t_data_head	*data;

	data = (t_data_head *)ptr_data;
	if (!data)
		return ;
	free(data);
}

