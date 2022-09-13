#include "minirt.h"

t_figure	*ft_last_figure(t_figure *fig)
{
	while (fig->next)
		fig = fig->next;
	return (fig);
}