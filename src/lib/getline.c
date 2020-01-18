#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
size_t                  /* O - Length of string */
strlcat(char       *dst,        /* O - Destination string */
              const char *src,      /* I - Source string */
          size_t     size)      /* I - Size of destination string buffer */
{
  size_t    srclen;         /* Length of source string */
  size_t    dstlen;         /* Length of destination string */


 /*
  * Figure out how much room is left...
  */

  dstlen = strlen(dst);
  size   -= dstlen + 1;

  if (!size)
    return (dstlen);        /* No room, return immediately... */

 /*
  * Figure out how much room is needed...
  */

  srclen = strlen(src);

 /*
  * Copy the appropriate amount...
  */

  if (srclen > size)
    srclen = size;

  memcpy(dst + dstlen, src, srclen);
  dst[dstlen + srclen] = '\0';

  return (dstlen + srclen);
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
        char *dest = *lineptr, *ret, *newline;
        size_t len = *n;

        if (dest == NULL || len < 1) {
                len = 256;
                if ((dest = malloc(len)) == NULL) {
                        goto error;
                }
        }

        /* Fetch up to line_length bytes from the file, or up to a newline */
        ret = fgets(dest, (int) (len-1), stream);
        if (ret == NULL) {
                if (feof(stream) != 0) {
                        dest[0] = '\0';
                        len = 0;
                        return 0;
                } else {
                        goto error;
                }
        }

        /* If the line was too long, and so doesn't contain a newline, carry on
         * fetching until it does, or we hit the end of the file. */
        while ((newline = strchr(dest, '\n')) == NULL) {
                char *new_dest, *tmp;

                /* Create a new storage space the same size as the last one, and carry
                 * on reading. We'll need to append this to the previous string - fgets
                 * will just overwrite it. */
                if ((tmp = malloc(len)) == NULL) {
                        goto error;
                }

                ret = fgets(tmp, (int) (len-1), stream);
                if (ret == NULL) {
                        /* This probably shouldn't happen... */
                        if (feof(stream) != 0) {
                                free(tmp);
                                break;
                        } else {
                                free(tmp);
                                goto error;
                        }
                }

                len *= 2;
                if ((new_dest = realloc(dest, (size_t)len)) == NULL) {
                        free(tmp);
                        goto error;
                }

                dest = new_dest;
                strlcat(dest, tmp, len);
                free(tmp);
        }

        /* Don't include the newline in the line we return. */
        if (newline != NULL)
                *newline = '\0';

        return (ssize_t) (newline - dest - 1);

error:
        free(dest);
        dest = NULL;
        len = 0;
        return -1;
}

#endif
