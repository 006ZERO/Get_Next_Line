#include "get_next_line.h"

size_t ft_strlen(const char *s) {
  size_t i;

  if (!s)
    return (0);
  i = 0;
  while (s[i])
    i++;
  return (i);
}

char *ft_strchr(const char *s, int c) {
  size_t i;

  if (!s)
    return (NULL);
  i = 0;
  while (s[i]) {
    if (s[i] == (char)c)
      return ((char *)&s[i]);
    i++;
  }
  if ((char)c == '\0')
    return ((char *)&s[i]);
  return (NULL);
}

char *ft_strjoin(char *s1, const char *s2) {
  char *joined;
  size_t len1;
  size_t len2;
  size_t i;
  size_t j;

  len1 = ft_strlen(s1);
  len2 = ft_strlen(s2);
  joined = (char *)malloc(len1 + len2 + 1);
  if (!joined)
    return (free(s1), NULL);
  i = 0;
  while (i < len1) {
    joined[i] = s1[i];
    i++;
  }
  j = 0;
  while (j < len2)
    joined[i++] = s2[j++];
  joined[i] = '\0';
  free(s1);
  return (joined);
}

char *ft_substr(const char *s, unsigned int start, size_t len) {
  char *sub;
  size_t s_len;
  size_t i;

  if (!s)
    return (NULL);
  s_len = ft_strlen(s);
  if (start >= s_len)
    return (NULL);
  if (len > s_len - start)
    len = s_len - start;
  sub = (char *)malloc(len + 1);
  if (!sub)
    return (NULL);
  i = 0;
  while (i < len && s[start + i]) {
    sub[i] = s[start + i];
    i++;
  }
  sub[i] = '\0';
  return (sub);
}
