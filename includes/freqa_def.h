#ifndef XOR_DEF_h
# define XOR_DEF_h

# include "libft.h"

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <sys/stat.h>

# define ONE_LINE 0
# define ZEROX 1
# define BSX 2			// backslashx //x
# define SPACE 3
# define COLUMN 4
# define SEMI_COL 5
# define COMMA 6

#define TRIGRAM 'T'
#define POS 'P'
#define MTX 'M'
#define COUNT 'C'
#define SORTED 'S'

#define DISP 1

#define CHAR_MIN_BY_THREADS 1024

typedef pthread_mutex_t t_mtx;

typedef struct s_data
{
	char		*text;
	int			max_threads;
	int			char_by_thread;
	int			nb_threads;
	pthread_t	*threads;
	t_list		**head;
	t_list		**list;
	t_uint		disp_pos;
	t_uint		n_grams;
	t_uint		nb_trigrams;	  //count for all trigram
	t_bool		config;			  // 0 if only frequency, 1 if another prog call it
	t_bool		bytes;
	t_bool		hex;
}				t_data;

typedef struct s_data_node
{
	char	*trigram;
	int		count;
	int		*pos;
	t_bool	sorted;
	t_mtx	*mtx_node;
}			t_data_node;

typedef struct s_data_head
{
	int		*nb_threads;
	t_uint	size_sample;
	int		nb_trigrams;
}			t_data_head;

typedef struct s_reader
{
	int		id;
	int		n_grams;
	int		char_by_thread;
	char	*sample;
	t_mtx	*reader_mtx;
	t_ulong	length;
	t_uint	start;
	t_list	**h_list;
}			t_reader;


#endif
