*This activity has been created as part of the 42 curriculum by gabusalm.*

# get_next_line

## Description
**get_next_line** is a C function that reads and returns **one line** at a time from a file descriptor.

- Prototype: `char *get_next_line(int fd);`
- The returned line **includes `\n`** if it exists in the input.
- If there is nothing left to read or an error happens, it returns **NULL**.

This project is mainly about learning **static variables**, buffering, and safe memory management.

## Files
- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

## Instructions

### Compile
You must compile with the usual flags and optionally define `BUFFER_SIZE`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

You should also be able to compile without `-D BUFFER_SIZE`
(use a default value in your header).

---

## Example (simple test)

Create a `main.c` for testing (not required to submit):

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

---

## Algorithm (Detailed Explanation + Justification)

### Why this algorithm?
The goal is to return **exactly one line per call** while reading as little as possible.
We cannot read the whole file at once, and we must keep leftover data between calls.

### Core idea
We keep a **static buffer (stash)** that stores leftover characters between calls:

1. Read from `fd` into a temporary buffer (`BUFFER_SIZE` bytes).
2. Append it to the stash.
3. Stop reading once a `\n` is found in the stash.
4. Extract the line:
   - If `\n` exists, return everything up to and including it.
   - If EOF is reached and stash still contains data, return it as the last line.
5. Update the stash to keep only the remaining characters.
6. If stash is empty and EOF is reached, return `NULL`.

### Why static stash?
Because the function is called many times, and each call must continue from where the previous call stopped.
A static variable preserves state across function calls without using global variables.

---

## Complexity
- **Time Complexity:** O(n) over the whole file.
- **Memory Usage:** Depends on the longest line stored in the stash.

---

## Rules / Notes
- Allowed functions: `read`, `malloc`, `free`
- Forbidden: `lseek`, global variables, using libft

---

## Resources
- `man 2 read`
- Static variables in C (documentation/tutorials)
- File descriptors in Unix/Linux
- 42 subject: *Get Next Line (Version 1.1)*

---

## AI Usage
AI was used for:
- Writing and formatting this README.md
- Explaining the algorithm in clear steps

No AI-generated source code was copied directly into the project files.

