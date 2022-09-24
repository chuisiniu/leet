int isValid(char *s)
{
	static char stack[5000];
	int top;
	char *c;
	char pop;

	top = 0;
	c = s;
	while (*c != '\0') {
		if ('{' == *c || '(' == *c || '[' == *c) {
			if (top >= sizeof(stack))
				break;
			stack[top++] = *c;
		} else {
			if (top == 0)
				return 0;
			pop = stack[--top];
			if (pop == '{' && *c == '}')
				;
			else if (pop == '(' && *c == ')')
				;
			else if (pop == '[' && *c == ']')
				;
			else
				return 0;
		}
		c++;
	}

	return 0 == top;
}
