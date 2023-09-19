#include <stdio.h>
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 128

/**
 *resize_buffer: Resize  buffer for the line
 * This function resizes buffer by doubling capacity
 *
 * @line:pointer to line in the buffer
 * @line capacity:pointer to current capacity of buffer
 *
 */

void resize_buffer(char **line, size_t *line_capacity)
{
	*line_capacity *= 2;
	char *new_line = (char *)realloc(*line, (*line_capacity) * sizeof(char));

	if (new_line == NULL)
	{
		fprintf(stderr, "memory reallocation error\n");
		free(*line);
		exit(EXIT_FAILURE);
	}
	*line = new_line;
}

/**
 * ctsm_getline -  custom getline function
 *
 * function reads a line from given stream
 *
 * @FILE stream: stream pointer to the file stream.
 * @return: pointer to the line read from stream
 * or null if no input entered.
 */

char *cstm_getline(FILE *stream)
{
	char *line = NULL;
	size_t line_size = 0;
	size_t line_capacity = INITIAL_BUFFER_SIZE;
	int c;

	if (stream == NULL)
	{
		return (NULL);
	}

	line = (char *)malloc(line_capacity * sizeof(char));
	if (line == NULL)
	{
		return (NULL);
	}

	while (1)
	{
		c = fgetc(stream);
		if (c == EOF)
		{
			if (line_size == 0)
			{
				free(line);
				return (NULL);
			}
			break;
		}

		if (line_size >= line_capacity - 1)
		{
			resize_buffer(&line, &line_capacity);
		}

		line[line_size++] = (char)c;
		if (c == '\n')
		{
			break;
		}
	}

	line[line_size] = '\0';

	return (line);
}

/**
 * main function: this is the entry point of program
 *
 * responsible for handling user input
 *
 * return: exit status of the program..
 */

int main(void)
{
	char *line;

	printf("Enter your text input:\n");

	while ((line = cstm_getline(stdin)) != NULL)
{
		printf("Your input: %s", line);
		free(line);
	}

	return (0);
}

