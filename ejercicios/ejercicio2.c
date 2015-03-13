#include <stdio.h>
#include <getopt.h>
#include "coche.h"
#include "concesionario.h"

int main(int argc, char *argv[])
{
	struct coche *c;
	struct concesionario *con;
	int val, option_index = 0;
	char buffer[4000];

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

	while(1){
		val = getopt_long(argc, argv, "m:i:g:d:h", long_options, &option_index);
		if(val == -1){
			return val;
		}
		switch(val){
		case 'm':
			curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MATRICULA, val);
			break;
		
		case 'i':
			curso_coche_attr_set_u32(c, CURSO_COCHE_ATTR_ID, val);
			break;

		case 'g':
			curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MARCA, val);
			break;
		
		case 'd':
			curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_DUENO, val);
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