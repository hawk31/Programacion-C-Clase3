#include <stdio.h>
#include <getopt.h>
#include "concesionario.h"
#include <string.h>

int main(int argc, char *argv[])
{
	struct coche *c;
	struct concesionario *con;
	int val, option_index = 0;
	char buffer[4000];
	char *auxistr;
	int auxiint;

	static struct option long_options[] = {
		{"matricula", required_argument, 0, 'm'},
		{"id", required_argument, 0, 'i'},
		{"marca", required_argument,0, 'g'},
		{"dueno", required_argument, 0, 'd'},
		{"help", required_argument, 0, 'h'},
		{0}
	};

	c = curso_coche_alloc();
	con = curso_concesionario_alloc();

	auxistr = malloc(20*sizeof(char));


	while(1){
		val = getopt_long(argc, argv, "m:i:g:d:h", long_options, &option_index);
		if(val == -1){
			break;
		}
		switch(val){
		case 'm':
			auxistr = optarg;
			curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MATRICULA, auxistr);
			break;
		
		case 'i':
			auxiint = atoi(optarg);
			curso_coche_attr_set_u32(c, CURSO_COCHE_ATTR_ID, auxiint);
			break;

		case 'g':
			auxistr = optarg;
			curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MARCA, auxistr);
			break;
		
		case 'd':
			auxistr = optarg;
			curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO, auxistr);
			break;
		case 'h':
			printf("Toma ayuda chachi \n");
			break;
		default:
			printf("No has metido un comando compatible \n");
		}

	}
	curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE, c);
	curso_concesionario_snprintf(buffer, sizeof(buffer), con);
	printf("%s", buffer);

}