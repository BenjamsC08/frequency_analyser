#include "freq_a.h"

int read_config(FILE *f, t_data *data, t_uint v)
{
	int value;

	if (f && fscanf(f, "%x", &value) == 1)
	{
		if (!value)
		{
			fclose(f);
			return (0);
		}
	}
	else if (v)
		value = v;
	else
		return (0);
	data->disp_pos = get_bit(value, 0); 
	data->config = get_bit(value, 1);
	data->hex = get_bit(value, 2);
	data->n_grams = get_bits(value, 3, 7);
	data->max_threads = get_bits(value, 10, 5);

	return (1);
}

int config_file(t_data *data)
{
    FILE *f = fopen("config", "r");
    int value = 0, tmp = 0;

    if (f)
	{
        if (read_config(f, data, 0))
			return (1);
        fclose(f);
    }
    ft_dprintf(1, "No valid configuration found. Entering interactive setup.\n");

    while (1)
	{
        ft_dprintf(1, "Max thread (1-31) [<= nproc]:\n");
        if (scanf("%d", &tmp) == 1 && tmp >= 1 && tmp <= 31)
            break;
        ft_dprintf(1, "Invalid thread count.\n");
        while (getchar() != '\n');
    }
	value += tmp << 6;
    while (1) {
        ft_dprintf(1, "Size of ngrams (min 2, max INT_MAX):\n");
        if (scanf("%d", &tmp) == 1 && tmp >= 2 && tmp <= 63)
            break;
        ft_dprintf(1, "Invalid size.\n");
        while (getchar() != '\n');
    }
	value += tmp;
	value <<= 1;
    while (1) {
        ft_dprintf(1, "Only hex format [1/0]:\n");
        if (scanf("%d", &tmp) == 1 && (tmp == 1 || tmp == 0))
            break;
        ft_dprintf(1, "Invalid size.\n");
        while (getchar() != '\n');
    }
	value += tmp;
	value <<= 1;
    while (1) {
        ft_dprintf(1, "output files ? [1/0]:\n");
        if (scanf("%d", &tmp) == 1 && (tmp == 1 || tmp == 0))
            break;
        ft_dprintf(1, "Invalid size.\n");
        while (getchar() != '\n');
    }
	value += tmp;
	value <<= 1;
	if (tmp == 0)
	{
		while (1) {
			ft_dprintf(1, "Disp Position of n-gram? [1/0]:\n");
			if (scanf("%d", &tmp) == 1 && (tmp == 1 || tmp == 0))
				break;
			ft_dprintf(1, "Invalid size.\n");
			while (getchar() != '\n');
		}
	}
	value += tmp;
    while (getchar() != '\n');

    f = fopen("config", "w");
    if (f)
	{
        fprintf(f, "%x", value);
        fclose(f);
    }
	if (!read_config(NULL, data, value))
		return (0);
    return (1);
}
