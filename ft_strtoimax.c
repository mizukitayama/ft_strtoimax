#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>

static bool	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

static bool ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

static int  ft_digittoint(int c)
{
  return (c - '0');
}

static bool		ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

static bool  ft_isspace(int c)
{
  c = (unsigned char)c;
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

intmax_t  ft_strtoimax(const char *nptr, char **endptr, int base)
{
  const char *s;
	uintmax_t acc;
	unsigned char c;
	uintmax_t cutoff;
	int neg, any, cutlim;

  s = nptr;
  while(ft_isspace(*s))
    s++;
  if (*s == '-')
  {
    neg = 1;
    s++;
  }
  else
  {
    neg = 0;
    if (*s == '+')
      s++;
  }
  if ((base == 0 || base == 16) &&
    *s == '0' && *(s + 1) == 'x' || *(s + 1) == 'X')
  {
    s += 2;
    base = 16;
  }
  if (base == 0)
    base = *s == '0' ? 8 : 10;
  acc = 0;
  any = 0;
  if (base < 2 || base > 36) // error
    return (0);
  cutoff = neg ? (uintmax_t)-(INTMAX_MIN + INTMAX_MAX) + INTMAX_MAX : INTMAX_MAX;
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
      printf("82: %d\n", c);
      break;
    }
    if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
    {
      printf("82!!!!");
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
    acc = neg ? INTMAX_MIN : INTMAX_MAX;
  else if (neg)
    acc = -acc;
  if (endptr != NULL)
    *endptr = (char *)(any ? s - 1 : nptr);
  return(acc);
}

// #include <inttypes.h>

// int main()
// {
//   char *s = "    3212 ";
//   char *end = "";
//   printf("%jd\n", ft_strtoimax(s, &end, 4));
//   printf("end: %s\n", end);
//   printf("%jd\n", strtoimax(s, &end, 4));
//   printf("end: %s\n", end);

//   printf("\n============\n\n");

//   printf("%jd\n", ft_strtoimax(s, &end, 10));
//   printf("end: %s\n", end);
//   printf("%jd\n", strtoimax(s, &end, 10));
//   printf("end: %s\n", end);

//   printf("\n============\n\n");

//   s = "0x236f9   ";
//   printf("%jd\n", ft_strtoimax(s, &end, 16));
//   printf("end: %s\n", end);
//   printf("%jd\n", strtoimax(s, &end, 16));
//   printf("end: %s\n", end);

//   printf("\n============\n\n");

//   printf("%jd\n", ft_strtoimax(s, &end, 0));
//   printf("end: %s\n", end);
//   printf("%jd\n", strtoimax(s, &end, 0));
//   printf("end: %s\n", end);

//   printf("\n============\n\n");

//   s = "   -0x2A36E9   ";
//   printf("%jd\n", ft_strtoimax(s, &end, 16));
//   printf("end: %s\n", end);
//   printf("%jd\n", strtoimax(s, &end, 16));
//   printf("end: %s\n", end);
// }
