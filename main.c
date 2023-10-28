#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
char **get_pre_parsed_array(char *filename)
{
	int fd;
	char *temp;
	char	**pre_parsed_array;
	int dict_len;
	int i;
	int j;
	int row_len;

	dict_len = 0;
   	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return NULL;
	while (get_next_line(fd) != NULL)
		dict_len++;
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return NULL;
	pre_parsed_array = (char **)malloc(dict_len * sizeof(char*));
	i = 0;
	while (i < dict_len)
	{
		temp = get_next_line(fd);
		row_len = 0;
		while (temp[row_len] != '\0')
			row_len++;
		pre_parsed_array[i] = (char*)malloc(row_len * sizeof(char));
		j = 0;
		while (j < row_len)
		{
			pre_parsed_array[i][j] = temp[j];
			j++;
		}
		pre_parsed_array[i][j] = '\0';
	}
	return (pre_parsed_array);
}


int main()
{
	char **temp = get_pre_parsed_array("numbers.dict");
	printf("%s\n", temp[0]);
}	
