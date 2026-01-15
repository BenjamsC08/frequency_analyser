#include "freq_a.h"
#include "libft.h"

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
	data->cf.flag.DISP_POSITION_GRAMS = get_bit(value, 0);
	data->cf.flag.CONFIG_FILE = get_bit(value, 1);
	data->cf.flag.MANAGE_AS_BYTES = get_bit(value, 2);
	data->cf.flag.FORCE_HEX = get_bit(value, 3);
	data->cf.flag.SIZE_NGRAM = get_bits(value, 4, 7);
	if (data->cf.flag.MANAGE_AS_BYTES)
		data->cf.flag.SIZE_NGRAM <<= 1;
	data->cf.flag.MAX_THREADS = get_bits(value, 11, 5);
	if (f)
		fclose(f);
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

	tmp = add_option("Size of ngrams (min 2, max 31):", 2, 31);
	value += tmp;
	value <<= 1;

	tmp = add_option("Force to convert each char of the entry in byte? [1/0]:\n(your sample only have hex char 0->f)", 0, 1);
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
