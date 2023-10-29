#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

typedef struct array
{
	char **array;
	int size;
} array;


array *get_pre_parsed_array(char *filename)
{
	array *pre_parsed_array = (array*)malloc(sizeof(array));
	int fd;
	char *temp;
	int i;
	int j;
	int row_len;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return NULL;
	pre_parsed_array -> size  = 0;	
	while (get_next_line(fd) != NULL)
		(pre_parsed_array -> size)++;
	if (close(fd) == -1)
		return NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return NULL;
	pre_parsed_array -> array = (char **)malloc((pre_parsed_array -> size) * sizeof(char*));
	if ((pre_parsed_array -> array) == NULL)
		return NULL;
	i = 0;
	while (i < (pre_parsed_array -> size)  && (temp = get_next_line(fd)) != NULL)
	{
		row_len = 0;
		while (temp[row_len] != '\0')
			row_len++;
		(pre_parsed_array -> array)[i] = (char*)malloc(row_len * sizeof(char));
		if ((pre_parsed_array -> array)[i] == NULL)
			return NULL;
		j = 0;
		while (j < row_len)
		{
			(pre_parsed_array -> array)[i][j] = temp[j];
			j++;
		}
		(pre_parsed_array -> array)[i][j] = '\0';
		i++;
	}
	return (pre_parsed_array);

	
}

int main()
{
	int i;
	array* a = get_pre_parsed_array("numbers.dict");
	for (i = 0; i < a -> size; i++)
		printf("%s", (a -> array)[i]);
}	
