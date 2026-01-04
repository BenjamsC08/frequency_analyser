#include "freq_a.h"

t_list *init_head(t_data *d)
{
	t_data_head *data;

	data = ft_calloc(1, sizeof(t_data_head));
	if (!data)
		return (NULL);
	data->nb_threads = &d->nb_threads;
	data->size_sample = ft_strlen(d->text);
	data->nb_trigrams = d->nb_trigrams;

	return (ft_lstnew(data));
}

t_list *start_list()
{
	t_data_node *data;

	data = ft_calloc(1, sizeof(t_data_node));
	if (!data)
		return (NULL);
	data->trigram = ft_strdup("abc");
	if (!data->trigram)
		return (free(data), NULL);
	data->count = 0;
	data->mtx_node = ft_calloc(1, sizeof(t_mtx));
	if (!data->mtx_node)
		return (free(data->trigram), free(data), NULL);
	if (pthread_mutex_init(data->mtx_node, NULL) != 0)
		return (free_data_node(data), NULL);
	data->pos = ft_calloc(1, sizeof(int));
	if (!data->pos)
		return (free_data_node(data), NULL);
	return (ft_lstnew(data));
}



t_reader *init_data_threads(t_data *data, char *str, int i, t_mtx **mutex)
{
	t_reader *thread = ft_calloc(1, sizeof(t_reader));
	static t_ulong k = INT_MAX;

	if (!thread)
		return (NULL);
	thread->sample = ft_strdup(str);
	if (!thread->sample)
		return free(thread), free(str), NULL;
	thread->length = ft_strlen(str);
	if (k > thread->length)
		k = thread->length;
	free(str);
	thread->reader_mtx = *mutex;
	thread->h_list = data->list;
	thread->id = i;
	if (thread->length > k)
		thread->start = 1 + i * k + (thread->length - k);
	else if (i == 0)
		thread->start = 1;
	else
		thread->start = 1 + i * thread->length;

	thread->char_by_thread = thread->length;
	thread->n_grams = data->n_grams;
	return (thread);
}
