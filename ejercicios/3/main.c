#include "concesionario.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>




void main(int argc, char *argv[])
{
	struct concesionario *con;
	struct coche *c;
	int val, option_index = 0;
	char *auxistr;

	FILE *f;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char buffer[4000];


	con = curso_concesionario_alloc();

	/* Chunk para leer el nombre del fichero via argumentos */

	static struct option long_options[] = {
		{"fichero", required_argument, 0, 'f'},
		{0}
	};

	val = getopt_long(argc, argv, "f", long_options, &option_index);

	switch(val){

	case 'f':
		auxistr = argv[2];
		break;
	default: 
		printf("No has metido un comando compatible\n");
		break;
	}

	/* Hora de leer el fichero linea a linea */

	printf("%s\n", auxistr);

	f = fopen(auxistr, "r");
	if(f == NULL){
		exit(EXIT_FAILURE);
	}

	while((read = getline(&line, &len, f)) != -1){
		char *pt;
		printf("Linea de tamano %zu \n", read);
		printf("%s\n", line);
		int i=0;
		c = curso_coche_alloc();
		int auxiint;


		pt =  strtok(line, ",");
		while(pt != NULL){
			switch(i){
			case 0:
				curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MATRICULA, pt);
				break;
			case 1:
				auxiint = atoi(pt);
				curso_coche_attr_set_u32(c, CURSO_COCHE_ATTR_ID, auxiint);
				break;
			case 2:
				curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MARCA, pt);
				break;
			case 3:
				curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO, auxistr);
				break;

			}
			i++;
			pt = strtok(NULL, ",");
		}
		curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE, c);
		/*curso_coche_free(c);*/
	}

	curso_concesionario_snprintf(buffer, sizeof(buffer), con);
	printf("%s", buffer);




}