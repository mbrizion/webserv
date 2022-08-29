#include <cstddef>

char	*ft_strnstr(const char *s1, const char *s2, const size_t len) {
	if (!*s2)
		return (NULL);
	if (!len)
		return (NULL);
	size_t	i;
	size_t	j;
	i = 0;
	while (s1[i] && i < len) {
		j = 0;
		while (s1[i + j] == s2[j] && i + j++ < len) {
			if (s2[j] == '\0')
				return ((char *)(s1 + i));
		}
		i++;
	}
	return (NULL);
}
