#include "queue.h"
#include "tile_game.h"
#include "linked_list.h"
#include <stdbool.h>
#include <stdlib.h>

bool solution_reached(struct game_state state);
bool present(struct linked_list *list, size_t);
bool empty(struct linked_list *list);

void enqueue(struct queue *q, struct game_state state) 
{
    uint64_t serialized_state = serialize(state);
    insert_at_head(&(q->data), (size_t)serialized_state);
}

struct game_state dequeue(struct queue *q) 
{
    if (empty(&(q -> data)))
    {
        struct game_state empty_state = {{{0, 0, 0, 0}, 
                                          {0, 0, 0, 0}, 
                                          {0, 0, 0, 0}, 
                                          {0, 0, 0, 0}}, 0, 0, 0};
        return empty_state;
    }
    uint64_t serialized_state = remove_from_tail(&(q -> data));
    return deserialize(serialized_state);
}

int number_of_moves(struct game_state start) 
{
    struct linked_list serials = {0};
    struct queue q = {0};
    struct game_state state = start;
    if (!present(&serials, serialize(state))) 
    {
        insert_at_head(&serials, serialize(state));
        enqueue(&q, state);
    }
    
    while (q.data.head != NULL)
    {
        struct game_state current = dequeue(&q);
        if (solution_reached(current))
        {
            free_list(serials);
            free_list(q.data);
            return current.num_steps;
        }

        void (*moves[])(struct game_state *) = {move_up, move_down, move_left, move_right}; // Array of pointers
        for (int i = 0; i < 4; i++)
        {
            struct game_state next_state = current;
            moves[i](&next_state);
            if (!present(&serials, serialize(next_state))) 
            {
                insert_at_head(&serials, serialize(next_state));
                enqueue(&q, next_state);
            }
            if (solution_reached(next_state))
            {
                free_list(serials);
                free_list(q.data);
                return next_state.num_steps;
            }
        }
    }
    free_list(serials);
    free_list(q.data);
    return -1;
}

bool solution_reached(struct game_state state)
{
    int num = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((num != 16 && state.tiles[i][j] != num) || (num == 16 && state.tiles[i][j] != 0)) {return false;}
            num++;
        }
    }
    return true;
}

bool present(struct linked_list *serials, size_t val)
{
    struct list_node * ptr = serials -> head;
    while (ptr != NULL)
    {
        if ((ptr -> value == val)) return true;
        ptr = ptr -> next;
    }
    return false;
}

bool empty(struct linked_list *list) 
{
    return list -> head == NULL;
}