#include "freq_a.h"


/* need to be changed lost a lot of trigrams depends on how many threads because
*
*
*
*	if thread 1 have -	123
*	if thread 2 have -	456
*	if thread 3 have -	789	  (like they did actually)
*
*	i lost trigrams : {234, 567}
*
*	each trigrams n > 0 need to have the two last char of the last thread
*
*/

char	**split_for_threads(t_data *data)
{
	int		l;
	int		n;
	char	*str;
	char	**strs;

	str = data->text;
	l = ft_strlen(str);
	if (l == 0)
		return (NULL);
	if (l < CHAR_MIN_BY_THREADS)
	{
		data->char_by_thread = l;
		data->nb_threads = 1;
	}
	else if (l / CHAR_MIN_BY_THREADS > data->max_threads)
	{
		data->char_by_thread = l / data->max_threads;
		data->nb_threads = data->max_threads;
	}
	else
	{
		data->nb_threads = (l / CHAR_MIN_BY_THREADS);
		data->char_by_thread = (l / data->nb_threads);
	}
	strs = ft_calloc(data->nb_threads, sizeof(char *));
	if (!strs)
		return (NULL);
	n = 0;
	int f = 0;


	while (n < data->nb_threads)
	{
		const char	*start_ptr = str +(data->char_by_thread * n) - f;
		int			len_to_dup;
		if (n + 1 == data->nb_threads)
			len_to_dup = ft_strlen((str + (data->char_by_thread * n))) + f;
		else
			len_to_dup = data->char_by_thread + f;
		strs[n] = ft_strndup(start_ptr, len_to_dup);
		n++;
		f = data->n_grams - 1;
	}
	return (strs);
}

void	destroy_list(t_list **head)
{
	t_list	*current;
	t_list	*next;

	if (!head || !*head)
		return ;
	current = (*head)->next;
	ft_lstdelone(*head, &free_data_head);
	next = NULL;
	while (current)
	{
		next = current->next;
		ft_lstdelone(current, &free_data_node);
		current = next;
	}
	*head = NULL;
}

#include <stdio.h>

void	print_list(t_list **head, t_uint p)
{
	t_list	*current;
	int		count;
	int		*pos;

	int max = ((t_data_head *)((*head)->content))->nb_trigrams;
	current = (*head)->next;
	while (current)
	{
		count = (*(int *)extract_data_node(current->content, COUNT));
		pos = (int *)extract_data_node(current->content, POS);
		ft_dprintf(1, "trigram :'%s%s%s', count :'%s%d%s'", 
			 GREEN, (char *)extract_data_node(current->content, TRIGRAM), RESET,
			 YELLOW, count, RESET);
		dprintf(1, " prob : %s%.2f%%%s", YELLOW, 100.0f * count / max, RESET);
		if (p)
		{
			ft_dprintf(1, ", pos:[" );
			int i = -1;
			while (++i < count)
			{
				if (i == count - 1)
					ft_dprintf(1, "%d", pos[i]);
				else
					ft_dprintf(1, "%d, ", pos[i]);
			}
			ft_dprintf(1, "]");
		}
		ft_dprintf(1, "\n");
		if (current->next)
			current = current->next;
		else 
			break;
	}
	ft_dprintf(1, "\n%slength of the sample %d\n%s", CYAN, ((t_data_head *)((*head)->content))->size_sample, RESET);
	ft_dprintf(1, "%s%d trigrams\n%s", CYAN, max, RESET);
	ft_dprintf(1, "%s%d threads%s\n", CYAN, *((t_data_head *)((*head)->content))->nb_threads, RESET);
	ft_dprintf(1, "%s%d nodes%s\n", CYAN, ft_lstsize((*head)->next), RESET);

}
