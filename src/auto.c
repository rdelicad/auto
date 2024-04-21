#include "../include/auto.h"

void createDirectory(char *str)
{
	char	*subDirs[] = {"nmap", "content", "script"};
	int		numSubDirs = sizeof(subDirs) / sizeof(subDirs[0]);
	char	path[100];
	struct	stat st = {0};

	// verificar si el directorio base ya existe
    if (stat(str, &st) == -1)
    {
        // si el directorio base no existe, intentar crearlo
        if (mkdir(str, 0777) == -1)
        {
            perror("No se pudo crear el directorio base");
            exit(EXIT_FAILURE);
        }
    }

	// crear los subdirectorios
    for (int i = 0; i < numSubDirs; i++)
    {
        sprintf(path, "%s/%s", str, subDirs[i]);

        // verificar si el subdirectorio ya existe
        if (stat(path, &st) == -1)
        {
            // si el subdirectorio no existe, intentar crearlo
            if (mkdir(path, 0777) == -1)
            {
                perror("No se pudo crear el subdirectorio");
                exit(EXIT_FAILURE);
            }
        }
    }

	// posicionarse en el directorio nmap
	sprintf(path, "%s/nmap", str);
	if (chdir(path) == -1)
	{
		perror("No se pudo cambiar de directorio");
		exit(EXIT_FAILURE);
	}
}

void pingMachine(char *ip)
{
	char command[100];
	FILE *file;
	char line[256];
	int success = 0;

	// mostrar mensaje en pantalla de ejecucion del comando
	printf("\033[1;32mHaciendo ping a la maquina \033[1;35m%s\033[0m\n", ip);

	// ejecutar el comando para mostrar la salida en pantalla
	sprintf(command, "ping -c 1 %s", ip);
	system(command);

	// ejecutar el comando para redirigir la salida a un archivo
	sprintf(command, "ping -c 1 %s > output.txt", ip);
	system(command);

	// abrir el archivo de salida
	file = fopen("output.txt", "r");
	if (file == NULL)
	{
		perror("No se pudo abrir el archivo de salida");
		exit(EXIT_FAILURE);
	}

	// leer el archivo de salida
	while (fgets(line, sizeof(line), file))
	{
		if (strstr(line, "1 received"))
		{
			success = 1;
			break;
		}
	}

	// cerrar el archivo de salida
	fclose(file);

	// verificar si se recibio respuesta
	if (success)
		printf("\033[1;32mLa maquina \033[1;35m%s \033[1;32mrespondio al ping\n\033[0m", ip);
	else
		printf("\033[1;31mLa maquina \033[1;35m%s \033[1;31mno respondio al ping\n\033[0m", ip);
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		createDirectory(argv[1]);
		pingMachine(argv[2]);
	}
	else
		printf("Error");
}
