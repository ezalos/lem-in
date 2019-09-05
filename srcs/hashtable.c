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

struct s_hashtable      *hashtable_init(void)
{
    struct s_hashtable *const   h = ft_memalloc(sizeof(struct s_hashtable));
    
    
    h->elements = ft_memalloc(sizeof(struct s_hashelement *)
        * HASHTABLE_DEFAULT_SIZE);
    h->elements_size = HASHTABLE_DEFAULT_SIZE;
    h->elements_count = 0;
    return (h);
}

void                    hashtable_deinit(struct s_hashtable *const hashtable)
{
    if (hashtable)
    {
        if (hashtable->elements)
            free(hashtable->elements);
        free(hashtable);
    }
}

static size_t           hash(const char *key, size_t key_length)
{
    size_t                      hash;
    
    hash = 5381;
    while (key_length--)
        hash = ((hash << 5) + hash) + (size_t)*key++;
    return (hash);
}

void                    hashtable_expand_append(struct s_hashtable *const hashtable,
    struct s_hashelement *const element)
{
    const size_t                key_hash = hash(element->key,
        element->key_length) % hashtable->elements_size;
    struct s_hashelement        *current_element;

    //element->next = NULL;
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

static void                     hashtable_expand(struct s_hashtable *const hashtable)
{
    const size_t                elements_size = hashtable->elements_size;
    size_t                      index;
    struct s_hashelement        **elements;
    struct s_hashelement        *element;
    struct s_hashelement        *tmp;

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

struct s_hashelement            *hashelement_init_param(void *const data,
    const void *const key, const size_t key_length)
{
    struct s_hashelement        *element;

    element = ft_memalloc(sizeof(struct s_hashelement));
    element->data = data;
    element->key = key;
    element->key_length = key_length;
    element->next = NULL;
    return (element);
}

void                            hashtable_append(struct s_hashtable *const hashtable,
    void *const data, const void *const key, const size_t key_length)
{
    size_t                      key_hash;
    struct s_hashelement        *element;
    
    time_exe(__func__);
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
        element->next = ft_memalloc(sizeof(struct s_hashelement));
        element->next->data = data;
        element->next->key = key;
        element->next->key_length = key_length;
        element->next->next = NULL;
    }
}

void                            *hashtable_value(struct s_hashtable *const hashtable,
    const void *const key, const size_t key_length)
{
    struct s_hashelement    *element;
    const size_t            key_hash = hash(key, key_length) % hashtable->elements_size;
    
    time_exe(__func__);
    element = *(hashtable->elements + key_hash);
    while (element) {
        if (element->key_length == key_length
        && !ft_strncmp(element->key, key, key_length))
            return (element->data);
        element = element->next;
    }
    return (NULL);
}
