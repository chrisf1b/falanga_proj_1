#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct line 
{
	char* contents;
	struct line* prev;
	struct line* next;
	int nodeNum;
};



void newElem(struct line* Head, char* newLine, int numElem) 
{

	struct line* Tail = Head;
	while(Tail->next != NULL) {
		Tail = Tail->next;
	}
	struct line * new = (struct line*) malloc(sizeof(struct line));
	size_t lineL = strnlen((const char*)newLine, 32);
	new->contents = (char*) malloc(lineL+1); /* 32 is MAXLEN*/
	/*new->contents = newLine;*/
	strncpy(new->contents, newLine, lineL+1);
	/*new->contents = strdup(newLine);*/
	Tail->next = new;
	new->next = NULL;
	new->prev = Tail;
	new->nodeNum = numElem;
}




int main(int argc, char *argv[])
{
	if (argc != 2 && argc != 3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
	int numLines = 0;
	struct line *Head = NULL; /* create Head*/
	Head = (struct line*) malloc(sizeof(struct line));
	FILE *stream;
	ssize_t getLineReturn;
	size_t len = 0;
	char *lineread = NULL;
	/* readfile */
	/* getline() returns -1 when EOF*/
	stream = fopen(argv[1], "r");
	if (stream == NULL) {
		fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
		exit(1);
	}
	
	while ((getLineReturn = getline(&lineread, &len, stream)) != -1) {
		if (numLines == 0) {
			size_t lineH = strnlen((const char*)lineread, 32);
			Head->contents = malloc(lineH+1);
			if (Head->contents == NULL) {
				fprintf(stderr, "error: malloc failed\n");
				exit(1);
			}
			strncpy(Head->contents, lineread, lineH+1);
			Head->next = NULL;
			Head->nodeNum = 1;
			numLines = numLines + 1;
		}
		else {
			newElem(Head, lineread, numLines+1);
			numLines = numLines + 1;
		}
	}
	struct line *Temp = (struct line*) malloc(sizeof(struct line));
	Temp = Head;
	if (argc == 2) {
		while (Temp->next != NULL) {
			Temp = Temp->next;
			}
		while (Temp != NULL) {
			printf("%s", Temp->contents);
			Temp = Temp->prev;
		}
	}
	if (argc == 3) {
		if (strncmp(argv[1], argv[2], sizeof(argv[1])) == 0) {
			fprintf(stderr, "error: input and output file must differ\n");	
			exit(1);
		}
		struct line *newTemp = (struct line*) malloc(sizeof(struct line));
		newTemp = Head;
		
		/* second arg is the file name to write to */
		FILE *streamTwo;
		streamTwo = fopen(argv[2], "w+");
		while (newTemp->next != NULL) {
			newTemp = newTemp->next;
		}
		while (newTemp != NULL) {
			fprintf(streamTwo, "%s", newTemp->contents); 
			newTemp = newTemp->prev;
			if (stream == NULL) {
				fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
				exit(1);
			} 
		}
		fclose(streamTwo);
		
	}

	free(lineread);
        fclose(stream);
        exit(EXIT_SUCCESS);

}


