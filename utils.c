/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:55:56 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/01/30 20:26:37 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	free_dbl_ptr(char **ptr, int i)
{
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_trpl_ptr(char ***ptr, int i)
{
	while (ptr[i] != NULL)
	{
		free_dbl_ptr(ptr[i], 0);
		i++;
	}
	free(ptr);
}

void	pop_back(t_list *head)
{
	while (head->next->next)
	{
		head = head->next;
	}
	free(head->next);
	head->next = NULL;
}

void	nop(void *nothing)
{
}

int	valid_quotes(char	*str)
{
	int		i;
	t_list	*head;
	char	*last;

	i = 0;
	head = ft_lstnew("0");
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			last = ft_lstlast(head)->content;
			if (str[i] != last[0])
				ft_lstadd_back(&head, ft_lstnew(str + i));
			else if (str[i] == last[0])
				pop_back(head);
		}
		i++;
	}
	if (ft_lstsize(head) == 1)
		return (ft_lstclear(&head, nop), 1);
	return (ft_lstclear(&head, nop), 0);
}
