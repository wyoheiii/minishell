
t_parsed	*create_parsed(char **command)
{
	t_parsed	*parsed;

	parsed = (t_parsed *)malloc(sizeof(t_parsed));
	if (parsed == NULL)
		return (NULL);
	parsed->command = command;
	parsed->state = NONE;
	parsed->next = NULL;
	return (parsed);
}
