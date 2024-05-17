// https://git.quacker.org/d/freebsd-nq/commit/9c5cbc30e7062561affda0e5413f6db27a83b27e#diff-59f10e04966536300a4a3ab9c1a13c389327d620
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>

static bool	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

static bool	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

static int	ft_digittoint(int c)
{
	return (c - '0');
}

static bool	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

static bool	ft_isspace(int c)
{
	c = (unsigned char)c;
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static const char	*skip_whitespace(const char *s)
{
	while (ft_isspace(*s))
		s++;
	return (s);
}

static int	is_negative(const char **s)
{
	if (**s == '-')
	{
		(*s)++;
		return (1);
	}
	else if (**s == '+')
	{
			(*s)++;
	}
	return (0);
}

static int	parse_base(const char **s, int base)
{
	if ((base == 0 || base == 16) && **s == '0'
		&& ((*s)[1] == 'x' || (*s)[1] == 'X'))
	{
		(*s) += 2;
		base = 16;
	}
	if (base == 0)
	{
		if (**s == '0')
			base = 8;
		else
			base = 10;
	}
	return (base);
}

intmax_t	ft_strtoimax(const char *nptr, char **endptr, int base)
{
	const char		*s;
	uintmax_t			acc;
	unsigned char	c;
	uintmax_t			cutoff;
	int						neg;
	int						any;
	int						cutlim;

	s = skip_whitespace(nptr);
	neg = is_negative(&s);
	base = parse_base(&s, base);
	acc = 0;
	any = 0;
	if (base < 2 || base > 36)
		errno = EINVAL;
	cutoff = neg ? (uintmax_t) - (INTMAX_MIN + INTMAX_MAX) + INTMAX_MAX : INTMAX_MAX;
	cutlim = cutoff % base;
	cutoff /= base;
	while (1)
	{
		c = *s;
		if (ft_isdigit(c))
			c = ft_digittoint(c);
		else if (ft_isalpha(c))
			c -= ft_isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
		{
			break;
		}
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
		{
			any = -1;
		}
		else
		{
			any = 1;
			acc *= base;
			acc += c;
		}
		s++;
	}
	if (any < 0)
	{
		acc = neg ? INTMAX_MIN : INTMAX_MAX;
		errno = ERANGE;
	}
	else if (!any)
		errno = EINVAL;
	else if (neg)
		acc = -acc;
	if (endptr != NULL)
		*endptr = (char *)(any ? s : nptr);
	return (acc);
}

#include <inttypes.h>
int main()
{
	char *s = "    321g2 ";
	char *end = "";
	printf("%jd\n", ft_strtoimax(s, &end, 4));
	printf("end: %s\n", end);
	printf("%jd\n", strtoimax(s, &end, 4));
	printf("end: %s\n", end);
	printf("\n============\n\n");
	printf("%jd\n", ft_strtoimax(s, &end, 10));
	printf("end: %s\n", end);
	printf("%jd\n", strtoimax(s, &end, 10));
	printf("end: %s\n", end);
	printf("\n============\n\n");
	s = "0x236f9   ";
	printf("%jd\n", ft_strtoimax(s, &end, 15));
	printf("end: %s\n", end);
	printf("%jd\n", strtoimax(s, &end, 15));
	printf("end: %s\n", end);
	printf("\n============\n\n");
	printf("%jd\n", ft_strtoimax(s, &end, 0));
	printf("end: %s\n", end);
	printf("%jd\n", strtoimax(s, &end, 0));
	printf("end: %s\n", end);
	printf("\n============\n\n");
	s = "   -0x2A36E9   ";
	printf("%jd\n", ft_strtoimax(s, &end, 16));
	printf("end: %s\n", end);
	printf("%jd\n", strtoimax(s, &end, 16));
	printf("end: %s\n", end);
	printf("\n============\n\n");
	s = "		04434   ";
	printf("%jd\n", ft_strtoimax(s, &end, 0));
	printf("end: %s\n", end);
	printf("%jd\n", strtoimax(s, &end, 0));
	printf("end: %s\n", end);
	printf("\n============\n\n");
	s = "		9223372036854775809   ";
	printf("%jd\n", ft_strtoimax(s, &end, 0));
	printf("end: %s\n", end);
	printf("%jd\n", strtoimax(s, &end, 0));
	printf("end: %s\n", end);
	printf("\n============\n\n");
	s = "		-9223372036854775809   ";
	printf("%jd\n", ft_strtoimax(s, &end, 15));
	printf("end: %s\n", end);
	printf("%jd\n", strtoimax(s, &end, 15));
	printf("end: %s\n", end);
}
