#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_LINE_SIZE BUFFER_SIZE

static char buffer[BUFFER_SIZE];
static int buffer_pos = 0;

char *cstm_getline(void)
{
	char *line = (char *)calloc((MAX_LINE_SIZE + 1),  sizeof(char));
	if (line == NULL)
	{
		return (NULL);
	}

	size_t line_size = 0;

	while (1) 
	{
		if (buffer_pos == 0)
		{
		ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));

		if (bytes_read < 0)
		{
			free(line);
			return (NULL);
		}

		if (bytes_read == 0)
		{
			if (line_size > 0)
			{
				return (line);
			}
			else
			{
				free(line);
				return (NULL);
			}
		}
		}

		for (int i = buffer_pos; i < buffer_pos + BUFFER_SIZE; i++)
		{
			if (buffer[i] == '\n' || buffer[i] == '\0')
			{
				if (line_size + i - buffer_pos + 1 <= MAX_LINE_SIZE)
				{
					strncat(line, buffer + buffer_pos, i - buffer_pos + 1);
					line_size += i - buffer_pos + 1;
				}
				else
				{
					fprintf(stderr, "Line exceeds maximum input size\n");
					free(line); 
					return (NULL);
				}

				buffer_pos = i + 1;
				line[line_size] = '\0'; 
				return (line);
			}

			if (line_size + BUFFER_SIZE + 1 <= MAX_LINE_SIZE) 
			{
				strncat(line, buffer + buffer_pos, BUFFER_SIZE);
				line_size += BUFFER_SIZE;
				buffer_pos = 0; 
			}
			else 
			{
				fprintf(stderr, "Line exceeds maximum input size\n");
				free(line); 
				return (NULL);
			}
		}
	}
}

int main() 
{
	while (1)
	{
		char *line = cstm_getline();

		if (line != NULL) 
		{
			printf("You entered: %s\n", line);
			free(line);
		}
		else
		{
			printf("Error reading input or no data entered.\n");
			break;
		}
	}		
	return (0);
}
