#include "../../includes/ft_printf.h"


static int	pf_putx_precision(t_convert *p)
{
	int i;
	int len;

	len = ft_strlen(p->s);
	i = 0;
	if (p->precision)
	{
		if (p->precision > len)
		{
			while (p->precision > len)
			{
				ft_putchar_fd('0', 1);
				len++;
				i++;
			}
		}
		ft_putstr_fd(p->s, 1);
		i += (int)ft_strlen(p->s);
		p->count += i;
	}
	return (i);
}

static void	pf_putx_checkprecision(t_convert *p)
{
	if (p->precision > -1)
	{
		if (p->precision == 0)
			return ;
		if (p->precision < (int)ft_strlen(p->s))
		{
			write(1, p->s, (int)ft_strlen(p->s));
			p->count += (int)ft_strlen(p->s);
		}
		else
		{
			pf_putx_precision(p);
		}
	}
	else
	{
		write(1, p->s, ft_strlen(p->s));
		p->count += (int)ft_strlen(p->s);
	}
}

static void	pf_putx_width_zero(t_convert *p)
{
	if (p->precision > -1 && p->precision > (int)ft_strlen(p->s))
	{
		pf_putspaces(p->width - p->precision);
		pf_putzero(p->precision - ft_strlen(p->s));
		write(1, p->s, ft_strlen(p->s));
	}
	else if (p->precision > -1)
	{
		pf_putspaces(p->width - ft_strlen(p->s));
		write(1, p->s, ft_strlen(p->s));
	}
	else
	{
		pf_putzero(p->width - ft_strlen(p->s));
		write(1, p->s, ft_strlen(p->s));
	}
	if (p->width > (int)ft_strlen(p->s))
		p->count += p->width;
	else
		p->count += (int)ft_strlen(p->s);
}

static void	pf_putx_width(t_convert *p)
{
	if (p->zero)
		pf_putx_width_zero(p);
	else
	{
		 if (p->precision > -1 && p->precision > (int)ft_strlen(p->s))
		{
			if (p->width > p->precision)
			{
				pf_putspaces(p->width - p->precision);
				p->count += p->width - p->precision;
			}
			pf_putx_precision(p);
		}
		else
		{
			if (p->width > (int)ft_strlen(p->s))
			{
				pf_putspaces(p->width - ft_strlen(p->s));
				p->count += p->width - ft_strlen(p->s);
			}
			write(1, p->s, ft_strlen(p->s));
			p->count += ft_strlen(p->s);
		}
	}
}

static void	pf_putx_minus(t_convert *p)
{
	if (p->width)
	{
		if (p->precision > -1 && p->precision < (int)ft_strlen(p->s))
		{
			write(1, p->s, ft_strlen(p->s));
			p->count += ft_strlen(p->s);
			if (p->width > p->precision)
			{	
				pf_putspaces(p->width - ft_strlen(p->s));
				p->count += p->width - ft_strlen(p->s);
			}
		}
		else if (p->precision > (int)ft_strlen(p->s))
		{
			pf_putx_precision(p);
			if (p->width > p->precision)
			{
				pf_putspaces(p->width - p->precision);
				p->count += p->width - p->precision;
			}
		}
		else
		{
			write(1, p->s, ft_strlen(p->s));
			pf_putspaces(p->width - (int)ft_strlen(p->s));
			if (p->width < (int)ft_strlen(p->s))
				p->count += ft_strlen(p->s);
			else
				p->count += p->width;
		}
	}
	else if (p->precision > -1 && p->precision < (int)ft_strlen(p->s))
	{
		p->count += write(1, p->s, p->precision);
	}
	else
	{
 		p->count += write(1, p->s, ft_strlen(p->s));
	}
}

void		pf_putx(t_convert *p, int isupper)
{
	int i;
	int len;

	if (isupper)
		p->s = pf_ultohex(p->X, isupper);
	else
		p->s = pf_ultohex(p->x, isupper);
	len = ft_strlen(p->s);
	i = 0;
	if (p->s)
	{
		if (p->minus)
		{
			pf_putx_minus(p);
		}
		else if (p->width)
		{
			pf_putx_width(p);
		}
		else
		{
			pf_putx_checkprecision(p);
		}
	}

	free(p->s);
}