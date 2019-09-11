/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:40:38 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/02 14:40:40 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

t_hashtable         *hashtable_init(void)
{
    t_hashtable *h;

    h = ft_memalloc(sizeof(t_hashtable));
    h->elements = ft_memalloc(sizeof(t_hashelement *) * HASHTABLE_DEFAULT_SIZE);
    h->elements_size = HASHTABLE_DEFAULT_SIZE;
    h->elements_count = 0;
    return (h);
}

void                hashtable_deinit(t_hashtable *hashtable)
{
    if (hashtable)
    {
        if (hashtable->elements)
            ft_memdel((void **)&hashtable->elements);
        ft_memdel((void **)&hashtable);
    }
}

static size_t       hash(char *key, size_t key_length)
{
    size_t                      hash;
    
    hash = 5381;
    while (key_length--)
        hash = ((hash << 5) + hash) + (size_t)*key++;
    return (hash);
}

void                hashtable_expand_append(t_hashtable *hashtable, t_hashelement *element)
{
    size_t          key_hash;
    t_hashelement        *current_element;

    key_hash = hash(element->key,
        element->key_length) % hashtable->elements_size;
    current_element = *(hashtable->elements + key_hash);
    if (current_element)
    {
        while (current_element != NULL && current_element->next != NULL)
        {
            current_element = current_element->next;
        }
        current_element->next = element;
    }
    else
        *(hashtable->elements + key_hash) = element;
}

static void         hashtable_expand(t_hashtable *hashtable)
{
    const size_t                elements_size = hashtable->elements_size;
    size_t                      index;
    t_hashelement        **elements;
    t_hashelement        *element;
    t_hashelement        *tmp;

    index = 0;
    elements = hashtable->elements;
    hashtable->elements_size *= 2;
    hashtable->elements = ft_memalloc(sizeof(void *) * hashtable->elements_size);
    while (index < elements_size) {
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

t_hashelement       *hashelement_init_param(void *data, void *key, size_t key_length)
{
    t_hashelement        *element;

    element = ft_memalloc(sizeof(t_hashelement));
    element->data = data;
    element->key = key;
    element->key_length = key_length;
    element->next = NULL;
    return (element);
}

void                hashtable_append(t_hashtable *hashtable, void *data, void *key, size_t key_length)
{
    size_t                      key_hash;
    t_hashelement        *element;
    
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

void                *hashtable_value(t_hashtable *hashtable, void *key, size_t key_length)
{
    struct s_hashelement    *element;
    size_t            key_hash;

    key_hash = hash(key, key_length) % hashtable->elements_size;
    element = *(hashtable->elements + key_hash);
    while (element) {
        if (element->key_length == key_length
        && !ft_strncmp(element->key, key, key_length))
            return (element->data);
        element = element->next;
    }
    return (NULL);
}
