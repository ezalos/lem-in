/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <ythomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:40:38 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/23 19:56:13 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

t_hashtable				*hashtable_init(void)
{
	t_hashtable	*h;

	h = ft_memalloc(sizeof(t_hashtable));
	h->elements = ft_memalloc(sizeof(t_hashelement *) * HASHTABLE_DEFAULT_SIZE);
	h->elements_size = HASHTABLE_DEFAULT_SIZE;
	h->elements_count = 0;
	return (h);
}

t_hashelement			*hashelement_init_param(void *data,
		void *key, size_t key_length)
{
	t_hashelement	*element;

	element = ft_memalloc(sizeof(t_hashelement));
	element->data = data;
	element->key = key;
	element->key_length = key_length;
	element->next = NULL;
	return (element);
}

void					hashtable_append(t_hashtable *hashtable,
		void *data, void *key, size_t key_length)
{
	size_t				key_hash;
	t_hashelement		*element;

	if (++hashtable->elements_count >= hashtable->elements_size)
		hashtable_expand(hashtable);
	key_hash = hash(key, key_length) % hashtable->elements_size;
	element = *(hashtable->elements + key_hash);
	if (!element)
	{
		element = hashelement_init_param(data, key, key_length);
		*(hashtable->elements + key_hash) = element;
	}
	else
	{
		while (element && element->next)
			element = element->next;
		element->next = ft_memalloc(sizeof(t_hashelement));
		element->next->data = data;
		element->next->key = key;
		element->next->key_length = key_length;
		element->next->next = NULL;
	}
}

void					*hashtable_value(t_hashtable
		*hashtable, void *key, size_t key_length)
{
	struct s_hashelement	*element;
	size_t					key_hash;

	key_hash = hash(key, key_length) % hashtable->elements_size;
	element = *(hashtable->elements + key_hash);
	while (element)
	{
		if (element->key_length == key_length
		&& !ft_strncmp(element->key, key, key_length))
			return (element->data);
		element = element->next;
	}
	return (NULL);
}
