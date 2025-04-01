#include "queue.h"
#include "tile_game.h"

// enqueue function: Add a serialized game state to the queue
void enqueue(struct queue *q, struct game_state state) 
{
    // append serialized_state to queue.data (use linked list's insert_at_tail)

    insert_at_tail(q, state);

}


// dequeue function: Remove and return the deserialized game state at the head of the queue
struct game_state dequeue(struct queue *q) 
{
    // if queue.data is empty:
    //     return null // or an invalid game_state
    // serialized_state = remove_from_head(queue.data)
    // return deserialize(serialized_state)
    
    if (q -> data == NULL) return NULL;
    return (struct game_state){0};
}


// number_of_moves function: Perform BFS to find the shortest path to solve the Tiles game
int number_of_moves(struct game_state start) 
{
    // Create a queue and a set for visited states
    queue = initialize queue
    visited = initialize empty set

    // Add the start state to the queue and mark it as visited
    enqueue(queue, start)
    mark serialize(start) as visited

    while queue is not empty:
        current_state = dequeue(queue)

        // If the current state is the goal, return the number of steps
        if is_goal_state(current_state):
            return current_state.num_steps

        // Generate all possible next states (up, down, left, right)
        for each move in [move_up, move_down, move_left, move_right]:
            next_state = apply move to current_state
            serialized_next_state = serialize(next_state)

            // If the next state has not been visited
            if serialized_next_state is not in visited:
                mark serialized_next_state as visited
                increment next_state.num_steps by 1
                enqueue(queue, next_state)
            end if
        end for
    end while

    return -1 // Return -1 if no solution is found

    return 0;
}
