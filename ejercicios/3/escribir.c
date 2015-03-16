#include "concesionario.h"
#include <stdio.h>
#include <string.h>




void main()
{
	struct concesionario *con;
	struct coche *c, *c1, *c2;
	uint32_t num_coches;
	uint32_t i;

	FILE *f;

	c1 = curso_coche_alloc();

	curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MATRICULA, "DF 67838 SE");
	curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MARCA, "mini");
	curso_coche_attr_set_u32(c1, CURSO_COCHE_ATTR_ID, 0);

	c2 = curso_coche_alloc();

	curso_coche_attr_set_str(c2, CURSO_COCHE_ATTR_MATRICULA, "DF 8819 M");
	curso_coche_attr_set_str(c2, CURSO_COCHE_ATTR_MARCA, "BMW");
	curso_coche_attr_set_u32(c2, CURSO_COCHE_ATTR_ID, 1);

	con = curso_concesionario_alloc();

	curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO, "Alvaro");

	curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE, c1);

	curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE, c2);



	/* A partir de aqui */

	num_coches = curso_concesionario_attr_get_u32(con, CURSO_CONCESIONARIO_ATTR_NUM_COCHES);
	printf("%u \n", num_coches);

	f = fopen("salidacoches.txt", "w");

	char *matricula;
	int id;
	char *marca;
	char *dueno;

	dueno = malloc(20*sizeof(char));
	matricula = malloc(20*sizeof(char));
	marca = malloc(20*sizeof(char));

	strcpy(dueno, curso_concesionario_attr_get_str(con, CURSO_CONCESIONARIO_ATTR_DUENO));


	/* Iterar sobre el concesionario */

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