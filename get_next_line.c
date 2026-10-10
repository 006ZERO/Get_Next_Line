#include "get_next_line.h"

static char *read_to_stash(int fd, char *stash) {
  char *buffer;
  ssize_t bytes_read;

  buffer = (char *)malloc(BUFFER_SIZE + 1);
  if (!buffer)
    return (free(stash), NULL);
  bytes_read = 1;
  while (!ft_strchr(stash, '\n') && bytes_read > 0) {
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read == -1)
      return (free(buffer), free(stash), NULL);
    buffer[bytes_read] = '\0';
    stash = ft_strjoin(stash, buffer);
    if (!stash)
      return (free(buffer), NULL);
  }
  free(buffer);
  return (stash);
}

static char *extract_line(char *stash) {
  size_t i;

  if (!stash || !stash[0])
    return (NULL);
  i = 0;
  while (stash[i] && stash[i] != '\n')
    i++;
  if (stash[i] == '\n')
    i++;
  return (ft_substr(stash, 0, i));
}

static char *clean_stash(char *stash) {
  size_t i;
  char *remaining;

  if (!stash)
    return (NULL);
  i = 0;
  while (stash[i] && stash[i] != '\n')
    i++;
  if (!stash[i])
    return (free(stash), NULL);
  remaining = ft_substr(stash, i + 1, ft_strlen(stash) - (i + 1));
  free(stash);
  return (remaining);
}

char *get_next_line(int fd) {
  static char *stash;
  char *line;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
  stash = read_to_stash(fd, stash);
  if (!stash)
    return (NULL);
  line = extract_line(stash);
  stash = clean_stash(stash);
  return (line);
}
