#include <stdio.h>

/*
	El programa recibe como entrada el codigo fuente de un programa valido de C. Este codigo fuente es mostrado al usuario que ejecuta el programa,
	sin tomar en cuenta los comentarios que existan en este codigo fuente. Los comentarios que se ignoran usan el estilo de comentarios de C (/*)
*/
void comment(void);    
void quote(int); 

int main(void)
{
	int c, d; 
	/* c es la variable que almacena el actual caracter leido. En caso de encontrarse una diagonal,
	se utiliza d para leer un caracter adelante de c. */
	c = getchar();
	while (c != EOF) 
		if (c == '/') 
			if ((d = getchar()) == '*') {
				comment();
				c = getchar();
			}
			else {
				putchar(c);
				c = d;
			}
		else 
			if (c == '"' || c == '\'') {
				quote(c);
				c = getchar();
			}
			else {
				putchar(c);
				c = getchar();
			}
	return 0;
}

/* comment: La funcion lee cada comentario del programa de entrada, cuando termina vuelve a main */
void comment(void)
{
	int c, d;
	/* c es la variable que almacena el anterior caracter leido y d es el actual caracter leido */
	c = getchar();
	while ((d = getchar()) != '/' || c != '*') 
		c = d;
}

/* quote: La funcion se encuentra dentro de una constante de cadena o una constante de caracter.
	Se imprimen todos los caracteres validos antes de que se encuentre el fin de la cadena o 
	constante de caracter */
void quote(int qmark)
{
	int c, last_chr;
	/* c es la variable que almacena el actual caracter leido y last_chr el anterior caracter leido */
	last_chr = '\0'; 
	putchar(qmark); /* Imprime la comilla inicial si es una cadena o el apostrofo si es constante de caracter */
	
	/* Toda comilla o apostrofo que le anteceda una diagonal invertida no es tomada en cuenta como fin */
	while ((c = getchar()) != qmark || last_chr == '\\') {
		putchar(c);
		/* Cuando hay dos diagonales invertidas consecutivas, se hace referencia a la secuencia de escape
		de la diagonal invertida y por lo tanto el ultimo caracter almacenado no puede ser considerado 
		una diagonal invertida */
		if (c == '\\' && last_chr == '\\')
			last_chr = '\0';
		else 
			last_chr = c;
	}
	putchar(c);
}