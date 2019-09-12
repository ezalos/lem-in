/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:01:28 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/12 14:18:21 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

size_t					hash(char *key, size_t key_length)
{
	size_t		hash;

	hash = 5381;
	while (key_length--)
		hash = ((hash << 5) + hash) + (size_t)*key++;
	return (hash);
}

void					hashtable_deinit(t_hashtable *hashtable)
{
	if (hashtable)
	{
		if (hashtable->elements)
			ft_memdel((void **)&hashtable->elements);
		ft_memdel((void **)&hashtable);
	}
}

void					hashtable_expand_append(t_hashtable *hashtable,
		t_hashelement *element)
{
	size_t				key_hash;
	t_hashelement		*current_element;

	key_hash = hash(element->key,
		element->key_length) % hashtable->elements_size;
	current_element = *(hashtable->elements + key_hash);
	if (current_element)
	{
		while (current_element != NULL && current_element->next != NULL)
			current_element = current_element->next;
		current_element->next = element;
	}
	else
		*(hashtable->elements + key_hash) = element;
}

void					hashtable_expand(t_hashtable *hashtable)
{
	const size_t	elements_size = hashtable->elements_size;
	size_t			index;
	t_hashelement	**elements;
	t_hashelement	*element;
	t_hashelement	*tmp;

	index = 0;
	elements = hashtable->elements;
	hashtable->elements_size *= 2;
	hashtable->elements = ft_memalloc(sizeof(void *)
		* hashtable->elements_size);
	while (index < elements_size)
	{
		element = *(elements + index++);
		while (element)
		{
			tmp = element->next;
			element->next = NULL;
			hashtable_expand_append(hashtable, element);
			element = tmp;
		}
	}
	ft_memdel((void**)&elements);
}
