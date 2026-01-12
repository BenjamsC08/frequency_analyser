#include "freq_a.h"
#include "libft.h"

char *remove_whitespace(char *str)
{
	char	*output;
	char	*out;

	output = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!output)
		return (NULL);
	out = output;
	while (*str)
	{
		if (ft_iswhitespace(*str))
		{
			str++;
			continue ;
		}
		*(out++) = *(str++);
	}
	return (output);
}

char	*reset_hex(char *str)
{
	char  *iu;
	char  *out;
	
	iu = remove_whitespace(str);
	if (!iu)
		return (write(1, "alloc error\n", 12), NULL);
	if (!ft_only_charset(iu, "0123456789abcdefABCDEFxX:;,\\"))
		return (write(1, "Not a correct hex format\n", 25), free(iu), NULL);
	out = NULL;
	if (iu[0] == 'x')
		out = ft_remove_charset(iu, "x");
	if (iu[0] == 'X')
		out = ft_remove_charset(iu, "X");
	if (iu[0] == '0' && iu[1] == 'x')
		out = ft_remove_substring(iu, "0x");
	if (iu[0] == '\\' && iu[1] == 'x')
		out = ft_remove_substring(iu, "\\x");
	if (iu[0] == '0' && iu[1] == 'X')
		out = ft_remove_substring(iu, "0X");
	if (iu[2] == ':' || iu[2] == ';' || iu[2] == ',')
		out = ft_remove_charset(iu, ":;,");
	if (!out)
		return (iu);
	free(iu);
	return (out);
}

char	*ft_str_insert(char *str, char *to_insert, int step)
{
	char	*out;
	int		k;

	k = ft_strlen(str);
	out = ft_calloc(sizeof(char), sizeof(char *));
	if (!out)
		return (NULL);
	k = 0;
	while (str[k])
	{
		if (k % step == 0)
			out = ft_strfjoin(out, to_insert);
		out = ft_str_add_char(out, str[k]);
		k++;
	}
	free(str);
	return (out);
}

static char	*get_to_insert(int type)
{
	if (type == 1)
		return ("0x");
	if (type == 2)
		return ("\\x");
	if (type == 3)
		return (" ");
	if (type == 4)
		return (":");
	if (type == 5)
		return (";");
	if (type == 6)
		return (",");
	return (0);
}

char	*hex_format(char *str, int type)
{
	char	*out;
	char	*s;
	char	*to_insert;

	out = reset_hex(str);
	if (!out)
		return (NULL);
	ft_lowerise(&out);
	if (type == ONE_LINE)
		return (out);
	to_insert = get_to_insert(type);
	if (!to_insert)
		return (out);
	s = str;
	if (type >= 4 && type < 7)
	{
		s = ft_cut(END, str, 2);
		str += 2;
	}
	out = ft_str_insert(str, to_insert, 2);
	if (!out)
		return (free(s), NULL);
	if (s != str)
		return (ft_strfjoin(s, out));
	return (out);
}

char	*byte_format(char *str)
{
	char	 *out;
	char	 *tmp;

	out = ft_calloc(2, 1);
	if (!out)
		return (NULL);
	while (*str)
	{
		tmp = ft_xtoa((t_ulong)*str, MIN_HEX);
		out = ft_strfjoin(out, tmp);
		free (tmp);
		if (!out)
			return (NULL);
		str++;
	}
	return (out);
}
