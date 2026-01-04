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
	data->bytes = get_bit(value, 2);
	data->hex = get_bit(value, 3);
	data->n_grams = get_bits(value, 3, 7);
	data->max_threads = get_bits(value, 10, 5);

	return (1);
}

int	add_option(char *str, int low_limit, int high_limit)
{
	int tmp = 0;

	while (1)
	{
        ft_dprintf(1, "%s\n", str);
        if (scanf("%d", &tmp) == 1 && tmp >= low_limit && tmp <= high_limit)
            break;
        ft_dprintf(1, "something wrong cannot be >= at %d, or <= at %d\n", high_limit, low_limit);
        while (getchar() != '\n');
    }
	return (tmp);
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

	tmp = add_option("Max thread (1-31) [<= nproc]:", 1, 31);
	value += tmp << 6;

	tmp = add_option("Size of ngrams (min 2, max INT_MAX):", 2, 63);
	value += tmp;
	value <<= 1;

	tmp = add_option("Force entry in hexadecimal ? [1/0]:", 0, 1);
	value += tmp;
	value <<= 1;

	tmp = add_option("Bytes management [1/0]:\n(will take 0x41 (or A) instead of taking 0 x 4 1)", 0, 1);
	value += tmp;
	value <<= 1;

	tmp = add_option("output files ? [1/0]:", 0, 1);
	value += tmp;
	value <<= 1;

	if (tmp == 0)
		tmp = add_option("Disp Position of n-gram? [1/0]:", 0, 1);
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
