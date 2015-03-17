#include "concesionario.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>

struct concesionario *leerfichero(char *auxistr) /*He preferido que devuelva un concesionario directamente*/
{

	struct concesionario *con;
	struct coche *c;

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char buffer[4000];

	FILE *f;


	con = curso_concesionario_alloc();

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
				curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO, pt);
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
	fclose(f);
	return(con);

}


void escribirfichero(struct concesionario *con){

	struct coche *c, *c1, *c2;
	uint32_t num_coches;
	uint32_t i;

	FILE *f;


	num_coches = curso_concesionario_attr_get_u32(con, CURSO_CONCESIONARIO_ATTR_NUM_COCHES);
	printf("%u \n", num_coches);

	f = fopen("salidadefinitivo.txt", "w");

	char *matricula;
	int id;
	char *marca;
	char *dueno;

	dueno = malloc(20*sizeof(char));
	matricula = malloc(20*sizeof(char));
	marca = malloc(20*sizeof(char));

	strcpy(dueno, curso_concesionario_attr_get_str(con, CURSO_CONCESIONARIO_ATTR_DUENO));

	for(i=0; i < num_coches; i++)
	{
		c = curso_concesionario_attr_get_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE, i);
		printf("%d\n", i);

		strcpy(matricula, curso_coche_attr_get_str(c, CURSO_COCHE_ATTR_MATRICULA));
		id = curso_coche_attr_get_u32(c, CURSO_COCHE_ATTR_ID);
		strcpy(marca, curso_coche_attr_get_str(c, CURSO_COCHE_ATTR_MARCA));
		fprintf(f, "%s, %d, %s, %s \n", matricula, id, marca, dueno);

	}

	fclose(f);

}

/*Oda a la simpleza,
vamos a guardar los mismos valores recibidos en otro fichero.
Pero porque estamos vagos.*/

void main(int argc, char *argv[]){

	int val, option_index = 0;
	char *auxistr;
	struct concesionario *con;


	static struct option long_options[] = {
		{"fichero", required_argument, 0, 'f'},
		{0}
	};

	val = getopt_long(argc, argv, "f", long_options, &option_index);

	switch(val){

	case 'f':
		auxistr = argv[2];
		con = leerfichero(auxistr);
		/*Aqui se puede jugar con el concesionario a gusto del consumidor*/
		escribirfichero(con);
		break;
	default: 
		printf("No has metido un comando compatible\n");
		break;
	}

}