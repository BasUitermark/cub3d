#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* isalpha(3)
 * Tests if character is either isupper(3) or islower(3)
 * Returns zero if the test returns false, non-zero if the test returns true
 */
int		ft_isalpha(int c);

/* isdigit(3)
 * Tests if character is a digit
 * Returns zero if the test returns false, non-zero if the test returns true
 */
int		ft_isdigit(int c);

/* isalnum(3)
 * Tests if character is isalpha(3) or isdigit(3)
 * Returns zero if the test returns false, non-zero if the test returns true
 */
int		ft_isalnum(int c);

/* isascii(3)
 * Tests if character is an ASCII character
 * Returns zero if the test returns false, non-zero if the test returns true
 */
int		ft_isascii(int c);

/* isprint(3)
 * Tests if character is printable (32 >= c <= 127)
 * Returns zero if the test returns false, non-zero if the test returns true
 */
int		ft_isprint(int c);

/* strlen(3)
 * Computes the length of the string s
 * Returns the number of characters in string s before the null terminator
 */
size_t	ft_strlen(const char *s);

/* strlcpy(3)
 * Copies dstsize - 1 characters from string src to dst
 * NUL-terminates the result if there is room
 * Returns the length of src
 */
size_t	ft_strlcpy(char *dst, const char *src, \
	size_t dstsize);

/* strlcat(3)
 * Appends dstsize - 1 characters from string src to dst
 * It will append at most dstsize - strlen(dst) - 1 characters
 * Returns the length of src + length of dst
 */
size_t	ft_strlcat(char *dst, const char *src, \
	size_t dstsize);

/* strchr(3)
 * Locates first occurance of c in string s
 * Returns pointer to character or NULL if character does not appear in s
 */
char	*ft_strchr(const char *s, int c);

/* strrchr(3)
 * Locates last occurance of c in string s
 * Returns pointer to character or NULL if character does not appear in s
 */
char	*ft_strrchr(const char *s, int c);

/* strncmp(3)
 * lexicographically compares not more than n characters 
 * of the null-terminated strings s1 and s2
 * Returns difference between s1 and s2 where the character is different
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* strnstr(3)
 * locates occurance needle in haystack where not more than len chars are
 * searched
 * Returns pointer of start of needle in haystack or NULL if not found
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/* toupper(3)
 * converts character to uppercase if possible
 * Returns uppercase char if previously lowercase, or the original char
 */
int		ft_toupper(int c);

/* tolower(3)
 * converts character to lowercase if possible
 * Returns lowercase char if previously uppercase, or the original char
 */
int		ft_tolower(int c);

/* atoi(3)
 * converts the initial portion of the string pointed to by str to int
 * Returns converted integer
 */
int		ft_atoi(const char *str);

/* memset(3)
 * writes len bytes of value c to the string b
 * Returns its first argument
 */
void	*ft_memset(void *b, int c, size_t len);

/* bzero(3)
 * writes n zeroed bytes to string s
 * Returns nothing
 */
void	ft_bzero(void *s, size_t n);

/* memcpy(3)
 * copies n bytes from memory area src to memory area dst
 * if dst and src overlap, behavior is undefined
 * Returns original value of dst
 */
void	*ft_memcpy(void *dst, const void *src, size_t n);

/* memmove(3)
 * copies len bytes from memory area src to memory area dst
 * the two strings may overlap; the copy is always done non-destructively
 * Returns original value of dst
 */
void	*ft_memmove(void *dst, const void *src, size_t len);

/* memchr(3)
 * locates the first occurrence of c (converted to an unsigned char) in string s
 * Returns a pointer to the located byte or null if the byte does not exist
 */
void	*ft_memchr(const void *s, int c, size_t n);

/* memcmp(3)
 * locates the first occurrence of c (converted to an unsigned char) in string s
 * Returns difference between the first two differing bytes
 * 0 if strings are identical
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/* The following functions are allowed to be re-coded using the malloc
 * function.
 */

/* calloc(3)
 * contiguously allocates enough space for count objects that are size bytes
 * also zeroes all allocated bytes
 * Returns pointer to allocated memory
 */
void	*ft_calloc(size_t count, size_t size);

/* strdup(3)
 * allocates sufficient memory for a copy of the string s1
 * and copies the content of s1 to the allocated memory
 * Returns pointer to allocated memory
 */
char	*ft_strdup(const char *s1);

/* substr( custom )
 * Allocates (with malloc(3)) and returns a substring
 * from the string ’s’.
 * The substring begins at index ’start’ and is of
 * maximum size ’len’.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* strjoin( custom )
 * Allocates (with malloc(3)) and returns a new
 * string, which is the result of the concatenation
 * of ’s1’ and ’s2’.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/* strtrim( custom )
 * Allocates (with malloc(3)) and returns a copy of
 * ’s1’ with the characters specified in ’set’ removed
 * from the beginning and the end of the string.
 */
char	*ft_strtrim(char const *s1, char const *set);

/* split( custom )
 * Allocates (with malloc(3)) and returns an array
 * of strings obtained by splitting ’s’ using the
 * character ’c’ as a delimiter.  The array must be
 * ended by a NULL pointer.
 */
char	**ft_split(char const *s, char c);

/* itoa( custom )
 * Allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument.
 * Negative numbers must be handled.
 */
char	*ft_itoa(int n);

/* strmapi( custom )
 * Applies the function ’f’ to each character of the
 * string ’s’ to create a new string (with malloc(3))
 * resulting from successive applications of ’f’.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* striteri( custom )
 * Applies the function f to each character of the
 * string passed as argument, and passing its index
 * as first argument.  Each character is passed by
 * address to f to be modified if necessary
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* putchar_fd( custom )
 * Outputs the character ’c’ to the given file
 * descriptor.
 */
void	ft_putchar_fd(char c, int fd);

/* putstr_fr( custom )
 * Outputs the string ’s’ to the given file
 * descriptor.
 */
void	ft_putstr_fd(char *s, int fd);

/* putendl_fd( custom )
 * Outputs the string ’s’ to the given file
 * descriptor, followed by a newline.
 */
void	ft_putendl_fd(char *s, int fd);

/* putnbr_fd( custom )
 * Outputs the integer ’n’ to the given file
 * descriptor.
 */
void	ft_putnbr_fd(int n, int fd);

/* ft_lstnew( custom )
 * Allocates (with malloc(3)) and returns a new
 * element.  The variable ’content’ is initialized
 * with the value of the parameter ’content’.  The
 * variable ’next’ is initialized to NULL.
 */
t_list	*ft_lstnew(void *content);

/* ft_lstadd_front( custom )
 * Adds the element ’new’ at the beginning of the
 * list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/* ft_lstsize( custom )
 * Counts the number of elements in a list.
 */
int		ft_lstsize(t_list *lst);

/* ft_lstlast( custom )
 * Returns the last element of the list.
 */
t_list	*ft_lstlast(t_list *lst);

/* ft_lstadd_back( custom )
 * Adds the element ’new’ at the end of the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/* ft_lstdelone( custom )
 * Takes as a parameter an element and frees the
 * memory of the element’s content using the function
 * ’del’ given as a parameter and free the element.
 * The memory of ’next’ must not be freed.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/* ft_lstclear( custom )
 * Deletes and frees the given element and every
 * successor of that element, using the function ’del’
 * and free(3).
 * Finally, the pointer to the list must be set to
 * NULL.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/* ft_lstiter( custom )
 * Iterates the list ’lst’ and applies the function
 * ’f’ to the content of each element.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/* ft_lstmap( custom )
 * Iterates the list ’lst’ and applies the function
 * ’f’ to the content of each element.  Creates a new
 * list resulting of the successive applications of
 * the function ’f’.  The ’del’ function is used to
 * delete the content of an element if needed.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif